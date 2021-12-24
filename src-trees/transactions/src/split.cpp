/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "split.h"

#include <cassert>

#include "transaction.h"

StringField Split::getName() const {
  assert(pParent_ != nullptr);
  return name_.str() == "" ? (pParent_->getName()) : name_;
}

StringField Split::getMemo() const {
  assert(pParent_ != nullptr);
  return memo_.str() == "" ? (pParent_->getMemo()) : memo_;
}

StringField Split::getPeriod() const {
  assert(pParent_ != nullptr);
  return period_.str() == "" ? (pParent_->getPeriod()) : period_;
}

Date Split::getDate() const {
  assert(pParent_ != nullptr);
  return date_ == Date() ? (pParent_->getDate()) : date_;
}

StringField Split::getVendor() const {
  assert(pParent_ != nullptr);
  return vendor_.str() == "" ? (pParent_->getVendor()) : vendor_;
}

void Split::setParentTransaction(Transaction *testTransaction) {
  pParent_ = testTransaction;
  pParent_->addChildSplit(this);
}
