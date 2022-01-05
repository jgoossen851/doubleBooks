/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "transaction.h"
#include "split.h"

Currency Transaction::getDebitSum() const { 
  Currency sum(0);
  for (uint ii = 0; ii < getNumChildren(); ii++) {
    sum += getChildPtr(ii)->getDebitSum();
  }
  return sum;
}

Currency Transaction::getCreditSum() const { 
  Currency sum(0);
  for (uint ii = 0; ii < getNumChildren(); ii++) {
    sum += getChildPtr(ii)->getCreditSum();
  }
  return sum;
}

Account Transaction::getCreditAccount(void) const {
  return getNumChildren() == 1 ? getChildPtr(0)->getCreditAccount() : Account();
}

Account Transaction::getDebitAccount(void) const {
  return getNumChildren() == 1 ? getChildPtr(0)->getDebitAccount() : Account();
}
