/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PARENTOF_H_
#define PARENTOF_H_

#include "childAddress.h"

/**
 * @brief Class that contains references to children objects
 * 
 * @note: The class cannot be copy constructed, copy assigned,
 * or move constructed due to the limitations of the member mChildAddr_.
 */
template<typename T>
class parentOf {
  childAddress<T> mChildAddr_;

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  parentOf()
      : mChildAddr_(this, nullptr) {};
  /// Destructor function
  ~parentOf() = default;
  /// Move Assignement Operator
  parentOf& operator=(parentOf&& other) = default;

  void addChild(T& newChild) {
    mChildAddr_.addChild(newChild);
  }

  void replaceChild(T& oldChild, T& newChild) {
    mChildAddr_.replaceChild(oldChild, newChild);
  }

  void removeChild(T& oldChild) {
    mChildAddr_.removeChild(oldChild);
  }

};

#endif // PARENTOF_H_
