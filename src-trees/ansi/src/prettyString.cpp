/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "prettyString.h"

bool operator== (const PrettyString &rhs, const PrettyString &lhs) {
  return rhs.numUnprintableChars_ == lhs.numUnprintableChars_ && rhs.str_ == lhs.str_;
}

bool operator!= (const PrettyString &rhs, const PrettyString &lhs) {
  return !(rhs == lhs);
}

/// Function to Append to Pretty String
PrettyString& operator+= (PrettyString& lhs, const PrettyString& rhs) {
  lhs.str_ += rhs.str_;
  lhs.numUnprintableChars_ += rhs.numUnprintableChars_;
  return lhs;
}

/// Function to concatinate two PrettyStrings
const PrettyString operator+(const PrettyString &lhs, const PrettyString &rhs) {
  PrettyString result = lhs;
  return result += rhs;
}
