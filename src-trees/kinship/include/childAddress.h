/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CHILDADDRESS_H_
#define CHILDADDRESS_H_

#include "kinship.h"

#include <ostream>
#include <vector>

// Forward declare template friend functions
template<typename T> class childAddress; // pre-declare the template class itself
template<typename T> std::ostream& operator<< (std::ostream& o, const childAddress<T>& x);

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
  void            *pTop_;      //!< Pointer to the class containing this class
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
  ~childAddress();

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
  childAddress& operator=(childAddress&& other) noexcept;


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
  T& dereference(unsigned int ind);
  
  /// Dereference to base class
  Child& base_deref(unsigned int ind);

  /**
   * @brief Function to notifiy the managed resource that a child object has moved
   * 
   * @param pOrig Pointer to the original child object
   * @param pNew  Pointer to the new child object
   */
  void notifyMove(T *pOrig, T *pNew); //!< @todo Check if this function is still necessary

  /**
   * @brief Function to notifiy the managed resource that a child object has been added
   * 
   * @param pNew  Pointer to the new child object
   */
  void notifyAddition(T *pNew); //!< @todo Check if this function is still necessary

  void addChild(T* pNewChild, Parent* pParent);

  void replaceChild(T* pOldChild, T* pNewChild, Parent* pParent);

  void removeChild(T* pOldChild);

  bool isContainsChild(const T* pChild) const;

  unsigned int vectorSize(void) const { return vpChildren_.size(); }

  friend std::ostream& operator<< <> (std::ostream& o, const childAddress<T>& x);

 private:
  unsigned int findChildInd(const T* pChild) const;

};

#ifndef CHILDADDRESS_TCC_
#include "childAddress.tcc"
#endif // CHILDADDRESS_TCC_

#endif // CHILDADDRESS_H_
