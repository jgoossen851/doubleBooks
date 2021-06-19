#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>

#include "transaction.h"
#include "format.h"
#include "csv.h"

/// Formatted database
template<FormatVersion VER>
struct Database{
 public:
  Database(const StringDatabase &strDb);
		
	const std::vector<std::string>::size_type number_of_columns;
	const std::vector<std::string>				    header;
	const std::vector<unsigned int>				    column_width; // in characters
	std::vector<Transaction> 			            body;
	
 private:
	bool formatData_(const std::vector<std::vector<std::string>> &data_str);
};

#endif