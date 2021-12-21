/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// #include <string>
// #include <vector>
// #include <iostream>
// #include <cassert>

#include "element.h"

enum InheritBool{
  FALSE = 0,  //!< False
  TRUE = 1,   //!< True 
  INHERITED,  //!< Value is not stored locally but must be ascertained from parent object
  UNDEFINED   //!< Value is not set
};

class Account : public Element {
  Account             *pParent_;
  const unsigned int  sortOrder_;
  const std::string   name_;
  InheritBool         isBudgeted_;
  InheritBool         isDebitIncrease_;

 public:
  /// Default constructor function
  Account()
    : pParent_(nullptr),
      sortOrder_(0),
      name_("Undefined"),
      isBudgeted_(UNDEFINED),
      isDebitIncrease_(UNDEFINED)
    {}
  
  /// Parameterized constructor function
  Account(unsigned int  sortOrder,
          std::string   name,
          InheritBool   isBudgeted,
          InheritBool   isDebitIncrease,
          Account       *pParent = nullptr
          )
    : pParent_(pParent),
      sortOrder_(sortOrder),
      name_(name),
      isBudgeted_(isBudgeted),
      isDebitIncrease_(isDebitIncrease)
    {}
 
  // Override inherited functions
  std::string str(const unsigned int &max_characters = 12) const override {
    // Recursively find name:
    std::string fullname;
    if (pParent_ == nullptr) {
      fullname = name_;
    } else {
      fullname = pParent_->str(max_characters);
      fullname.append(":");
      fullname.append(name_);
    }

    return (fullname.length() > max_characters) 
        ? fullname.substr(fullname.length() - max_characters, std::string::npos)
        : fullname;
  }
  const void* value_ptr(void) const override {return nullptr;} // Placeholder
  bool operator<(const Element &rhs) const override;

  // Getter and Setter Functions
  InheritBool getIsBudgeted(void) {
    return isBudgeted_ == INHERITED ? pParent_->getIsBudgeted() : isBudgeted_;
  }
  InheritBool getIsDebitIncrease(void) {
    return isDebitIncrease_ == INHERITED ? pParent_->getIsDebitIncrease() : isDebitIncrease_;
  }
  void setParent(Account *pParent = nullptr) {
    pParent_ = pParent;
    return;
  };
  void setIsBudgeted(const InheritBool isBudgeted) {
    isBudgeted_ = isBudgeted;
  };
  void setIsDebitIncrease(const InheritBool isDebitIncrease) {
    isDebitIncrease_ = isDebitIncrease;
  };

};

#endif // ACCOUNT_H_
