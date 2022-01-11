/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#define PARENTOF_TCC_
#include "parentOf.h"

#include "childAddress.h"
#include "kinship.h"

template<typename T>
void parentOf<T>::addChild(Child* pNewChild) {
  mChildAddr_.addChild(static_cast<T*>(pNewChild), this);
}

template<typename T>
void parentOf<T>::replaceChild(Child* pOldChild, Child* pNewChild) {
  mChildAddr_.replaceChild(static_cast<T*>(pOldChild), static_cast<T*>(pNewChild), this);
}

template<typename T>
void parentOf<T>::removeChild(Child* pOldChild) {
  mChildAddr_.removeChild(static_cast<T*>(pOldChild));
}

template<typename T>
bool parentOf<T>::isContainsChild(const Child* pChild) const {
  return mChildAddr_.isContainsChild(static_cast<const T*>(pChild));
}

template<typename T>
T* parentOf<T>::getChildPtr(const uint iChild) const {
  return &(mChildAddr_.dereference(iChild));
}

template<typename T>
uint parentOf<T>::getNumChildren(void) const {
  return mChildAddr_.vectorSize();
}
