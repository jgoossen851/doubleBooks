/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "account.h"

#include "ansi.h"

bool Account::operator<(const Element &rhs) const {
  return *(static_cast<const int*>(this->value_ptr())) < *(static_cast<const int*>(rhs.value_ptr()));
}


/// Parameterized constructor functions
  Account::Account(const AccountList *pAcctList)
      : pAcctList_(pAcctList)
      {}

  Account::Account(const AccountList *pAcctList, std::string str)
      : pAcctList_(pAcctList)
      {
    setFromStr(str);
  }

std::string Account::str(const unsigned int &max_characters) const {
  return pAcctList_ == nullptr ? ansi::DIM + "Undefined" + ansi::NORMAL
                                : pAcctList_->at(acctListInd_).str(max_characters);
}
