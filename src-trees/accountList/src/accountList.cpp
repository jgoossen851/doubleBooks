/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "accountList.h"

#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

#include "csv.h"
#include "strings.h"

/// Default constructor function
AccountEntry::AccountEntry()
    : pParent_(nullptr),
      sortOrder_(0),
      name_("Undefined"),
      isBudgeted_(UNDEFINED),
      isDebitIncrease_(UNDEFINED)
    {}
  
/// Parameterized constructor function
AccountEntry::AccountEntry( unsigned int  sortOrder,
                            std::string   name,
                            InheritBool   isBudgeted,
                            InheritBool   isDebitIncrease,
                            AccountEntry  *pParent
                            )
    : pParent_(pParent),
      sortOrder_(sortOrder),
      name_(name),
      isBudgeted_(isBudgeted),
      isDebitIncrease_(isDebitIncrease)
    {}
 
std::string AccountEntry::str(const unsigned int &max_characters) const {
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

// Getter and Setter Functions
InheritBool AccountEntry::getIsBudgeted(void) {
  return isBudgeted_ == INHERITED ? pParent_->getIsBudgeted() : isBudgeted_;
}
InheritBool AccountEntry::getIsDebitIncrease(void) {
  return isDebitIncrease_ == INHERITED ? pParent_->getIsDebitIncrease() : isDebitIncrease_;
}
void AccountEntry::setParent(AccountEntry *pParent) {
  pParent_ = pParent;
  return;
}
void AccountEntry::setIsBudgeted(const InheritBool isBudgeted) {
  isBudgeted_ = isBudgeted;
}
void AccountEntry::setIsDebitIncrease(const InheritBool isDebitIncrease) {
  isDebitIncrease_ = isDebitIncrease;
}



// Default Constructor Function
AccountList::AccountList(){}
// Parameterized Constructor Function
AccountList::AccountList(const char *accountsCsv){
  load(accountsCsv);
}

void AccountList::load(const char *accountsCsv){
  constexpr unsigned int NUM_KNOWN_COLS       = 6;
  constexpr unsigned int ENTRY_ID             = 0;
  constexpr unsigned int PARENT_ID            = 1;
  constexpr unsigned int ACCOUNT_NAME         = 2;
  constexpr unsigned int ACCOUNT_SORT_ORDER   = 3;
  constexpr unsigned int IS_BUDGETED          = 4;
  constexpr unsigned int IS_DEBIT_INCREASE    = 5;

  // Initialize Accounts from CSV
  Csv csv(accountsCsv);
  StringDatabase strDat = csv.load();
  assert(strDat.number_of_columns == NUM_KNOWN_COLS);
  unsigned int numAccounts = strDat.body.size();

  // Clear and place invalid entry at position 0 in vector of account entries
  vAcctEntries_.clear();
  vAcctEntries_.push_back(AccountEntry(-1, "Undefined", UNDEFINED, UNDEFINED));

  // Load data into vector of Account Entries
  std::vector<int> vAcctIds;
  std::vector<int> vAcctParentIds;
  for (unsigned int iAct = 0; iAct < numAccounts; iAct++) {
    vAcctIds.push_back(Strings::toInteger(strDat.at(iAct, ENTRY_ID)));
    vAcctParentIds.push_back(Strings::toInteger(strDat.at(iAct, PARENT_ID)));

    InheritBool isBudgeted = Strings::isInteger(strDat.at(iAct, IS_BUDGETED)) 
        ? (Strings::toInteger(strDat.at(iAct, IS_BUDGETED)) == 0 ? FALSE : TRUE)
        : UNDEFINED;
    InheritBool isDebitIncrease = Strings::isInteger(strDat.at(iAct, IS_DEBIT_INCREASE)) 
        ? (Strings::toInteger(strDat.at(iAct, IS_DEBIT_INCREASE)) == 0 ? FALSE : TRUE)
        : UNDEFINED;

    vAcctEntries_.push_back(AccountEntry(
        Strings::toInteger(strDat.at(iAct, ACCOUNT_SORT_ORDER)),
        strDat.at(iAct, ACCOUNT_NAME),
        isBudgeted,
        isDebitIncrease
    ));
  }
  
  // Find account ancestors
  for (unsigned int iAct = 0; iAct < numAccounts; iAct++) {
    // Find the index of the parent account
    auto parentInd = std::find(vAcctIds.begin(), vAcctIds.end(), vAcctParentIds.at(iAct));
    if (parentInd != vAcctIds.end()) {
      // Account's parent found
      int ParentIndex = std::distance(vAcctIds.begin(), parentInd);
      // Note vAcctEntries_ has one extra element at the beginning
      vAcctEntries_.at(iAct+1).setParent(&vAcctEntries_.at(ParentIndex+1));
      if (vAcctEntries_.at(iAct+1).getIsBudgeted() == UNDEFINED) { vAcctEntries_.at(iAct+1).setIsBudgeted(INHERITED); }
      if (vAcctEntries_.at(iAct+1).getIsDebitIncrease() == UNDEFINED) { vAcctEntries_.at(iAct+1).setIsDebitIncrease(INHERITED); }
    }
  }
}

AccountEntry AccountList::at(unsigned int ind) const {
  return vAcctEntries_.at(ind);
}

unsigned int AccountList::size(void) const {
  return vAcctEntries_.size();
}
