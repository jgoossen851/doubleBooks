/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#define PARENTADDRESS_TCC_
#include "parentAddress.h"

#include "kinship.h"

#include <cassert>

template<typename T>
parentAddress<T>::~parentAddress() {
  if (pParent_ != nullptr) {
    if ( pParent_->isContainsChild(static_cast<const Child*>(pTop_))) {
      pParent_->removeChild(static_cast<Child*>(pTop_));
    }
  }
}

template<typename T>
parentAddress<T>& parentAddress<T>::operator=(const parentAddress& other) {
  replaceParent(other.pParent_);
  if (! pParent_->isContainsChild(static_cast<const Child*>(pTop_))) {
    pParent_->addChild(static_cast<Child*>(pTop_));
  }
  return *this;
} //!< @todo Move this functionallity inside replaceParent(), along with functionallity from ChildOf class. Add an extra parameter for 'this' if necessary, and delete pTop_ if possible.

template<typename T>
parentAddress<T>& parentAddress<T>::operator=(parentAddress&& other) {
  replaceParent(other.pParent_);
  if (! pParent_->isContainsChild(static_cast<const Child*>(pTop_))) {
    pParent_->addChild(static_cast<Child*>(pTop_));
  }
  if ( other.pParent_->isContainsChild(static_cast<const Child*>(other.pTop_))) {
    other.pParent_->removeChild(static_cast<Child*>(other.pTop_));
  }
  return *this;
}

template<typename T>
void parentAddress<T>::notifyMove(T *pOrig, T *pNew) {
  assert(pParent_ == pOrig);
  pParent_ = pNew;
} //!< @todo Check if this function is still necessary

template<typename T>
void parentAddress<T>::setParent(T* pNewParent) {
  assert(pParent_ == nullptr || pParent_ == pNewParent);
  pParent_ = pNewParent;
} //!< @todo Use functionallity inside replaceParent

template<typename T>
void parentAddress<T>::replaceParent(T* pNewParent) {
  pParent_ = pNewParent;
}

template<typename T>
void parentAddress<T>::removeParent() {
  pParent_ = nullptr;
}

template<typename T>
bool parentAddress<T>::isValid() const {
  return pParent_ != nullptr;
}

template<typename T>
std::ostream& operator<< (std::ostream& o, const parentAddress<T>& x) {
  return o << x.pParent_;
}
