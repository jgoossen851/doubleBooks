/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PRETTYSTRING_H_
#define PRETTYSTRING_H_

#include <string>

class PrettyString {
  std::string str_;
  uint        numUnprintableChars_ = 0;

 public:
  PrettyString() = default;
  PrettyString(const std::string &str, const uint &numUnprintableChars)
      : str_(str)
      , numUnprintableChars_(numUnprintableChars) {}

  // Copy Constructor from string
  PrettyString(const std::string &str) 
      : str_(str)
      , numUnprintableChars_(0) {}
  // Copy Constructor from char array
  PrettyString(const char *str) 
      : str_(std::string(str))
      , numUnprintableChars_(0) {}
  // Copy Constructor from char
  PrettyString(const char str) 
      : str_(std::string(1, str))
      , numUnprintableChars_(0) {}

  // Copy Assignment Operator from string
  PrettyString& operator=(const std::string &rhs) {
    str_ = rhs;
    numUnprintableChars_ = 0;
    return *this;
  }

  std::string getStr(void) const {
    return str_;
  }

  // Define operator overloading as friend functions outside of scope to allow promotion of argument types
  // See #7: https://isocpp.org/wiki/faq/operator-overloading#op-ov-rules
  friend bool operator== (const PrettyString &rhs, const PrettyString &lhs);
  friend bool operator!= (const PrettyString &rhs, const PrettyString &lhs);
  friend PrettyString& operator+= (PrettyString &lhs, const PrettyString &rhs);
  friend const PrettyString operator+(const PrettyString &lhs, const PrettyString &rhs);

  /// Function to format as stream
  friend std::ostream& operator<< (std::ostream& o, const PrettyString& x){
    return o << x.str_;
  }

  /// Function to format a string as entirely formatting characters
  static PrettyString format(const std::string &str) {
    return PrettyString(str, str.length());
  }
};

#endif // PRETTYSTRING_H_
