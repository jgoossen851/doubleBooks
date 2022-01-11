/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "register.h"
#include "csv.h"
#include "ansi.h"
#include "datafield.h"

#include <cassert>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <cstdio>
#include <string>

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

        vSplit_.back().setParent(&vTransaction_.back());
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
      vSplit_.back().setParent(vTransactionPtrs.at(ParentIndex));

    }
  }

  /// @bug For any orphaned splits, look through transactions again.

}

void Register::printSplits(void) const {
  /// @todo pass a parameter to sort by. Then create a copy of the vector vSplit_ that is sorted, and print this.

  printHeader();
  for (uint iSplit = 0; iSplit < vSplit_.size(); iSplit++) {
    printEntry(&vSplit_.at(iSplit));
  }
}

void Register::printTransactions(void) const {
  /// @todo pass a parameter to sort by. Then create a copy of the vector vSplit_ that is sorted, and print this.

  printHeader();
  for (uint iTransaction = 0; iTransaction < vTransaction_.size(); iTransaction++) {
    printEntry(&vTransaction_.at(iTransaction));
  }
}

void Register::printEntry(const Entry *entry) const {
    /// @note Using fprint here doen't allow formatting in strings.
    printElement(std::to_string(entry->getId()), vColumnWidth_.at(ID), 2);
    printElement(entry->getName().str(vColumnWidth_.at(NAME)), vColumnWidth_.at(NAME), 2);
    printElement(entry->getPeriod().str(vColumnWidth_.at(PERIOD)), vColumnWidth_.at(PERIOD), 2);
    printElement(entry->getDate().str(vColumnWidth_.at(DATE)), vColumnWidth_.at(DATE), 2);
    printElement(entry->getVendor().str(vColumnWidth_.at(VENDOR)), vColumnWidth_.at(VENDOR), 2);
    printElement(entry->getAmount().str(vColumnWidth_.at(AMOUNT)), vColumnWidth_.at(AMOUNT), 2);
    printElement(entry->getDebitAccount().str(vColumnWidth_.at(DEBIT_ACCOUNT)), vColumnWidth_.at(DEBIT_ACCOUNT), 2);
    printElement(entry->getCreditAccount().str(vColumnWidth_.at(CREDIT_ACCOUNT)), vColumnWidth_.at(CREDIT_ACCOUNT), 2);
    printElement(entry->getMemo().str(vColumnWidth_.at(MEMO)), vColumnWidth_.at(MEMO), 2);
    std::cout << std::endl;

    /// @note This way, however, get messed up when the window resizes.
    // std::cout << ansi::CLEAR_LINE << ansi::RESET_LINE;
    // std::cout << UintField(entry->getId()).str(vColumnWidth_.at(ID)) << ansi::COLUMN(6);
    // std::cout << entry->getName().str(vColumnWidth_.at(NAME)) << ansi::COLUMN(28)
    //           << entry->getPeriod().str(vColumnWidth_.at(PERIOD)) << ansi::COLUMN(34)
    //           << entry->getDate().str(vColumnWidth_.at(DATE)) << ansi::COLUMN(44)
    //           << entry->getVendor().str(vColumnWidth_.at(VENDOR)) << ansi::COLUMN(56)
    //           << entry->getAmount().str(vColumnWidth_.at(AMOUNT)) << ansi::COLUMN(68)
    //           << entry->getDebitAccount().str(vColumnWidth_.at(DEBIT_ACCOUNT)) << ansi::COLUMN(85)
    //           << entry->getCreditAccount().str(vColumnWidth_.at(CREDIT_ACCOUNT)) << ansi::COLUMN(102)
    //           << entry->getMemo().str(vColumnWidth_.at(MEMO)) << std::endl;
}

void Register::printHeader() const {

  std::vector<TransactionColumns> columnsToPrint;
  columnsToPrint.push_back(ID);
  columnsToPrint.push_back(NAME);
  columnsToPrint.push_back(PERIOD);
  columnsToPrint.push_back(DATE);
  columnsToPrint.push_back(VENDOR);
  columnsToPrint.push_back(AMOUNT);
  columnsToPrint.push_back(DEBIT_ACCOUNT);
  columnsToPrint.push_back(CREDIT_ACCOUNT);
  columnsToPrint.push_back(MEMO);

  std::cout << ansi::CLEAR_LINE << ansi::RESET_LINE;
  std::cout << ansi::BOLD + ansi::UNDERLINE + ansi::OVERLINE;
  for (uint ii = 0; ii < columnsToPrint.size(); ii++) {
    printElement(vHeader_.at(columnsToPrint.at(ii)),
                 vColumnWidth_.at(columnsToPrint.at(ii)), 2);
  }
  std::cout << ansi::RESET << std::endl;
}

void Register::printElement(PrettyString str, uint width, uint space) const {
  std::cout << ansi::SAVE_CURSOR;
  std::cout << str;
  std::cout << ansi::RESTORE_CURSOR << ansi::CURSOR_FORWARD(width+space);
}
