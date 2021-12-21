/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "ansi.h"
#include "csv.h"
#include "strings.h"

#include "currency.h"
#include "date.h"
#include "category.h"
#include "account.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <strings.h>
#include <vector>


int failTest() {
  std::cout << ansi::RED << "  ^ Test Failed!" << ansi::RESET << std::endl;
  return EXIT_FAILURE;
}

int testElementDisplay(std::string testName,
                       Element     *elementUnderTest,
                       std::string ansString ) {
  std::cout << testName << " displays as " << elementUnderTest->str(12) << std::endl;
  if( ansString.compare(elementUnderTest->str(12)) != 0) return failTest();
  return EXIT_SUCCESS;
}

int testStrings(std::string testString,
                std::string ansString ) {
  std::cout << "Compare Strings: \"" << testString << "\"" << std::endl;
  if( ansString.compare(testString) != 0) return failTest();
  return EXIT_SUCCESS;
}

int main() {

  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  // Test setting and printing table elements
  Currency currency;
  exitStatus |= testElementDisplay("Currency", &currency, "$0.00");
  currency.setFromStr("$1.23");
  exitStatus |= testElementDisplay("Currency", &currency, "$1.23");

  Date date;
  exitStatus |= testElementDisplay("Date", &date, "--/--/----");
  date.setFromStr("12/11/2010");
  exitStatus |= testElementDisplay("Date", &date, "12/11/2010");

  Category category;
  exitStatus |= testElementDisplay("Category", &category, "************");
  category.setFromStr("Cat1");
  exitStatus |= testElementDisplay("Category", &category, "************");

  Account account;
  exitStatus |= testElementDisplay("Account", &account, "Undefined");
  Account account2(1, "Savings", UNDEFINED, UNDEFINED);
  exitStatus |= testElementDisplay("Account2", &account2, "Savings");

  // Initialize Accounts from CSV
  Csv csv("../../../../res/data/Accounts.csv");
  StringDatabase strDat = csv.load();
  unsigned int numCols = 6;
  assert(strDat.number_of_columns == numCols);
  unsigned int numAccounts = strDat.body.size();

  // Load data into vector of Accounts
  std::vector<int> accountIDs;
  std::vector<int> accountParentIDs;
  std::vector<Account> accountList;
  for (unsigned int iAct = 0; iAct < numAccounts; iAct++) {
    std::vector<std::string> dataVec = strDat.body.at(iAct);

    accountIDs.push_back(Strings::toInteger(dataVec.at(0)));
    accountParentIDs.push_back(Strings::toInteger(dataVec.at(1)));

    InheritBool isBudgeted = Strings::isInteger(dataVec.at(4)) 
        ? (Strings::toInteger(dataVec.at(4)) == 0 ? FALSE : TRUE)
        : UNDEFINED;
    InheritBool isDebitIncrease = Strings::isInteger(dataVec.at(5)) 
        ? (Strings::toInteger(dataVec.at(5)) == 0 ? FALSE : TRUE)
        : UNDEFINED;

    accountList.push_back(Account(
        Strings::toInteger(dataVec.at(3)),  // Sort Order
        dataVec.at(2),                      // Name
        isBudgeted,                         // isBudgeted
        isDebitIncrease                     // isDebitIncrease
    ));
  }
  
  // Find account ancestors
  for (unsigned int iAct = 0; iAct < numAccounts; iAct++) {
    // Find the index of the parent account
    auto parentInd = std::find(accountIDs.begin(), accountIDs.end(), accountParentIDs.at(iAct));
    if (parentInd != accountIDs.end()) {
      // Account's parent found
      int ParentIndex = std::distance(accountIDs.begin(), parentInd);
      accountList.at(iAct).setParent(&accountList.at(ParentIndex));
      if (accountList.at(iAct).getIsBudgeted() == UNDEFINED) { accountList.at(iAct).setIsBudgeted(INHERITED); }
      if (accountList.at(iAct).getIsDebitIncrease() == UNDEFINED) { accountList.at(iAct).setIsDebitIncrease(INHERITED); }
    }
  }

  // Test several Account strings and properties
  exitStatus |= testStrings(accountList.at(2).str(5) + " B[" + std::to_string(accountList.at(2).getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at(2).getIsDebitIncrease()) + "]",
                            "quity B[0] D[0]");
  exitStatus |= testStrings(accountList.at(12).str(40) + " B[" + std::to_string(accountList.at(12).getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at(12).getIsDebitIncrease()) + "]",
                            "Expenses:Food:Groceries B[1] D[1]");
  exitStatus |= testStrings(accountList.at(40).str() + " B[" + std::to_string(accountList.at(40).getIsBudgeted()) 
                                                    + "] D[" + std::to_string(accountList.at(40).getIsDebitIncrease()) + "]",
                            "ets:Checking B[0] D[1]");

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
