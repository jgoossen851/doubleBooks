/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#define CHILDADDRESS_TCC_
#include "childAddress.h"

#include "kinship.h"

#include <algorithm>
#include <cassert>
#include <vector>

/// Destructor function
template<typename T>
childAddress<T>::~childAddress() {
  for (auto itr = vpChildren_.begin(); itr < vpChildren_.end(); itr++) {
    if (*itr != nullptr) {
      (*itr)->removeParent();
    }
  }
}

/// Move Assignement Operator
template<typename T>
childAddress<T>& childAddress<T>::operator=(childAddress&& other) noexcept {
  // Move the internal memory
  vpChildren_ = std::move(other.vpChildren_);
  /// @todo Check if these should use the notify functions from 'parentAddress'
  // For each child, update the parent.
  for (auto itr = vpChildren_.begin(); itr < vpChildren_.end(); itr++) {
    if (*itr != nullptr) {
      // (*itr)->replaceParent(static_cast<Parent*>(pTop_));
      uint ind = std::distance(vpChildren_.begin(), itr);
      vpChildren_.at(ind)->replaceParent(static_cast<Parent*>(pTop_));
    }
  }
  other.vpChildren_ = std::vector<T*>();
  return *this;
}

/// Indexed dereference operator
template<typename T>
T& childAddress<T>::dereference(uint ind) const {
  assert(ind < vpChildren_.size() && "Attempting to dereference an element beyond the current contents of the vector.");
  assert(vpChildren_.at(ind) != nullptr && "Attempting to dereference a nullptr.");
  return *vpChildren_.at(ind);
}

template<typename T>
void childAddress<T>::addChild(T* pNewChild, Parent* pParent) {
  // Add a child, replacing nullptr if found
  uint ind = findChildInd(nullptr);
  if (ind == vpChildren_.size()) {
    vpChildren_.push_back(pNewChild);
  } else {
    vpChildren_.at(ind) = pNewChild;
  }
  // Set the the child's parent to this object's container
  if (vpChildren_.at(ind) != nullptr) {
    vpChildren_.at(ind)->setParent(pParent);
  }
}

template<typename T>
void childAddress<T>::replaceChild(T* pOldChild, T* pNewChild, Parent* pParent) {
  uint ind = findChildInd(pOldChild);
  if (vpChildren_.at(ind) != nullptr) {
    assert(ind != vpChildren_.size() && "Child pointer not found inside parent class");
  }
  vpChildren_.at(ind) = pNewChild;
  // Set parent of new child
  if (vpChildren_.at(ind) != nullptr) {
    vpChildren_.at(ind)->setParent(pParent);
  }
  // Remove parent from old child (after removed from vector to avoid vector resize)
  if (pOldChild != nullptr) {
    pOldChild->removeParent();
  }
}

template<typename T>
void childAddress<T>::removeChild(T* pOldChild) {
  uint ind = findChildInd(pOldChild);
  assert(ind != vpChildren_.size() && "Child pointer not found inside parent class");
  // Replace the child to delete with the last child and delete last child
  vpChildren_.at(ind) = vpChildren_.back();
  vpChildren_.pop_back();
  // Remove parent from old child
  if (pOldChild != nullptr) {
    pOldChild->removeParent();
  }
}

template<typename T>
bool childAddress<T>::isContainsChild(const T* pChild) const {
  auto itr = std::find(vpChildren_.begin(), vpChildren_.end(), pChild);
  return itr != vpChildren_.end();
}

template<typename T>
unsigned int childAddress<T>::vectorSize(void) const {
  return (vpChildren_.size() == 1 && vpChildren_.at(0) == nullptr)
    ? 0
    : vpChildren_.size();
}

template<typename T>
std::ostream& operator<< (std::ostream& o, const childAddress<T>& x) {
  o << "[";
  for (auto itr = x.vpChildren_.begin(); itr < x.vpChildren_.end(); itr++) {
    if (itr > x.vpChildren_.begin()) { o << ", "; }
    o << *itr;
  }
  return o << "]";
}

template<typename T>
uint childAddress<T>::findChildInd(const T* pChild) const {
  auto itr = std::find(vpChildren_.begin(), vpChildren_.end(), pChild);
  return std::distance(vpChildren_.begin(), itr);
}