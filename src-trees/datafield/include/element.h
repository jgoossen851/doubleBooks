/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>

/// Base class for transaction elements
class Element{
 public:
  /// Function to format the element as a string for printing
  virtual std::string str(const unsigned int &max_characters) const =0;
  /// Function to return a pointer to the element's value, for comparisons
  virtual const void* value_ptr(void) const =0;
  /// Function to compare two elements
  virtual bool operator<(const Element &rhs) const =0;
  
};

#endif
