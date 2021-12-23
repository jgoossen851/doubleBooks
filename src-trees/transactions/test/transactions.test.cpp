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
  if( ansString.compare(testString) != 0) {
    return failTest("Compare", ansString, testString);
  }
  return EXIT_SUCCESS;
}

int main() {
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  AccountList accountList("../../../../res/data/Accounts.2bkcfg");

  

  Transaction testTransaction;
  testTransaction.setId(1);
  testTransaction.setName("Transaction Name");
  testTransaction.setDate(Date("10/11/12"));
  testTransaction.setVendor("General Store");

  Split testSplit;
  testSplit.setId(2);
  testSplit.setPeriod("Q1");
  testSplit.setAmount(Currency("3.56"));
  testSplit.setDebitAccount(40);
  testSplit.setCreditAccount(20);
  testSplit.setMemo("This is the memo");
  testSplit.setParentTransaction(&testTransaction);

  // Test output
  unsigned int splitid = testSplit.getId();
  std::string name = testSplit.getName();
  std::string period = testSplit.getPeriod();
  Date date = testSplit.getDate();
  Currency amount = testSplit.getAmount();
  unsigned int debitAccountInd = testSplit.getDebitAccountInd();
  unsigned int creditAccountInd = testSplit.getCreditAccountInd();
  std::string memo = testSplit.getMemo();

  exitStatus |= testStrings(std::to_string(splitid), "2");
  exitStatus |= testStrings(name, "Transaction Name");
  exitStatus |= testStrings(period, "Q1");
  exitStatus |= testStrings(date.str(), "10/11/12");
  exitStatus |= testStrings(amount.str(), "     $3.56");
  exitStatus |= testStrings(accountList.at(debitAccountInd).str(10), "DebitAcct");
  exitStatus |= testStrings(accountList.at(creditAccountInd).str(10), "CreditAcct");
  exitStatus |= testStrings(memo, "This is the memo");
  
  




  // Read transactions CSV
  Csv transactionsList("../../../../res/data/TransactionsListv2.2bk");
  StringDatabase data = transactionsList.load();
  std::cout << "Database loaded." << std::endl;

  unsigned int numEntries = data.body.size();
  std::cout << "Num Entries: " << numEntries << std::endl;


  // create a vector of transactions and splits
  std::vector<Transaction>  vTransaction;
  std::vector<Split>        vSplit;

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
    const unsigned int BALANCED = 12;

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
      Transaction transaction;

      // Format transaction
      assert(Strings::isInteger(vStrings.at(ID)));
      transaction.setId(Strings::toInteger(vStrings.at(ID)));



      vTransaction.push_back(transaction);
    }




  }


  // Test several Account strings and properties
  exitStatus |= testStrings(accountList.at(3).str(5) + " B[" + std::to_string(accountList.at(3).getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at(3).getIsDebitIncrease()) + "]",
                            "quity B[0] D[0]");
  exitStatus |= testStrings(accountList.at(13).str(40) + " B[" + std::to_string(accountList.at(13).getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at(13).getIsDebitIncrease()) + "]",
                            "Expenses:Food:Groceries B[1] D[1]");
  exitStatus |= testStrings(accountList.at(41).str() + " B[" + std::to_string(accountList.at(41).getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at(41).getIsDebitIncrease()) + "]",
                            "ets:Checking B[0] D[1]");
  exitStatus |= testStrings(accountList.at().str() + " B[" + std::to_string(accountList.at().getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at().getIsDebitIncrease()) + "]",
                            "Undefined B[3] D[3]");

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
