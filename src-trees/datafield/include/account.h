/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// #include <string>
// #include <vector>
// #include <iostream>
// #include <cassert>

#include "element.h"

class Account : public Element {
  unsigned int    id_;
  
 public:
  /// Default constructor function
  Account(){}
  /// Parameterized constructor function
 
  // Override inherited functions
  std::string str(const unsigned int &max_characters = 12) const override {
    return std::string(max_characters, '*'); // Placeholder
  }
  void setFromStr(std::string str) {
    id_ = str.size(); // Placeholder
    return;
  }
  const void* value_ptr(void) const override {return nullptr;} // Placeholder
  bool operator<(const Element &rhs) const override;
};

#endif // ACCOUNT_H_
