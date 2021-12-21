/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "ansi.h"
#include "currency.h"
#include "date.h"
#include "category.h"
#include "account.h"

#include <cstdlib>
#include <iostream>


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

int main() {

  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  // Test setting and printing table elements
  Currency currency;
  exitStatus |= testElementDisplay("Currency", &currency, "$0.00");
  currency.setFromStr("$1.23");
  exitStatus |= testElementDisplay("Currency", &currency, "$0.00");

  Date date;
  exitStatus |= testElementDisplay("Date", &date, "");
  date.setFromStr("12/11/2010");
  exitStatus |= testElementDisplay("Date", &date, "12/11/2010");

  Category category;
  exitStatus |= testElementDisplay("Category", &category, "************");
  category.setFromStr("Cat1");
  exitStatus |= testElementDisplay("Category", &category, "************");

  Account account;
  exitStatus |= testElementDisplay("Account", &account, "Undefined");


  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
