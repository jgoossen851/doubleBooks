/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "transaction.h"

// #include <iostream>
#include <cassert>

#include "format.h"
#include "strings.h"

// ENTRY

bool Entry::operator<(const Entry &rhs) const {
  return (*this).getSortValue() < rhs.getSortValue();
}


// RECORD

int Record::getSortValue() const {
  return 17;
}

/// Create a Record
Record::Record( const unsigned int    id,
                const std::string   title,
                const int           period, // Change to class Period
                const Date          date,
                const Category      category,
                const Currency      amount,
                const std::string   vendor,
                const std::string   memo,
                const bool          isBalanced
                )
    : amount_(Currency(NEGATIVE_SIGN)) {

  id_         = id;
  title_      = title;
  period_     = period;
  date_       = date;
  category_   = category;
  amount_     = amount;
  vendor_     = vendor;
  memo_       = memo;
  isBalanced_ = isBalanced;
}

std::vector<std::string> Record::formatEntry() const {
  std::vector<std::string> strVec;
  strVec.push_back(std::to_string(id_));                      // ID
  strVec.push_back("");         // Parent
  strVec.push_back(title_);                                   // Title
  strVec.push_back(std::to_string(period_));                  // Period
  strVec.push_back(date_.str());                              // Date
  strVec.push_back(category_.getName());                      // Category
  strVec.push_back(amount_.str());                            // Amount
  strVec.push_back(vendor_);                     // Vendor
  strVec.push_back(memo_);                                    // Memo
  strVec.push_back(std::to_string(isBalanced_)); // Balanced
  assert(strVec.size() == Format<A1>::columns() && "Vector does not contain enought elements after formatting Record");
  return strVec;
}

Date        Record::getDate()         const {return date_;}
bool        Record::getIsBalanced()   const {return isBalanced_;}
std::string Record::getVendor()       const {return vendor_;}


// TRANSACTION

Transaction::Transaction(const std::vector<std::string> strVec){
  id_         = Strings::toInteger(strVec.at(DB_ID));
  vendor_     = strVec.at(DB_VENDOR);
  isBalanced_ = Strings::toInteger(strVec.at(DB_STATEMENT));
  date_.setFromStr(strVec.at(DB_DATE));
  
  addRecord(strVec);
}

bool Transaction::addRecord(const std::vector<std::string> strVec) {
  Record new_record(id_, 
                    strVec.at(DB_TITLE), 
                    Strings::toInteger(strVec.at(DB_PERIOD)), 
                    date_, 
                    Category(strVec.at(DB_CATEGORY)), 
                    Currency(strVec.at(DB_AMOUNT)), 
                    vendor_, 
                    strVec.at(DB_MEMO), 
                    isBalanced_);
  records_.push_back(new_record);
  return true;
}

std::vector<std::string> Transaction::formatEntry() const {
  std::vector<std::string> strVec;
  const int numRecords = records_.size();
  if (numRecords == 1) {
    strVec = records_.at(0).formatEntry();
    assert(strVec.size() == Format<A1>::columns() && "Vector does not contain enought elements after formatting Transaction with single Record");
  } else {
    strVec.push_back(std::to_string(id_));      // ID
    strVec.push_back("");                       // Parent
    strVec.push_back(vendor_ + " Transaction"); // Title
    strVec.push_back("");                       // Period
    strVec.push_back(date_.str());              // Date
    strVec.push_back("");                       // Category
    strVec.push_back(getAmount().str());        // Amount
    strVec.push_back("");                       // Vendor
    strVec.push_back("Containing " + std::to_string(numRecords) + " records"); // Memo
    strVec.push_back(std::to_string(isBalanced_)); // Balanced
    assert(strVec.size() == Format<A1>::columns() && "Vector does not contain enought elements after formatting Transaction with multiple Record");
  }
  return strVec;
}
