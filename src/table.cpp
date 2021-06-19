#include "table.h"

#include <vector>
#include <string>
#include <cstdio>
// #include <iostream>
#include <cassert>

#include "database.h"
#include "ansi.h"

Table::Table( unsigned int columns,
              std::vector<unsigned int> widths,
              std::vector<std::string> header,
              std::vector<std::vector<std::string>> data ) {
  columns_  = columns;
  // std::cout << "\033[31mTable default constructed with " << columns_ << " columns\033[0m" << std::endl;
  widths_   = widths;
  header_   = header;
  data_     = data;
}
  
Table::Table(Database<A1> db) {
  columns_  = db.number_of_columns;
  // std::cout << "\033[31mTable constructed from DB with " << columns_ << " columns\033[0m" << std::endl;
  widths_   = db.column_width;
  header_   = db.header;
  // std::cout << "So far so good...  Size is " << db.body.size() <<  std::endl;
  for (unsigned int ii = 0; ii < db.body.size(); ii++) {
    data_.push_back(db.body.at(ii).formatEntry());
  }
}

Table::Table(StringDatabase db) {
  columns_  = db.number_of_columns;
  // std::cout << "\033[31mTable constructed from string with " << columns_ << " columns\033[0m" << std::endl;
  widths_   = db.column_width;
  header_   = db.header;
  data_     = db.body;
}
  
void Table::print(){
  // std::cout << "Table properties: columns: " << columns_ << "  Length of header: " << header_.size() 
  //           << "\nLength of widths: " << widths_.size() << "  Length of data_(num entries): " << data_.size() 
  //           << "\nLength of data(width): " << data_.at(0).size() << std::endl;
  assert(data_.at(0).size() == widths_.size());
  printf("\n");
#ifdef CLEAR_SCREEN_ENABLE
  printf("%s", (ansi::CLEAR + ansi::BOLD + ansi::UNDERLINE + ansi::OVERLINE).c_str());
#else
  printf("%s", (ansi::BOLD + ansi::UNDERLINE + ansi::OVERLINE).c_str());
#endif
  printHeader_();
  printf("%s\n", ansi::RESET.c_str());
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
