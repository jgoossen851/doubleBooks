/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef DATE_H_
#define DATE_H_

#include "element.h"

#include <ctime>

class Date : public Element {
  struct std::tm  date_;
  int             sortValue_;
  
 public:
  /// Default Constructor Function
  Date();
  /// Parameterized Constructor Function
  Date(std::string str);

  /// Function Overrides from Element
  std::string str(const unsigned int &max_characters = 8) const override;
  void setFromStr(std::string str) override;
  const void* value_ptr(void) const override;
  bool operator<(const Element &rhs) const override;

  bool operator==(const Date &rhs) const {
    return sortValue_ == rhs.sortValue_;
  }

 private:
  bool isDateValid() const;
  std::string getDateStr(const char * format) const;
  void invalidateDate();
  void setDaysSinceJan1();


};

#endif
