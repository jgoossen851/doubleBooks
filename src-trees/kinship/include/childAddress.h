/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CHILDADDRESS_H_
#define CHILDADDRESS_H_

#include "kinship.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

/**
 * @brief Class to manage the address of the object with the parent relationship
 *
 * The class contains a pointer to the parent object that will be updated when the
 * parent object moves.
 * 
 * @tparam T  The type of the parent object
 */
template<typename T>
class childAddress {
  const void      *pTop_;      //!< Pointer to the class containing this class
  std::vector<T*> vpChildren_; //!< Vector of pointer to the children objects under the managed relationship

 public:
  // Define the 6 special member functions
  /**
   * @brief Default Constructor Function
   *
   * The default constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  childAddress() = delete;

  /// Destructor function
  ~childAddress() = default;

  /**
   * @brief Copy Constructor Function
   *
   * The copy constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  childAddress(const childAddress& other) = delete;

  /**
   * @brief Copy Assignment Operator
   *
   * The copy assignment operator is deleted to ensure that the children
   * referenced by vpChildren_ only need to maintain a relationship with
   * one parent. Copying the parent would require children to maintain
   * relationship with both copies.
   */
  childAddress& operator=(const childAddress& other) = delete;

  /**
   * @brief Move Constructor Function
   *
   * The move constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  childAddress(childAddress&& other) = delete;

  /// Move Assignement Operator
  childAddress& operator=(childAddress&& other) = default;


  // Parameterized Constructors
  /**
   * @brief Construct a new childAddress object with specified pointer
   * 
   * @param pTop Pointer of the object containing the childAddress object
   */
  childAddress(void *pTop)
      : pTop_(pTop) {};

  /**
   * @brief Construct a new childAddress object with specified pointer and initialized child object
   * 
   * @param pTop Pointer of the object containing the childAddress object
   * @param init Pointer of the managed parent object
   */
  childAddress(void *pTop, T *init)
      : pTop_(pTop)
      , vpChildren_(std::vector<T*>()) {
    vpChildren_.push_back(init);
  };

  /// Indexed dereference operator
  T& dereference(uint ind) {
    assert(ind < vpChildren_.size());
    return *vpChildren_.at(ind);
  }

  /// Dereference to base class
  Child& base_deref(uint ind) {
    return dereference(ind);
  }

  /**
   * @brief Function to notifiy the managed resource that a child object has moved
   * 
   * @param pOrig Pointer to the original child object
   * @param pNew  Pointer to the new child object
   */
  void notifyMove(T *pOrig, T *pNew) {
    uint ind = findChildInd(pOrig);
    vpChildren_.at(ind) = pNew;
  } //!< @todo Check if this function is still necessary

  /**
   * @brief Function to notifiy the managed resource that a child object has been added
   * 
   * @param pNew  Pointer to the new child object
   */
  void notifyAddition(T *pNew) {
    vpChildren_.push_back(pNew);
  } //!< @todo Check if this function is still necessary

  void addChild(T* pNewChild, Parent* pParent) {
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

  void replaceChild(T* pOldChild, T* pNewChild, Parent* pParent) {
    uint ind = findChildInd(pOldChild);
    if (vpChildren_.at(ind) != nullptr) {
      assert(ind != vpChildren_.size());
    }
    // Remove parent from old child
    vpChildren_.at(ind)->removeParent();
    vpChildren_.at(ind) = pNewChild;
    // Set parent of new child
    if (vpChildren_.at(ind) != nullptr) {
      vpChildren_.at(ind)->setParent(pParent);
    }
  }

  void removeChild(T* pOldChild) {
    uint ind = findChildInd(pOldChild);
    assert(ind != vpChildren_.size());
    // Replace the child to delete with the last child and delete last child
    vpChildren_.at(ind) = vpChildren_.back();
    vpChildren_.pop_back();
    // Remove parent from old child
    if (pOldChild != nullptr) {
      pOldChild->removeParent();
    }
  }

  bool isContainsChild(const T* pChild) const {
    auto itr = std::find(vpChildren_.begin(), vpChildren_.end(), pChild);
    return itr != vpChildren_.end();
  }

  uint vectorSize(void) const {
    return vpChildren_.size();
  }

 private:
  uint findChildInd(const T* pChild) const {
    auto itr = std::find(vpChildren_.begin(), vpChildren_.end(), pChild);
    return std::distance(vpChildren_.begin(), itr);
  }

};

#endif // CHILDADDRESS_H_
