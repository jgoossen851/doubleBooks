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
  childOf& operator=(childOf&& other) noexcept {
    mParentAddr_ = std::move(other.mParentAddr_);
    return *this;
  }
  /// Move Constructor
  childOf(childOf&& other) noexcept
      : mParentAddr_(this, nullptr) {
    mParentAddr_ = std::move(other.mParentAddr_);
  };
  /// Copy Constructor
  childOf(const childOf& other)
      : mParentAddr_(this, nullptr) {
    mParentAddr_ = other.mParentAddr_;
  };

  void setParent(Parent* pNewParent) override;

  /**
   * @brief Replaces the current child's parent with a new parent
   *
   * Also removes the child from the list of children managed by the
   * original parent object and adds the child to the list managed
   * by the new parent object.
   * The other children of the old parent are unaffected.
   * 
   * @param pNewParent Pointer of the new parent object
   */
  void replaceParent(Parent* pNewParent) override;

  void removeParent() override;

  T* getParentPtr() const;

};

#ifndef CHILDOF_TCC_
#include "childOf.tcc"
#endif // CHILDOF_TCC_

#endif // CHILDOF_H_
