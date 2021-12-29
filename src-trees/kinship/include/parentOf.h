/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PARENTOF_H_
#define PARENTOF_H_

class parentOf {

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  parentOf() = default;
  /// Destructor function
  ~parentOf() = default;
  /// Copy Constructor Function
  parentOf(const parentOf& other) = default;
  /// Copy Assignment Operator
  parentOf& operator=(const parentOf& other) = default;
  /// Move Constructor Function
  parentOf(parentOf&& other) = default;
  /// Move Assignement Operator
  parentOf& operator=(parentOf&& other) = default;

};

#endif // PARENTOF_H_
