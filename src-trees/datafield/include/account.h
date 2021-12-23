/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
#include <vector>

#include "element.h"
#include "strings.h"
#include "accountList.h"



class Account : public Element {
  const AccountList *pAcctList_;
  unsigned int      acctListInd_ = 0;

 public:
  /// Default constructor function
  Account()
    : pAcctList_(nullptr)
    {}

  /// Parameterized constructor functions
  Account(AccountList *pAcctList);
  Account(AccountList *pAcctList, std::string str);
 
  // Override inherited functions
  std::string str(const unsigned int &max_characters = 12) const override {
    return pAcctList_->at(acctListInd_).str(max_characters);
  }
  void setFromStr(std::string str) override {
    unsigned int index = Strings::toInteger(str);
    acctListInd_ = index < pAcctList_->size() ? index : 0;
    return;
  }
  const void* value_ptr(void) const override {return nullptr;} // Placeholder
  bool operator<(const Element &rhs) const override;
};

#endif // ACCOUNT_H_
