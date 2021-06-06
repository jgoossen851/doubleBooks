#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>

struct Database{
    std::vector<std::string>::size_type 	number_of_columns;
	std::vector<std::string> 				header;
	std::vector<unsigned int> 				column_width; // in characters
	std::vector<std::vector<std::string>> 	body;
};

#endif