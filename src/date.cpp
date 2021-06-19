
#include "date.h"

#include <iostream>

std::string Date::str(const unsigned int &max_characters) const {
  std::cout << "Converting date to string." << std::endl;
  if (date_str.size() <= max_characters) {
    std::cout << "Date ok length" << std::endl;
    return date_str;
  } else {
    std::cout << "Date too long" << std::endl;
    return std::string(max_characters, '*');
  }
}

void Date::setFromStr(std::string str) {
  date_str = str;
}

const void* Date::value_ptr(void) const {
  return &date_str;
}

bool Date::operator<(const Element &rhs) const {
  return this->date_str < *static_cast<const std::string*>(rhs.value_ptr());
}