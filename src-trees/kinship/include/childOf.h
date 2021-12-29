/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CHILDOF_H_
#define CHILDOF_H_

class childOf {

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  childOf() = default;
  /// Destructor function
  ~childOf() = default;
  /// Copy Constructor Function
  childOf(const childOf& other) = default;
  /// Copy Assignment Operator
  childOf& operator=(const childOf& other) = default;
  /// Move Constructor Function
  childOf(childOf&& other) = default;
  /// Move Assignement Operator
  childOf& operator=(childOf&& other) = default;

};

#endif // CHILDOF_H_
