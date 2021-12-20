/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef DATE_H_
#define DATE_H_

#include "element.h"

// Placeholder
class Date : public Element {
  std::string date_str;
  
  public:
  Date(){};
  std::string str(const unsigned int &max_characters = 8) const override;
  void setFromStr(std::string str) override;
  const void* value_ptr(void) const override;
  bool operator<(const Element &rhs) const override;
};

#endif
