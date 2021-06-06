#include "table.h"

#include <vector>
#include <string>
#include <cstdio>

#include "database.h"
#include "ansi.h"

Table::Table(	unsigned int columns,
				std::vector<unsigned int> widths,
				std::vector<std::string> header,
				std::vector<std::vector<std::string>> data ) {
	columns_ = columns;
	widths_ = widths;
	header_ = header;
	data_ = data;
}
	
Table::Table(Database db) {
	columns_ = db.number_of_columns;
	widths_ = db.column_width;
	header_ = db.header;
	data_ = db.body;
}
	
void Table::print(){
	printf("\n");
	printf("%s%s", ansi::BOLD, ansi::UNDERLINE);
	printHeader_();
	printf("%s\n", ansi::RESET);
	printData_();
}
	
void Table::printHeader_(){
	for (unsigned int ii = 0; ii < columns_; ii++) {
		printf("%-*.*s  ", widths_.at(ii), widths_.at(ii), header_.at(ii).c_str());
	}
}

void Table::printData_(){
	for (unsigned int ii = 0; ii < data_.size(); ii++) {
		for (unsigned int jj = 0; jj < columns_; jj++) {
			printf("%-*.*s  ", widths_.at(jj), widths_.at(jj), data_.at(ii).at(jj).c_str());
		}
		printf("\n");
	}	
}
