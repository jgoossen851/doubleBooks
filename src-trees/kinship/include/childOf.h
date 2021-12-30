/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CHILDOF_H_
#define CHILDOF_H_

#include "kinship.h"
#include "parentAddress.h"

/**
 * @brief Class that contains a reference to a parent
 * 
 * @note: The class cannot be copy constructed
 * or move constructed due to the limitations of the member mParentAddr_.
 */
template<typename T>
class childOf : public Child {
  parentAddress<T> mParentAddr_;

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  childOf()
      : mParentAddr_(this, nullptr) {};
  /// Destructor function
  ~childOf() = default;
  /// Copy Assignment Operator
  childOf& operator=(const childOf& other) = default;
  /// Move Assignement Operator
  childOf& operator=(childOf&& other) = default;

  void setParent(Parent* pNewParent) override {
    mParentAddr_.setParent(static_cast<T*>(pNewParent));
    if (mParentAddr_.isValid()) {
      if (! mParentAddr_->isContainsChild(this)) {
        mParentAddr_->addChild(this);
      }
    }
  }

  void replaceParent(Parent* pNewParent) override {
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

  void removeParent() override {
    if (mParentAddr_.isValid()) {
      if (mParentAddr_->isContainsChild(this)) {
        mParentAddr_->removeChild(this);
      }
    }
    mParentAddr_.removeParent();
  }

  T* getParentPtr() const {
    return &(*mParentAddr_);
  }

};

#endif // CHILDOF_H_
