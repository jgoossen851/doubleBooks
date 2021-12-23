/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "split.h"

#include <cassert>

#include "transaction.h"

std::string Split::getName() const {
  assert(pParent_ != nullptr);
  return name_ == "" ? (pParent_->getName()) : name_;
};

std::string Split::getMemo() const {
  assert(pParent_ != nullptr);
  return memo_ == "" ? (pParent_->getMemo()) : memo_;
};

std::string Split::getPeriod() const {
  assert(pParent_ != nullptr);
  return period_ == "" ? (pParent_->getPeriod()) : period_;
};

Date Split::getDate() const {
  assert(pParent_ != nullptr);
  return date_ == Date() ? (pParent_->getDate()) : date_;
};

std::string Split::getVendor() const {
  assert(pParent_ != nullptr);
  return vendor_ == "" ? (pParent_->getVendor()) : vendor_;
};

