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
#include "register.h"

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

  AccountList accountList("../../../../res/data/Accounts.dbkcfg");

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
  Csv transactionsList("../../../../res/data/TransactionsListv2.dbk");
  StringDatabase data = transactionsList.load();
  std::cout << "Database loaded." << std::endl;

  Register reg(data, "../../../../res/data/Accounts.dbkcfg");

  // std::cout << "SPLITS:" << std::endl;
  // reg.printSplits();

  // std::cout << "TRANSACTIONS:" << std::endl;
  // reg.printTransactions();


  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
