#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>

#include "transaction.h"

/// Unformatted Database
struct StringDatabase{
    std::vector<std::string>::size_type 	number_of_columns;
	std::vector<std::string> 				header;
	std::vector<unsigned int> 				column_width; // in characters
	std::vector<std::vector<std::string>> 	body;
};

/// Database formats and versions
enum FormatVersion {
	A1,
};

template<FormatVersion VER>
class Format {
  public:
	static unsigned int columns(void);
	
	static Transaction 				parse_transaction	(const std::vector<std::string> &trans_str);
	static std::vector<std::string> format_transaction	(const Transaction &trans);
};

/// Formatted database
template<FormatVersion VER>
struct Database{
  public:
	Database(const StringDatabase &strDb);
		
	const std::vector<std::string>::size_type 	number_of_columns;
	const std::vector<std::string>				header;
	const std::vector<unsigned int>				column_width; // in characters
	std::vector<Transaction> 					body;
	
  private:
	bool formatData_(const std::vector<std::vector<std::string>> &data_str){
		for (unsigned int ii = 0; ii < data_str.size(); ii++) {
			body.push_back(Format<VER>::parse_transaction(data_str.at(ii)));
		}
		return true;
	};
};

#endif