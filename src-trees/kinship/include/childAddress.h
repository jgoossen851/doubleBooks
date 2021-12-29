/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CHILDADDRESS_H_
#define CHILDADDRESS_H_

class childAddress {

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  childAddress() = default;
  /// Destructor function
  ~childAddress() = default;
  /// Copy Constructor Function
  childAddress(const childAddress& other) = default;
  /// Copy Assignment Operator
  childAddress& operator=(const childAddress& other) = default;
  /// Move Constructor Function
  childAddress(childAddress&& other) = default;
  /// Move Assignement Operator
  childAddress& operator=(childAddress&& other) = default;

};

#endif // CHILDADDRESS_H_
