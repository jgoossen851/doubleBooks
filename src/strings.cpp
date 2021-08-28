/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "strings.h"

namespace Strings {
  
/// Function to determine if a string is an integer
bool isInteger(const std::string str) {
  
  // Iterate throught the string until a non-digit is encountered
  std::string::const_iterator it = str.begin();
  while (it != str.end() && std::isdigit(*it)) ++it;
  
  return !str.empty() && it == str.end();
}

unsigned long toInteger(const std::string str) {
  return isInteger(str) ? std::stoul(str, nullptr) : (unsigned long)(-1);
}

float         toFloat(const std::string str){
  return (str == "") ? 0.0 : std::stof(str, nullptr);
}

double        toDouble(const std::string str){
  return (str == "") ? 0.0 : std::stod(str, nullptr);
}

} // namespace Strings
