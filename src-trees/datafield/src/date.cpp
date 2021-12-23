/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "date.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <locale>

Date::Date(){
  invalidateDate();
}

Date::Date(std::string str){
  setFromStr(str);
}

std::string Date::str(const unsigned int &max_characters) const {
  std::string dateStr = isDateValid() ? getDateStr("%m/%d/%y") : "--/--/--";
  return (dateStr.size() <= max_characters) ? dateStr : std::string(max_characters, '*');
}

bool Date::isDateValid() const {
  return 0 < date_.tm_mday && date_.tm_mday <= 31 // Day in [1-31]
      && 0 <= date_.tm_mon && date_.tm_mon < 12;  // Month since Jan in [0-11]
}

std::string Date::getDateStr(const char * format) const {
  std::ostringstream ss;
  ss << std::put_time(&date_, format);
  return ss.str();
}

void Date::setFromStr(std::string str) {
  
  std::istringstream ss(str);
  // Set expected string format
  ss.imbue(std::locale("en_US.UTF-8"));
  const char *in_format = "%m/%d/%Y";
  
  ss >> std::get_time(&date_, in_format);
  if (ss.fail()) {
    invalidateDate();
  } else {
    setDaysSinceJan1();
  }
}

void Date::invalidateDate() {
  // Set day to 0 to invalidate
  date_.tm_mday = 0;
  // Clear other values
  date_.tm_year = 0;
  date_.tm_mon = 0;
  date_.tm_yday = 0;
  sortValue_ = 0;
}

void Date::setDaysSinceJan1(){
  if (isDateValid()) {
    // Initialize day of year since first of month
    date_.tm_yday = date_.tm_mday - 1;
    // Add the cumulative total days from previous months
    const int monthTotals[12]
        = {   0,  31,  59,  90, 120, 151,
            181, 212, 243, 273, 304, 334 };
    assert((unsigned int)date_.tm_mon < 12);
    date_.tm_yday += monthTotals[date_.tm_mon];
    // Add one day if leap year and after Feb (tm_mon == 1)
    if (date_.tm_mon > 1
        && date_.tm_yday % 4 == 0
        && (date_.tm_yday % 100 != 0
        || date_.tm_yday % 1000 == 0)) {
      date_.tm_yday++;
    }
    // Set a unique sort value to compare dates
    sortValue_ = date_.tm_year * 1000 + date_.tm_yday;
  }
}

const void* Date::value_ptr(void) const {
  return &sortValue_;
}

bool Date::operator<(const Element &rhs) const {
  return this->sortValue_ < *static_cast<const int*>(rhs.value_ptr());
}
