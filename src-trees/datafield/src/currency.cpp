/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "currency.h"

#include <cstdio>
#include <cmath>
#include <cassert>
#include <string>
#include <iostream>

#include "ansi.h"
#include "strings.h"

Currency::Currency(NegativeFormat negativeFormat) 
    : cents_(0),
      negativeFormat_(negativeFormat) {}

Currency::Currency( int            cents,
                    NegativeFormat negativeFormat)
  : cents_(cents),
    negativeFormat_(negativeFormat) {}

Currency::Currency( std::string    str,
                    NegativeFormat negativeFormat)
    : cents_(0),
      negativeFormat_(negativeFormat) {
  setFromStr(str);
}

std::string Currency::str(const unsigned int &max_characters) const {
  if (cents_ < 0) {
    // Format negative number
    int characters = max_characters;
    switch (negativeFormat_) {
      case NEGATIVE_SIGN :
        characters--;     // Reserve space for negative sign
        break;
      case PARENTHESIS :
        characters -= 2;   // Reserve space for parenthesis
        break;
      case RED_COLOR :
      default :
        break;
    }
    return format_negative_string(display_magnitude(characters));
  } else {
    // Format positive number
    return display_magnitude(max_characters);
  }
}

std::string Currency::display_magnitude(const int &max_chars) const {
  constexpr int buffer_len = 16;
  assert(buffer_len > max_chars + 1); // Ensure buffer can fit all characters and null terminator
  char display_value[buffer_len];
  int chars = snprintf( display_value, buffer_len, "$%04.2f", (float)abs(cents_)/100);
  return (chars <= max_chars)
        ? std::string(display_value)
        : std::string(max_chars, '*');  
}

std::string Currency::format_negative_string(std::string positiveString) const {
  std::string negativeString;
  
  switch (negativeFormat_) {
    case NEGATIVE_SIGN :
      negativeString = "-" + positiveString;
      break;
    case PARENTHESIS :
      negativeString = "(" + positiveString + ")";
      break;
    case RED_COLOR :
      negativeString = ansi::SAVE_ATTRIBUTES + ansi::RED + positiveString + ansi::RESTORE_ATTRIBUTES;
      break;
    default :
      negativeString = "-" + positiveString;
  }
  
  return negativeString;
}

bool Currency::operator<(const Element &rhs) const {
  return this->cents_ < *static_cast<const int*>(rhs.value_ptr());
}

void Currency::setFromStr(std::string str) {
  // Erase non-digit or decimal or negative characters
  str.erase(0, str.find_first_of("0123456789.-"));
  double dollars = Strings::toDouble(str);
  cents_ = round(dollars*100);
  double residual = cents_ - dollars*100;
  assert(fabs(residual) < 0.001);
  return;
}

const void* Currency::value_ptr(void) const {
  return &cents_;
}


