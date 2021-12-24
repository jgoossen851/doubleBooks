/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CURRENCY_H_
#define CURRENCY_H_

#include <string>

#include "element.h"

/// Allowable formats for negative currencies
enum NegativeFormat{
  NEGATIVE_SIGN,  //!< Value printed to the right of a negative sign
  PARENTHESIS,    //!< Value printed inside parenthesis
  RED_COLOR       //!< Value printed in red
};

class Currency : public Element {
  /// Internal Storage of the currency value, in cents
  int             cents_;
  NegativeFormat  negativeFormat_;
  
 public:
  /// Default Constructor
  Currency(NegativeFormat negativeFormat = NEGATIVE_SIGN);
  /// Parameterized Constructors
  Currency(int            cents,
           NegativeFormat negativeFormat = NEGATIVE_SIGN);
  Currency(std::string    str,
           NegativeFormat negativeFormat = NEGATIVE_SIGN);
    
  // Function Overrides
  /// Format the dollar amount as a string
  std::string str(const unsigned int &max_characters = 10) const override;
  void setFromStr(std::string str) override;
  const void* value_ptr(void) const override;
  /// Comparison operator for two Currency objects
  bool operator<(const Element &rhs) const override;

  Currency operator-() const {
    return Currency(-cents_, negativeFormat_);
  }

  Currency& operator+=(const Currency &rhs) {
    cents_ += rhs.cents_;
    return *this;
  }
  const Currency operator+(const Currency &rhs) const {
    return Currency(*this) += rhs;
  }
  
 private:  
  std::string display_magnitude(const int &max_characters) const;
  std::string format_negative_string(std::string positiveString) const;
  std::string format_positive_string(std::string positiveString) const;

};

#endif
