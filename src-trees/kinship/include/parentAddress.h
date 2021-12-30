/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PARENTADDRESS_H_
#define PARENTADDRESS_H_

#include <cassert>
#include <iostream>
#include <string>

/**
 * @brief Class to manage the address of the object with the parent relationship
 *
 * The class contains a pointer to the parent object that will be updated when the
 * parent object moves.
 * 
 * @tparam T  The type of the parent object
 */
template<typename T>
class parentAddress {
  const void  *pTop_;     //!< Pointer to the class containing this class
  T           *pParent_;  //!< Pointer to the parent object under the managed relationship

 public:
  // Define the 6 special member functions
  /**
   * @brief Default Constructor Function
   *
   * The default constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  parentAddress() = delete;

  /// Destructor function
  ~parentAddress() = default;

  /**
   * @brief Copy Constructor Function
   *
   * The copy constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  parentAddress(const parentAddress& other) = delete;

  /// Copy Assignment Operator
  parentAddress& operator=(const parentAddress& other) = default;

  /**
   * @brief Move Constructor Function
   *
   * The move constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  parentAddress(parentAddress&& other) = delete;

  /// Move Assignement Operator
  parentAddress& operator=(parentAddress&& other) = default;


  // Parameterized Constructors
  /**
   * @brief Construct a new parentAddress object with specified pointer
   * 
   * @param pTop Pointer of the object containing the parentAddress object
   */
  parentAddress(void *pTop)
      : pTop_(pTop) {};

  /**
   * @brief Construct a new parentAddress object with specified pointer and initialized parent object
   * 
   * @param pTop Pointer of the object containing the parentAddress object
   * @param init Pointer of the managed parent object
   */
  parentAddress(void *pTop, T *init)
      : pTop_(pTop)
      , pParent_(init) {};


  /// Overload dereference operator
  T& operator*() const {
    return *pParent_;
  }

  /// Overload structure dereference operator
  T* operator->() const {
    return pParent_;
  }

  /**
   * @brief Function to notifiy the managed resource that the parent object has moved
   * 
   * @param pOrig Pointer to the original parent object
   * @param pNew  Pointer to the new parent object
   */
  void notifyMove(T *pOrig, T *pNew) {
    assert(pParent_ == pOrig);
    pParent_ = pNew;
  }

  void setParent(T& pNewParent) {
    assert(pParent_ == nullptr);
    pParent_ = &pNewParent;
  }

  void replaceParent(T& pNewParent) {
    pParent_ = &pNewParent;
  }

  void removeParent() {
    pParent_ = nullptr;
  }

};

#endif // PARENTADDRESS_H_
