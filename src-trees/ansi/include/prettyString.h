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

  // Equality test opeator
  friend bool operator== (const PrettyString &rhs, const PrettyString &lhs);
  friend bool operator!= (const PrettyString &rhs, const PrettyString &lhs);
  friend PrettyString& operator+= (PrettyString &lhs, const PrettyString &rhs);
  friend const PrettyString operator+(const PrettyString &lhs, const PrettyString &rhs);

  // /// @todo Move outside class. See #7: https://isocpp.org/wiki/faq/operator-overloading#op-ov-rules
  // // Function to Append to Pretty String
  // PrettyString& operator+= (const PrettyString& str) {
  //   str_ += str.str_;
  //   numUnprintableChars_ += str.numUnprintableChars_;
  //   return *this;
  // }

  // /// Function to concatinate two PrettyStrings
  // PrettyString operator+(const PrettyString &rhs) {
  //   return PrettyString(this->str_ + rhs.str_, this->numUnprintableChars_ + rhs.numUnprintableChars_);
  // }
  // /// Function to concatinate PrettyString with string
  // PrettyString operator+(const std::string &rhs) {
  //   return PrettyString(this->str_ + rhs, this->numUnprintableChars_);
  // }
  // /// Function to concatinate PrettyString with char array
  // PrettyString operator+(const char *rhs) {
  //   std::string rhsStr(rhs);
  //   return PrettyString(this->str_ + rhsStr, this->numUnprintableChars_);
  // }
  // /// Function to concatinate PrettyString with char array
  // PrettyString operator+(const char rhs) {
  //   std::string rhsStr(1, rhs);
  //   return PrettyString(this->str_ + rhsStr, this->numUnprintableChars_);
  // }
  // /// Function to concatinate string with PrettyString
  // friend PrettyString operator+ (const std::string &lhs, const PrettyString &rhs) {
  //   return PrettyString(lhs + rhs.str_, rhs.numUnprintableChars_);
  // }
  // /// Function to concatinate char array with PrettyString
  // friend PrettyString operator+ (const char *lhs, const PrettyString &rhs) {
  //   std::string lhsStr(lhs);
  //   return PrettyString(lhsStr + rhs.str_, rhs.numUnprintableChars_);
  // }
  // /// Function to concatinate char with PrettyString
  // friend PrettyString operator+ (char lhs, const PrettyString &rhs) {
  //   std::string lhsStr(1, lhs);
  //   return PrettyString(lhsStr + rhs.str_, rhs.numUnprintableChars_);
  // }
  

  /// Function to format as stream
  friend std::ostream& operator<< (std::ostream& o, const PrettyString& x){
    return o << x.str_;
  }

  // friend int std::string::compare (const PrettyString& lhs) {
  //   return rhs.compare(lhs.str_);
  // }

  /// Function to format a string as entirely formatting characters
  static PrettyString format(const std::string &str) {
    return PrettyString(str, str.length());
  }
};






// // /// Function to Append to Pretty String
// // PrettyString& operator+= (PrettyString& lhs, const PrettyString& rhs) {
// //   lhs.str_ += rhs.str_;
// //   lhs.numUnprintableChars_ += rhs.numUnprintableChars_;
// //   return lhs;
// // }

// // /// Function to concatinate two PrettyStrings
// // const PrettyString operator+(const PrettyString &lhs, const PrettyString &rhs) {
// //   // return PrettyString(lhs) += rhs;
// //   PrettyString result = lhs;
// //   return result += rhs;
// // }

// /// Function to concatinate two PrettyStrings
// PrettyString operator+(const PrettyString &rhs) {
//   return PrettyString(this->str_ + rhs.str_, this->numUnprintableChars_ + rhs.numUnprintableChars_);
// }
// /// Function to concatinate PrettyString with string
// PrettyString operator+(const std::string &rhs) {
//   return PrettyString(this->str_ + rhs, this->numUnprintableChars_);
// }
// /// Function to concatinate PrettyString with char array
// PrettyString operator+(const char *rhs) {
//   std::string rhsStr(rhs);
//   return PrettyString(this->str_ + rhsStr, this->numUnprintableChars_);
// }
// /// Function to concatinate PrettyString with char array
// PrettyString operator+(const char rhs) {
//   std::string rhsStr(1, rhs);
//   return PrettyString(this->str_ + rhsStr, this->numUnprintableChars_);
// }
// /// Function to concatinate string with PrettyString
// friend PrettyString operator+ (const std::string &lhs, const PrettyString &rhs) {
//   return PrettyString(lhs + rhs.str_, rhs.numUnprintableChars_);
// }
// /// Function to concatinate char array with PrettyString
// friend PrettyString operator+ (const char *lhs, const PrettyString &rhs) {
//   std::string lhsStr(lhs);
//   return PrettyString(lhsStr + rhs.str_, rhs.numUnprintableChars_);
// }
// /// Function to concatinate char with PrettyString
// friend PrettyString operator+ (char lhs, const PrettyString &rhs) {
//   std::string lhsStr(1, lhs);
//   return PrettyString(lhsStr + rhs.str_, rhs.numUnprintableChars_);
// }






#endif // PRETTYSTRING_H_
