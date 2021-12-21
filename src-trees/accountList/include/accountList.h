/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ACCOUNTLIST_H_
#define ACCOUNTLIST_H_

#include <string>
#include <vector>

enum InheritBool{
  FALSE = 0,  //!< False
  TRUE = 1,   //!< True 
  INHERITED,  //!< Value is not stored locally but must be ascertained from parent object
  UNDEFINED   //!< Value is not set
};

class AccountEntry {
  AccountEntry        *pParent_;
  const unsigned int  sortOrder_;
  const std::string   name_;
  InheritBool         isBudgeted_;
  InheritBool         isDebitIncrease_;

 public:
  /// Default constructor function
  AccountEntry();
  
  /// Parameterized constructor function
  AccountEntry(unsigned int  sortOrder,
              std::string   name,
              InheritBool   isBudgeted,
              InheritBool   isDebitIncrease,
              AccountEntry  *pParent = nullptr
              );
 
  std::string str(const unsigned int &max_characters = 12) const;

  // Getter and Setter Functions
  InheritBool getIsBudgeted(void);
  InheritBool getIsDebitIncrease(void);
  void setParent(AccountEntry *pParent = nullptr);
  void setIsBudgeted(const InheritBool isBudgeted);
  void setIsDebitIncrease(const InheritBool isDebitIncrease);
};


class AccountList {
  std::vector<AccountEntry> vAcctEntries_;

 public:
  // Default Constructor Function
  AccountList();
  // Parameterized Constructor Function
  AccountList(const char *accountsCsv);

  void load(const char *accountsCsv);

  AccountEntry at(unsigned int ind = 0) const;
  unsigned int size(void) const;
};

#endif // ACCOUNTLIST_H_
