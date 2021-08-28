/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "date.h"

// #include <iostream>

std::string Date::str(const unsigned int &max_characters) const {
  // std::cout << "Converting date to string." << std::endl;
  if (date_str.size() <= max_characters) {
    // std::cout << "Date ok length" << std::endl;
    return date_str;
  } else {
    // std::cout << "Date too long" << std::endl;
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
