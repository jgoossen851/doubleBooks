#include "csv.h"

#define DEBUG_MODE 0

#include <fstream>

#if DEBUG_MODE
	#include <iostream>
	#include "ansi.h"
#endif

Csv::Csv(const char * filename)
			: filename_(filename) 
			{}

Database Csv::load(){

	std::ifstream file(filename_);
	std::string line;
	Database data;
  
	#if DEBUG_MODE
		std::cout << ansi::UNDERLINE << "Contents of "
				  << ansi::BOLD << ansi::ITALIC << filename_
				  << ansi::RESET << ":" << std::endl;
	#endif
  
	// Initialize flags
	bool process_widths = false;
	bool process_data = false;

	// Iterate through lines until the end of the file
	while (file.eof() == false) {
		std::getline(file, line);
		#if DEBUG_MODE
			std::cout << ansi::RED << line << ansi::RESET << std::endl;
		#endif
		
		// Read first element to determine if string should be processed
		std::string first_element = line.substr(0, line.find('\t', 0));
		
		if (first_element == "ID") {
			// First, find and process headers
			data.header = delimitString_(line);
			data.number_of_columns = data.header.size();
			process_widths = true;
		} else if (process_widths) {
			// Then, process the field widths for each column
			std::vector<std::string> widths = delimitString_(line);
			for (unsigned int ii = 0; ii < widths.size(); ii++) {
				data.column_width.push_back(widths.at(ii).size());
			}
			process_widths = false;
			process_data = true;
		} else if (process_data && isInteger_(first_element)){
			// Finally, process the remaining data
			data.body.push_back(delimitString_(line, data.number_of_columns));
		}
	}
	
	return data;
}

bool Csv::isInteger_(std::string str) {
	if (str.empty()) return 0;
	
	char* ptr;
	constexpr int base = 10;
	strtol(str.c_str(), &ptr, base);
	return *ptr == 0;
}

std::vector<std::string> Csv::delimitString_(std::string str,
										std::vector<std::string>::size_type max_entries) {
	
	std::vector<std::string> parsedString;
	std::string element;
	
	std::size_t pos = 0; // position to start
	std::size_t len = 0;	
	while (len != std::string::npos && parsedString.size() < max_entries) {
		len = str.find('\t', pos);
		element = str.substr(pos, len - pos);
		pos = len+1;
		// Do not allow empty elements if no size is given
		if (max_entries == (unsigned int)-1 && element.empty()) break;
		parsedString.push_back(element);
		#if DEBUG_MODE
			std::cout << "[" << ansi::YELLOW << element << ansi::RESET << "]";
		#endif
	}
	#if DEBUG_MODE
		std::cout << std::endl;
	#endif
	
	return parsedString;
}
