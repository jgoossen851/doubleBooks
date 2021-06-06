#ifndef CSV_H_
#define CSV_H_

#include <string>
#include <vector>

#include "database.h"

class Csv {
  public:
	Csv(const char * filename);
	
	Database load(void);
	
  private:
	/// Function to split a string into a vector of strings delimited by a character
	std::vector<std::string> delimitString_(	std::string str,
											std::vector<std::string>::size_type max_entries = (unsigned int)-1);
	/// Function to determine if a string is an integer
	bool isInteger_(std::string str);
	
	const char * filename_;
};

#endif
