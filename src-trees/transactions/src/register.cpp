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

enum TransactionColumns {
  ID,
  PARENT_ID,
  NAME,
  PERIOD,
  DATE,
  VENDOR,
  AMOUNT,
  DEBIT_ACCOUNT,
  DEBIT_ACCOUNT_NOTE,
  CREDIT_ACCOUNT,
  CREDIT_ACCOUNT_NOTE,
  MEMO,
};

Register::Register(StringDatabase data, const char *accountListFile)
    : accountList_(accountListFile),
      numColumns_(data.number_of_columns),
      vHeader_(data.header),
      vColumnWidth_(data.column_width)
    {
  std::vector<unsigned int> vTransactionIds;
  std::vector<Transaction*> vTransactionPtrs;

  // Set capacity, as resizing a vector causes invalid pointers
  unsigned int maxEntries = data.body.size();
  vTransaction_.reserve(maxEntries);
  vSplit_.reserve(maxEntries);
  vTransactionIds.reserve(maxEntries);
  vTransactionPtrs.reserve(maxEntries);

  // Iterate through elements of database, filling vectors
  for (auto stringItr = data.body.begin(); stringItr < data.body.end(); stringItr++) {
    // Get transaction or split status
    bool isTransaction = stringItr->at(PARENT_ID) == "" ? true : false;
    bool isSplit = stringItr->at(DEBIT_ACCOUNT) == "" && stringItr->at(CREDIT_ACCOUNT) == "" ? false : true;
    if ( ! isTransaction && ! isSplit) {
      std::cerr << "Malformed transactions list." << std::endl;
      std::cerr << "Each entry must be a transaction (no parent id) or a split (containing an account in either debit or credit account." << std::endl;
      std::cerr << "Malformed transaction has ID: " << stringItr->at(ID) << std::endl;
      assert(isTransaction || isSplit); // Ensure each transaction is either a transaction or a split.
    }
    
    // Load transactions
    if (isTransaction) {
      vTransaction_.push_back(Transaction());
      // Format transaction
      assert(Strings::isInteger(stringItr->at(ID)));
      vTransaction_.back().setId(Strings::toInteger(stringItr->at(ID)));
      vTransaction_.back().setName(stringItr->at(NAME));
      vTransaction_.back().setPeriod(stringItr->at(PERIOD));
      vTransaction_.back().setDate(Date(stringItr->at(DATE)));
      vTransaction_.back().setVendor(stringItr->at(VENDOR));
      vTransaction_.back().setMemo(stringItr->at(MEMO));

      if (isSplit) {
        vSplit_.push_back(Split(&accountList_));

        vSplit_.back().setParentTransaction(&vTransaction_.back());
        vSplit_.back().setId(Strings::toInteger(stringItr->at(ID)));
        vSplit_.back().setAmount(Currency(stringItr->at(AMOUNT)));
        vSplit_.back().setDebitAccount(stringItr->at(DEBIT_ACCOUNT));
        vSplit_.back().setCreditAccount(stringItr->at(CREDIT_ACCOUNT));
      } else {
        // Save the transaction to allow splits to be added
        vTransactionIds.push_back(Strings::toInteger(stringItr->at(ID)));
        vTransactionPtrs.push_back(&vTransaction_.back());
      }
    } else {
      // If not a transaction, then a split
      vSplit_.push_back(Split(&accountList_));

      vSplit_.back().setId(Strings::toInteger(stringItr->at(ID)));
      vSplit_.back().setAmount(Currency(stringItr->at(AMOUNT)));
      vSplit_.back().setDebitAccount(stringItr->at(DEBIT_ACCOUNT));
      vSplit_.back().setCreditAccount(stringItr->at(CREDIT_ACCOUNT));

      // Potentially Overwrite values from transaction
      vSplit_.back().setName(stringItr->at(NAME));
      vSplit_.back().setPeriod(stringItr->at(PERIOD));
      vSplit_.back().setDate(Date(stringItr->at(DATE)));
      vSplit_.back().setVendor(stringItr->at(VENDOR));
      vSplit_.back().setMemo(stringItr->at(MEMO));

      // Look for parent transaction
      unsigned int parentId = Strings::toInteger(stringItr->at(PARENT_ID));
      auto parentTransactionInd = std::find(vTransactionIds.begin(), vTransactionIds.end(), parentId);
      assert(parentTransactionInd != vTransactionIds.end());
      int ParentIndex = std::distance(vTransactionIds.begin(), parentTransactionInd);
      vSplit_.back().setParentTransaction(vTransactionPtrs.at(ParentIndex));

    }
  }

  /// @bug For any orphaned splits, look through transactions again.

}

void Register::printSplits(void) const {
  /// @todo pass a parameter to sort by. Then create a copy of the vector vSplit_ that is sorted, and print this.

  for (uint iSplit = 0; iSplit < vSplit_.size(); iSplit++) {
    printEntry(&vSplit_.at(iSplit));
  }
}

void Register::printTransactions(void) const {
  /// @todo pass a parameter to sort by. Then create a copy of the vector vSplit_ that is sorted, and print this.

  for (uint iTransaction = 0; iTransaction < vTransaction_.size(); iTransaction++) {
    printEntry(&vTransaction_.at(iTransaction));
  }
}

void Register::printEntry(const Entry *entry) const {
    std::cout << entry->getId() << "\t";
    std::cout << entry->getName().str(vColumnWidth_.at(NAME)) << "\033[30G"
              << entry->getPeriod().str(vColumnWidth_.at(PERIOD)) << "\033[36G"
              << entry->getDate().str(vColumnWidth_.at(DATE)) << "\033[48G"
              << entry->getVendor().str(vColumnWidth_.at(VENDOR)) << "\033[60G"
              << entry->getAmount().str(vColumnWidth_.at(AMOUNT)) << "\033[72G"
              << entry->getDebitAccount().str(vColumnWidth_.at(DEBIT_ACCOUNT)) << "\033[89G"
              << entry->getCreditAccount().str(vColumnWidth_.at(CREDIT_ACCOUNT)) << "\033[106G"
              << entry->getMemo().str(vColumnWidth_.at(MEMO)) << std::endl;
}
