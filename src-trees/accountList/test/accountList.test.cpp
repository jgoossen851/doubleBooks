/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "ansi.h"
#include "csv.h"
#include "strings.h"

#include "accountList.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <strings.h>
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

  AccountList accountList("../../../../res/data/Accounts.dbkcfg"); //? Terminal
  // AccountList accountList("./res/data/Accounts.dbkcfg"); //? Codium

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
                            " B[3] D[3]");

  // Test Move Assignment Operator
  AccountEntry newAcct;
  {
    AccountEntry tempAcct(1, "TempAcct", TRUE, TRUE);
    newAcct = std::move(tempAcct);
  }
  exitStatus |= testStrings(newAcct.str(), "TempAcct");


  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
