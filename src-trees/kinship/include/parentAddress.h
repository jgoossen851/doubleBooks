/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PARENTADDRESS_H_
#define PARENTADDRESS_H_

class parentAddress {

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  parentAddress() = default;
  /// Destructor function
  ~parentAddress() = default;
  /// Copy Constructor Function
  parentAddress(const parentAddress& other) = default;
  /// Copy Assignment Operator
  parentAddress& operator=(const parentAddress& other) = default;
  /// Move Constructor Function
  parentAddress(parentAddress&& other) = default;
  /// Move Assignement Operator
  parentAddress& operator=(parentAddress&& other) = default;

};

#endif // PARENTADDRESS_H_
