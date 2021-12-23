/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "account.h"

bool Account::operator<(const Element &rhs) const {
  return *(static_cast<const int*>(this->value_ptr())) < *(static_cast<const int*>(rhs.value_ptr()));
}


/// Parameterized constructor functions
  Account::Account(AccountList *pAcctList)
      : pAcctList_(pAcctList)
      {}

  Account::Account(AccountList *pAcctList, std::string str)
      : pAcctList_(pAcctList)
      {
    setFromStr(str);
  }