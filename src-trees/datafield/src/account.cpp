/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "account.h"

#include "ansi.h"
#include "prettyString.h"

bool Account::operator<(const Element &rhs) const {
  return *(static_cast<const int*>(this->value_ptr())) < *(static_cast<const int*>(rhs.value_ptr()));
}


/// Parameterized constructor functions
  Account::Account(AccountList *pAcctList) {
    setParent(pAcctList);
  }

  Account::Account(AccountList *pAcctList, std::string str) {
    setParent(pAcctList);
    setFromStr(str);
  }

PrettyString Account::str(const unsigned int &max_characters) const {
  if (getParentPtr() == nullptr) {
    PrettyString ansiDim(ansi::DIM, 4);
    PrettyString ansiNormal(ansi::NORMAL, 5);
    PrettyString undefString = ansiDim + "Undefined" + ansiNormal;
    return undefString;
  } else {
    return PrettyString(getParentPtr()->at(acctListInd_).str(max_characters), 0);
  }
}
