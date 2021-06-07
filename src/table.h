#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include <string>

#include "database.h"

class Table{
  public:
	Table(	unsigned int columns,
			std::vector<unsigned int> widths,
			std::vector<std::string> header,
			std::vector<std::vector<std::string>> data );
	Table(	Database<A1> db);
	Table(	StringDatabase db);
	
	void print();
	
  private:
	void printHeader_();
	void printData_();
	
	unsigned int 							columns_;
	std::vector<unsigned int> 				widths_;
	std::vector<std::string> 				header_;
	std::vector<std::vector<std::string>> 	data_;
};

#endif