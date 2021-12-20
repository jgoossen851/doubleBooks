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


int runTest(std::string testName,
            Element     *elementUnderTest,
            std::string testString,
            std::string ansString ) {
  elementUnderTest->setFromStr(testString);
  std::cout << testName << " is set to " << testString << " and displayed as " << elementUnderTest->str(12) << std::endl;
  if( ansString.compare(elementUnderTest->str(12)) != 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int main() {

  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  // Test setting and printing elements
  Currency currency;
  exitStatus |= runTest("Currency", &currency, "$1.23", "$0.00");

  Date date;
  exitStatus |= runTest("Date", &date, "12/11/2010", "12/11/2010");

  Category category;
  exitStatus |= runTest("Category", &category, "Cat1", "************");

  Account account;
  exitStatus |= runTest("Account", &account, "Savings", "************");

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
