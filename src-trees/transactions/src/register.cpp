/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "register.h"
#include "csv.h"
#include <cassert>
#include <iostream>
#include <ostream>
#include <algorithm>

Register::Register(StringDatabase data, const char *accountListFile)
    : accountList_(accountListFile){
  // Max number of transactions in record
  unsigned int numEntries = data.body.size();

  std::vector<unsigned int> vTransactionIds;
  std::vector<Transaction*> vTransactionPtrs;

  // Set capacity, as resizing a vector causes invalid pointers
  vTransaction_.reserve(numEntries);
  vSplit_.reserve(numEntries);
  vTransactionIds.reserve(numEntries);
  vTransactionPtrs.reserve(numEntries);

  // Define columns in String Database from Transaction List
  constexpr unsigned int ID = 0;
  constexpr unsigned int PARENT_ID = 1;
  constexpr unsigned int NAME = 2;
  constexpr unsigned int PERIOD = 3;
  constexpr unsigned int DATE = 4;
  constexpr unsigned int VENDOR = 5;
  constexpr unsigned int AMOUNT = 6;
  constexpr unsigned int DEBIT_ACCOUNT = 7;
  constexpr unsigned int CREDIT_ACCOUNT = 9;
  constexpr unsigned int MEMO = 11;

  // Iterate through elements of database, filling vectors
  for (unsigned int iElement = 0; iElement < numEntries; iElement++ ) {
    std::vector<std::string> vStrings = data.body.at(iElement);

    // Get transaction or split status
    bool isTransaction = vStrings.at(PARENT_ID) == "" ? true : false;
    bool isSplit = vStrings.at(DEBIT_ACCOUNT) == "" && vStrings.at(CREDIT_ACCOUNT) == "" ? false : true;
    if ( ! isTransaction && ! isSplit) {
      std::cerr << "Malformed transactions list." << std::endl;
      std::cerr << "Each entry must be a transaction (no parent id) or a split (containing an account in either debit or credit account." << std::endl;
      std::cerr << "Malformed transaction has ID: " << vStrings.at(ID) << std::endl;
      assert(isTransaction || isSplit); // Ensure each transaction is either a transaction or a split.
    }
    
    // Load transactions
    if (isTransaction) {
      vTransaction_.push_back(Transaction());
      // Format transaction
      assert(Strings::isInteger(vStrings.at(ID)));
      vTransaction_.back().setId(Strings::toInteger(vStrings.at(ID)));
      vTransaction_.back().setName(vStrings.at(NAME));
      vTransaction_.back().setPeriod(vStrings.at(PERIOD));
      vTransaction_.back().setDate(Date(vStrings.at(DATE)));
      vTransaction_.back().setVendor(vStrings.at(VENDOR));
      vTransaction_.back().setMemo(vStrings.at(MEMO));

      if (isSplit) {
        vSplit_.push_back(Split(&accountList_));

        vSplit_.back().setParentTransaction(&vTransaction_.back());
        vSplit_.back().setId(Strings::toInteger(vStrings.at(ID)));
        vSplit_.back().setAmount(Currency(vStrings.at(AMOUNT)));
        vSplit_.back().setDebitAccount(vStrings.at(DEBIT_ACCOUNT));
        vSplit_.back().setCreditAccount(vStrings.at(CREDIT_ACCOUNT));
      } else {
        // Save the transaction to allow splits to be added
        vTransactionIds.push_back(Strings::toInteger(vStrings.at(ID)));
        vTransactionPtrs.push_back(&vTransaction_.back());
      }
    } else {
      // If not a transaction, then a split
      vSplit_.push_back(Split(&accountList_));

      vSplit_.back().setId(Strings::toInteger(vStrings.at(ID)));
      vSplit_.back().setAmount(Currency(vStrings.at(AMOUNT)));
      vSplit_.back().setDebitAccount(vStrings.at(DEBIT_ACCOUNT));
      vSplit_.back().setCreditAccount(vStrings.at(CREDIT_ACCOUNT));

      // Potentially Overwrite values from transaction
      vSplit_.back().setName(vStrings.at(NAME));
      vSplit_.back().setPeriod(vStrings.at(PERIOD));
      vSplit_.back().setDate(Date(vStrings.at(DATE)));
      vSplit_.back().setVendor(vStrings.at(VENDOR));
      vSplit_.back().setMemo(vStrings.at(MEMO));

      // Look for parent transaction
      unsigned int parentId = Strings::toInteger(vStrings.at(PARENT_ID));
      auto parentTransactionInd = std::find(vTransactionIds.begin(), vTransactionIds.end(), parentId);
      assert(parentTransactionInd != vTransactionIds.end());
      int ParentIndex = std::distance(vTransactionIds.begin(), parentTransactionInd);
      vSplit_.back().setParentTransaction(vTransactionPtrs.at(ParentIndex));

    }
  }

  /// @todo For any orphaned splits, look through transactions again.

}

void Register::printSplits(void) const {
  /// @todo pass a parameter to sort by. Then create a copy of the vector vSplit_ that is sorted, and print this.

  // Now print all splits:
  for (uint iSplit = 0; iSplit < vSplit_.size(); iSplit++) {
    std::cout << vSplit_.at(iSplit).getId() << "\t";
    std::cout << vSplit_.at(iSplit).getName().str(20) << "\033[30G"
              << vSplit_.at(iSplit).getPeriod().str(4) << "\033[36G"
              << vSplit_.at(iSplit).getDate().str(10) << "\033[48G"
              << vSplit_.at(iSplit).getVendor().str(10) << "\033[60G"
              << vSplit_.at(iSplit).getAmount().str(10) << "\033[72G"
              << vSplit_.at(iSplit).getDebitAccount().str(15) << "\033[89G"
              << vSplit_.at(iSplit).getCreditAccount().str(15) << "\033[106G"
              << vSplit_.at(iSplit).getMemo().str(20) << std::endl;
  }
}

void Register::printTransactions(void) const {
  /// @todo pass a parameter to sort by. Then create a copy of the vector vSplit_ that is sorted, and print this.

  // Now print all splits:
  for (uint iTransaction = 0; iTransaction < vTransaction_.size(); iTransaction++) {
    std::cout << vTransaction_.at(iTransaction).getId() << "\t";
    std::cout << vTransaction_.at(iTransaction).getName().str(20) << "\033[30G"
              << vTransaction_.at(iTransaction).getPeriod().str(4) << "\033[36G"
              << vTransaction_.at(iTransaction).getDate().str(10) << "\033[48G"
              << vTransaction_.at(iTransaction).getVendor().str(10) << "\033[60G"
              << vTransaction_.at(iTransaction).getAmount().str(10) << "\033[72G"
              << vTransaction_.at(iTransaction).getDebitAccount().str(15) << "\033[89G"
              << vTransaction_.at(iTransaction).getCreditAccount().str(15) << "\033[106G"
              << vTransaction_.at(iTransaction).getMemo().str(20) << std::endl;
  }
}
