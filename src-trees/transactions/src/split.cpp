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
  assert(getParentPtr() != nullptr);
  return name_.str() == "" ? (getParentPtr()->getName()) : name_;
}

StringField Split::getMemo() const {
  assert(getParentPtr() != nullptr);
  return memo_.str() == "" ? (getParentPtr()->getMemo()) : memo_;
}

StringField Split::getPeriod() const {
  assert(getParentPtr() != nullptr);
  return period_.str() == "" ? (getParentPtr()->getPeriod()) : period_;
}

Date Split::getDate() const {
  assert(getParentPtr() != nullptr);
  return date_ == Date() ? (getParentPtr()->getDate()) : date_;
}

StringField Split::getVendor() const {
  assert(getParentPtr() != nullptr);
  return vendor_.str() == "" ? (getParentPtr()->getVendor()) : vendor_;
}
