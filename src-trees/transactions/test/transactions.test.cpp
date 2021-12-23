/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "ansi.h"
#include "accountList.h"
#include "csv.h"
#include "currency.h"
#include "datafield.h"
#include "split.h"
#include "transaction.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <strings.h>
#include <sys/types.h>
#include <vector>


int failTest( std::string testName,
              std::string ansString,
              std::string resultString) {
  std::cout << ansi::RED << "Test Failed: " << ansi::RESET;
  std::cout << "Test " << testName << " should be [" << ansString 
            << "] but was [" << resultString << "]" << std::endl;
  return EXIT_FAILURE;
}

int testStrings(std::string testString,
                std::string ansString ) {
  // std::cout << testString << std::endl;
  if( ansString.compare(testString) != 0) {
    return failTest("Compare", ansString, testString);
  }
  return EXIT_SUCCESS;
}

int main() {
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  AccountList accountList("../../../../res/data/Accounts.2bkcfg");

  // std::cout << "transactions" << std::endl;
  Transaction testTransaction;
  testTransaction.setId(1);
  testTransaction.setName("Transaction Name");
  testTransaction.setDate(Date("10/11/12"));
  testTransaction.setVendor("General Store");

  // std::cout << "splits" << std::endl;
  Split testSplit(&accountList);
  testSplit.setId(2);
  testSplit.setPeriod("Q1");
  testSplit.setAmount(Currency("3.56"));
  testSplit.setDebitAccount("40");
  testSplit.setCreditAccount("20");
  testSplit.setMemo("This is the memo");
  testSplit.setParentTransaction(&testTransaction);

  // Test output
  // std::cout << "output" << std::endl;
  unsigned int splitid = testSplit.getId();
  StringField name = testSplit.getName();
  StringField period = testSplit.getPeriod();
  Date date = testSplit.getDate();
  Currency amount = testSplit.getAmount();
  unsigned int debitAccountInd = testSplit.getDebitAccountInd();
  unsigned int creditAccountInd = testSplit.getCreditAccountInd();
  StringField memo = testSplit.getMemo();

  exitStatus |= testStrings(std::to_string(splitid), "2");
  exitStatus |= testStrings(name.str(20), "Transaction Name");
  exitStatus |= testStrings(period.str(), "Q1");
  exitStatus |= testStrings(date.str(), "10/11/12");
  exitStatus |= testStrings(amount.str(), "     $3.56");
  exitStatus |= testStrings(accountList.at(debitAccountInd).str(20), "Assets:Cash");
  exitStatus |= testStrings(accountList.at(creditAccountInd).str(20), "rsonal:Miscellaneous");
  exitStatus |= testStrings(memo.str(20), "This is the memo");
  
  




  // Read transactions CSV
  Csv transactionsList("../../../../res/data/TransactionsListv2.2bk");
  StringDatabase data = transactionsList.load();
  std::cout << "Database loaded." << std::endl;

  unsigned int numEntries = data.body.size();
  std::cout << "Num Entries: " << numEntries << std::endl;


  // create a vector of transactions and splits
  std::vector<Transaction>  vTransaction;
  std::vector<Split>        vSplit;
  std::vector<unsigned int> vTransactionIds;
  std::vector<Transaction*> vTransactionPtrs;

  // Set capacity, as resizing a vector causes invalid pointers
  vTransaction.reserve(numEntries);
  vSplit.reserve(numEntries);
  vTransactionIds.reserve(numEntries);
  vTransactionPtrs.reserve(numEntries);

  for (unsigned int iElement = 0; iElement < numEntries; iElement++ ) {
    std::vector<std::string> vStrings = data.body.at(iElement);
    // Define column numbers
    const unsigned int ID = 0;
    const unsigned int PARENT_ID = 1;
    const unsigned int NAME = 2;
    const unsigned int PERIOD = 3;
    const unsigned int DATE = 4;
    const unsigned int VENDOR = 5;
    const unsigned int AMOUNT = 6;
    const unsigned int DEBIT_ACCOUNT = 7;
    const unsigned int CREDIT_ACCOUNT = 9;
    const unsigned int MEMO = 11;

    // Is Transaction?
    bool isTransaction = vStrings.at(PARENT_ID) == "" ? true : false;
    bool isSplit = vStrings.at(DEBIT_ACCOUNT) == "" && vStrings.at(CREDIT_ACCOUNT) == "" ? false : true;

    // Print entire line
    std::cout << (isTransaction ? ansi::CYAN : "");
    std::cout << (isSplit ? ansi::BOLD : "");
    for (unsigned int jj = 0; jj < vStrings.size(); jj++) {
      std::cout << vStrings.at(jj) << "  ";
    }
    std::cout << ansi::RESET << std::endl;

    // Load transactions
    if (isTransaction) {
      vTransaction.push_back(Transaction());
      // Format transaction
      assert(Strings::isInteger(vStrings.at(ID)));
      vTransaction.back().setId(Strings::toInteger(vStrings.at(ID)));
      vTransaction.back().setName(vStrings.at(NAME));
      vTransaction.back().setPeriod(vStrings.at(PERIOD));
      vTransaction.back().setDate(Date(vStrings.at(DATE)));
      vTransaction.back().setVendor(vStrings.at(VENDOR));
      vTransaction.back().setMemo(vStrings.at(MEMO));

      if (isSplit) {
        vSplit.push_back(Split(&accountList));

        vSplit.back().setParentTransaction(&vTransaction.back());
        vSplit.back().setId(Strings::toInteger(vStrings.at(ID)));
        vSplit.back().setAmount(Currency(vStrings.at(AMOUNT)));
        vSplit.back().setDebitAccount(vStrings.at(DEBIT_ACCOUNT));
        vSplit.back().setCreditAccount(vStrings.at(CREDIT_ACCOUNT));
      } else {
        // Save the transaction to allow splits to be added
        vTransactionIds.push_back(Strings::toInteger(vStrings.at(ID)));
        vTransactionPtrs.push_back(&vTransaction.back());
      }
    } else {
      // If not a transaction
      if (isSplit) {
        vSplit.push_back(Split(&accountList));

        vSplit.back().setId(Strings::toInteger(vStrings.at(ID)));
        vSplit.back().setAmount(Currency(vStrings.at(AMOUNT)));
        vSplit.back().setDebitAccount(vStrings.at(DEBIT_ACCOUNT));
        vSplit.back().setCreditAccount(vStrings.at(CREDIT_ACCOUNT));

        // Potentially Overwrite values from transaction
        vSplit.back().setName(vStrings.at(NAME));
        vSplit.back().setPeriod(vStrings.at(PERIOD));
        vSplit.back().setDate(Date(vStrings.at(DATE)));
        vSplit.back().setVendor(vStrings.at(VENDOR));
        vSplit.back().setMemo(vStrings.at(MEMO));

        // Look for parent transaction
        unsigned int parentId = Strings::toInteger(vStrings.at(PARENT_ID));
        auto parentTransactionInd = std::find(vTransactionIds.begin(), vTransactionIds.end(), parentId);
        assert(parentTransactionInd != vTransactionIds.end());
        int ParentIndex = std::distance(vTransactionIds.begin(), parentTransactionInd);
        vSplit.back().setParentTransaction(vTransactionPtrs.at(ParentIndex));

      } else {
        std::cout << "If it not a transaction or a split, I don't know what it is!" << std::endl;
      }
    }
  }

  // Now print all splits:
  for (uint iSplit = 0; iSplit < vSplit.size(); iSplit++) {
    std::cout << vSplit.at(iSplit).getId() << "\t";
    std::cout << vSplit.at(iSplit).getName().str(20) << "\033[30G"
              << vSplit.at(iSplit).getPeriod().str(4) << "\033[36G"
              << vSplit.at(iSplit).getDate().str(10) << "\033[48G"
              << vSplit.at(iSplit).getVendor().str(10) << "\033[60G"
              << vSplit.at(iSplit).getAmount().str(10) << "\033[72G"
              << vSplit.at(iSplit).getDebitAccountInd() << "\033[76G"
              << vSplit.at(iSplit).getCreditAccountInd() << "\033[80G"
              << vSplit.at(iSplit).getMemo().str(20) << std::endl;
  }

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
