
#include "date.h"

std::string Date::str(const unsigned int &max_characters) const {
  if (date_str.size() <= max_characters) {
    return date_str;
  } else {
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