/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef PARENTADDRESS_H_
#define PARENTADDRESS_H_

#include "kinship.h"

#include <cassert>
#include <ostream>

// Forward declare template friend functions
template<typename T> class parentAddress; // pre-declare the template class itself
template<typename T> std::ostream& operator<< (std::ostream& o, const parentAddress<T>& x);

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
  void        *pTop_;     //!< Pointer to the class containing this class
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
  ~parentAddress();

  /**
   * @brief Copy Constructor Function
   *
   * The copy constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  parentAddress(const parentAddress& other) = delete;

  /// Copy Assignment Operator
  parentAddress& operator=(const parentAddress& other); //!< @todo Move this functionallity inside replaceParent(), along with functionallity from ChildOf class. Add an extra parameter for 'this' if necessary, and delete pTop_ if possible.

  /**
   * @brief Move Constructor Function
   *
   * The move constructor is deleted to ensure that this object is constructed
   * with the address set of the parent object via member pTop_.
   */
  parentAddress(parentAddress&& other) = delete;

  /// Move Assignement Operator
  parentAddress& operator=(parentAddress&& other) noexcept;


  // Parameterized Constructors
  /**
   * @brief Construct a new parentAddress object with specified pointer
   * 
   * @param pTop Pointer of the object containing the parentAddress object
   */
  parentAddress(void *pTop)
      : pTop_(pTop)
      , pParent_(nullptr) {};

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
    assert(pParent_ != nullptr && "The child object has no parent pointer saved."); 
    return *pParent_; }

  /// Overload structure dereference operator
  T* operator->() const { assert(pParent_ != nullptr); return pParent_; }

  /**
   * @brief Set the address of a parent object if the parent object does not already exist.
   *
   * If the parent object is already set, use replaceParent() instead.
   * The function checks that the parent is a nullptr or that the parent has already been set
   * to the specified address.
   * 
   * @param pNewParent  Address of the new parent to set.
   */
  void setParent(T* pNewParent); //!< @todo Use functionallity inside replaceParent

  /**
   * @brief Replace the address of an existing parent object
   * 
   * @param pNewParent  Pointer to the new parent object
   */
  void replaceParent(T* pNewParent);

  void removeParent();

  bool isValid() const;

  friend std::ostream& operator<< <> (std::ostream& o, const parentAddress<T>& x);

};

#ifndef PARENTADDRESS_TCC_
#include "parentAddress.tcc"
#endif // PARENTADDRESS_TCC_

#endif // PARENTADDRESS_H_
