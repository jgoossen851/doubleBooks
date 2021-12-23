/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef DATAFIELD_H_
#define DATAFIELD_H_

#include "element.h"

#include <string>

class StringField : public Element {
  std::string str_ = "";
  
 public:
  /// Default Constructor Function
  StringField();
  /// Parameterized Constructor Function
  StringField(std::string str);

  /// Function Overrides from Element
  std::string str(const unsigned int &max_characters = 3) const override;
  void setFromStr(std::string str) override;
  const void* value_ptr(void) const override;
  bool operator<(const Element &rhs) const override;
};

class UintField : public Element {
  unsigned int uint_ = -1;
  
 public:
  /// Default Constructor Function
  UintField();
  /// Parameterized Constructor Function
  UintField(std::string str);

  /// Function Overrides from Element
  std::string str(const unsigned int &max_characters = 3) const override;
  void setFromStr(std::string str) override;
  const void* value_ptr(void) const override;
  bool operator<(const Element &rhs) const override;
};

class BoolField : public Element {
  bool bool_ = false;
  
 public:
  /// Default Constructor Function
  BoolField();
  /// Parameterized Constructor Function
  BoolField(std::string str);

  /// Function Overrides from Element
  std::string str(const unsigned int &max_characters = 3) const override;
  void setFromStr(std::string str) override;
  const void* value_ptr(void) const override;
  bool operator<(const Element &rhs) const override;
};

#endif // DATAFIELD_H_
