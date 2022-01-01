/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ACCOUNTLIST_H_
#define ACCOUNTLIST_H_

#include <cassert>
#include <string>
#include <vector>

#include "parentOf.h"
#include "childOf.h"

enum InheritBool{
  FALSE = 0,  //!< False
  TRUE = 1,   //!< True 
  INHERITED,  //!< Value is not stored locally but must be ascertained from parent object
  UNDEFINED   //!< Value is not set
};

class AccountEntry : public parentOf<AccountEntry>, public childOf<AccountEntry> {
  // AccountEntry                *pParent_; //!< @todo Change to Smart pointers?
  // std::vector<AccountEntry*>  vpChildren_;
  unsigned int                sortOrder_;
  std::string                 name_;
  InheritBool                 isBudgeted_;
  InheritBool                 isDebitIncrease_;

 public:
  /// Default constructor function
  AccountEntry();
  
  /// Parameterized constructor function
  AccountEntry(unsigned int  sortOrder,
              std::string   name,
              InheritBool   isBudgeted,
              InheritBool   isDebitIncrease//,
              // AccountEntry  *pParent = nullptr
              );

  /// Copy Constructor
  AccountEntry(const AccountEntry& rhs) = delete;

  // /// Move Constructor
  // AccountEntry(AccountEntry&& rvalue)
  //     : pParent_(rvalue.pParent_)
  //     , sortOrder_(rvalue.sortOrder_)
  //     , name_(rvalue.name_)
  //     , isBudgeted_(rvalue.isBudgeted_)
  //     , isDebitIncrease_(rvalue.isDebitIncrease_) {

  //   // Let children know I've moved. This also updates this->vpChildren
  //   for (auto itr = vpChildren_.begin(); itr < vpChildren_.end(); itr++) {
  //     (*itr)->setParentEntry(this);
  //   }

  //   // Clear rvalue resources
  //   rvalue.pParent_ = nullptr;
  //   rvalue.isBudgeted_ = UNDEFINED;
  //   rvalue.isDebitIncrease_ = UNDEFINED;
  // }

  /// Move Assignment Operator
  AccountEntry& operator=(AccountEntry&& other) = default;

  // /// Move Assignment Operator
  // AccountEntry& operator=(AccountEntry&& rvalue) {

  //   if (this != &rvalue) { // Prevent self-assignment

  //     // Do shallow copy (I'm assuming Move Constructor will be called to set consts.)
  //     pParent_ = rvalue.pParent_;
  //     sortOrder_ = rvalue.sortOrder_;
  //     name_ = rvalue.name_;
  //     isBudgeted_ = rvalue.isBudgeted_;
  //     isDebitIncrease_ = rvalue.isDebitIncrease_;

  //     // Let children know I've moved. This also updates this->vpChildren
  //     for (auto itr = vpChildren_.begin(); itr < vpChildren_.end(); itr++) {
  //       (*itr)->setParentEntry(this);
  //     }

  //     // Clear rvalue resources
  //     rvalue.pParent_ = nullptr;
  //     rvalue.isBudgeted_ = UNDEFINED;
  //     rvalue.isDebitIncrease_ = UNDEFINED;

  //   }

  //   return *this;
  // }

  /// Copy Assignment Operator [deleted]
  AccountEntry& operator=(const AccountEntry&) = delete;
 
  std::string str(const unsigned int &max_characters = 12) const;

  // Getter and Setter Functions
  InheritBool getIsBudgeted(void) const;
  InheritBool getIsDebitIncrease(void) const;
  void setIsBudgeted(const InheritBool isBudgeted);
  void setIsDebitIncrease(const InheritBool isDebitIncrease);
  // void setParentEntry(AccountEntry *pParent);

 private:
  // void addChildEntry(AccountEntry *pChild);

};


class AccountList {
  std::vector<AccountEntry> vAcctEntries_;

 public:
  // Default Constructor Function
  AccountList();
  // Parameterized Constructor Function
  AccountList(const char *accountsCsv);

  void load(const char *accountsCsv);

  const AccountEntry& at(unsigned int ind = 0) const;
  unsigned int size(void) const;
};

#endif // ACCOUNTLIST_H_
