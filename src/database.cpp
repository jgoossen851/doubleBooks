#include "database.h"

#include <cassert>

template<FormatVersion VER>
unsigned int Format<VER>::columns(void) {
	switch (VER) {
		case A1 :
			return 8;
			break;
		default :
			return 0;
			break;
	};
}
// Template Instantiation
template unsigned int Format<A1>::columns(void);


template<FormatVersion VER>
Database<VER>::Database(const StringDatabase &strDb)
					: number_of_columns(Format<VER>::columns()),
					  header(strDb.header),
					  column_width(strDb.column_width) {
	assert(this->number_of_columns == strDb.number_of_columns);
	formatData_(strDb.body);
}
// Template Instantiation
template Database<A1>::Database(const StringDatabase&);


/// Template specializations for different formats
template<>
Transaction Format<A1>::parse_transaction(const std::vector<std::string> &trans_str) {
	assert(trans_str.size() == columns());
	
	Transaction trans;
	
	trans.id = std::stoul(trans_str.at(0), nullptr);
	trans.entry_title = trans_str.at(1);
	trans.entry_number = std::stoul(trans_str.at(2), nullptr);
	trans.entry_date.setFromStr(trans_str.at(3));
	trans.category.setFromStr(trans_str.at(4));
	trans.transaction_amount.setFromStr(trans_str.at(5));
	trans.memo = trans_str.at(6);
	trans.statement = std::stoi(trans_str.at(7), nullptr);	
	
	return trans;
}

/// Template specializations for different formats
template<>
std::vector<std::string> Format<A1>::format_transaction(const Transaction &trans) {
	
	std::vector<std::string> trans_str;
	
	trans_str.push_back(std::to_string(trans.id));
	trans_str.push_back(trans.entry_title);
	trans_str.push_back(std::to_string(trans.entry_number));
	trans_str.push_back(trans.entry_date.date_str);
	trans_str.push_back(std::to_string(trans.category.cat));
	trans_str.push_back(trans.transaction_amount.display());
	trans_str.push_back(trans.memo);
	trans_str.push_back(std::to_string(trans.statement));
	
	return trans_str;
}
