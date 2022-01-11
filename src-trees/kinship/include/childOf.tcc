/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#define CHILDOF_TCC_
#include "childOf.h"

#include "kinship.h"
#include "parentAddress.h"

template<typename T>
void childOf<T>::setParent(Parent* pNewParent) {
  mParentAddr_.setParent(static_cast<T*>(pNewParent));
  if (mParentAddr_.isValid()) {
    if (! mParentAddr_->isContainsChild(this)) {
      mParentAddr_->addChild(this);
    }
  }
}

template<typename T>
void childOf<T>::replaceParent(Parent* pNewParent) {
  if (mParentAddr_.isValid()) {
    if (mParentAddr_->isContainsChild(this)) {
      mParentAddr_->removeChild(this);
    }
  }
  mParentAddr_.replaceParent(static_cast<T*>(pNewParent));
  if (mParentAddr_.isValid()) {
    if (! mParentAddr_->isContainsChild(this)) {
      mParentAddr_->addChild(this);
    }
  }
}

template<typename T>
void childOf<T>::removeParent() {
  if (mParentAddr_.isValid()) {
    if (mParentAddr_->isContainsChild(this)) {
      mParentAddr_->removeChild(this);
    }
  }
  mParentAddr_.removeParent();
}

template<typename T>
T* childOf<T>::getParentPtr() const {
  if ( ! mParentAddr_.isValid()) { return nullptr; }
  return &(*mParentAddr_);
}
