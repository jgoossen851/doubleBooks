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



class Account : public Element, public ChildAccount {
  unsigned int      acctListInd_ = 0;

 public:
  /// Default constructor function
  Account() {}

  /// Parameterized constructor functions
  Account(AccountList *pAcctList);
  Account(AccountList *pAcctList, std::string str);
 
  /**
   * @brief Displays account name as a string.
   * 
   * @param max_characters Max displayable characters in name
   * @return PrettyString  String containing account name. Note: may be longer than displayable character length due to formatting characters.
   */
  PrettyString str(const unsigned int &max_characters = 12) const override;
  void setFromStr(std::string str) override {
    unsigned int index = Strings::toInteger(str);
    acctListInd_ = index < getParentPtr()->size() ? index : 0;
    return;
  }
  const void* value_ptr(void) const override {return nullptr;} // Placeholder
  bool operator<(const Element &rhs) const override;

  unsigned int getAccountInd(void) const {
    return acctListInd_;
  };
};

#endif // ACCOUNT_H_
