#ifndef CSV_H_
#define CSV_H_

#include <string>
#include <vector>

/// Unformatted Database
struct StringDatabase{
  unsigned int                        	number_of_columns;
	std::vector<std::string> 				      header;
	std::vector<unsigned int> 				    column_width; // in characters
	std::vector<std::vector<std::string>> body;
};

class Csv {
	const char * filename_;
	
 public:
	Csv(const char * filename);
	
	StringDatabase load(void);
	
 private:
	/// Function to split a string into a vector of strings delimited by a character
	std::vector<std::string> delimitString_(	std::string str,
											std::vector<std::string>::size_type max_entries = (unsigned int)-1);
};

#endif
