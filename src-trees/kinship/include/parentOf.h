/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PARENTOF_H_
#define PARENTOF_H_

#include "childAddress.h"
#include "kinship.h"

/**
 * @brief Class that contains references to children objects
 * 
 * @note: The class cannot be copy constructed, copy assigned,
 * or move constructed due to the limitations of the member mChildAddr_.
 */
template<typename T>
class parentOf : public Parent {
  childAddress<T> mChildAddr_;

 public:
  // Define the 6 special member functions
  /// Default Constructor Function
  parentOf()
      : mChildAddr_(this, nullptr) {};
  /// Destructor function
  ~parentOf() = default;
  /// Move Assignement Operator
  parentOf& operator=(parentOf&& other) noexcept {
    mChildAddr_ = std::move(other.mChildAddr_);
    return *this;
  }
  /// Move Constructor
  parentOf(parentOf&& other) noexcept
      : mChildAddr_(this, nullptr) {
    mChildAddr_ = std::move(other.mChildAddr_);
  }

  void addChild(Child* pNewChild) override;

  void replaceChild(Child* pOldChild, Child* pNewChild) override;

  void removeChild(Child* pOldChild) override;

  bool isContainsChild(const Child* pChild) const override;

  T* getChildPtr(const uint iChild);

  /**
   * @brief Gets the number of children in the vector of pointers for the parent object
   * 
   * If the vector only contains a nullptr (i.e., an invalid child object), this function
   * will return 1, as the vector length is 1. However, this should not be counted on
   * as the functionallity may change to reflect that the parent object has no valid children.
   */
  uint getNumChildren(void) const;

};

#ifndef PARENTOF_TCC_
#include "parentOf.tcc"
#endif // PARENTOF_TCC_

#endif // PARENTOF_H_
