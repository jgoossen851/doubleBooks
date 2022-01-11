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
              InheritBool   isDebitIncrease
              );

  /// Copy Constructor [deleted]
  AccountEntry(const AccountEntry& rhs) = delete;

  /// Move Constructor
  AccountEntry(AccountEntry&& rhs) noexcept = default;

  /// Move Assignment Operator
  AccountEntry& operator=(AccountEntry&& other) noexcept = default;

  /// Copy Assignment Operator [deleted]
  AccountEntry& operator=(const AccountEntry&) = delete;
 
  std::string str(const unsigned int &max_characters = 12) const;

  // Getter and Setter Functions
  InheritBool getIsBudgeted(void) const;
  InheritBool getIsDebitIncrease(void) const;
  void setIsBudgeted(const InheritBool isBudgeted);
  void setIsDebitIncrease(const InheritBool isDebitIncrease);

};

// Forward declare AccountList
class AccountList;
// Declare base class for child accounts
class ChildAccount : public childOf<AccountList> {};

class AccountList : public parentOf<ChildAccount> {
  std::vector<AccountEntry> vAcctEntries_;

 public:
  /// Default Constructor Function
  AccountList();
  /// Parameterized Constructor Function
  AccountList(const char *accountsCsv);
  /// Move Constructor
  AccountList(AccountList&& rhs) noexcept = default;
  /// Move Assignment Operator
  AccountList& operator=(AccountList&& other) noexcept = default;

  void load(const char *accountsCsv);

  const AccountEntry& at(unsigned int ind = 0) const;
  unsigned int size(void) const;
};

#endif // ACCOUNTLIST_H_
