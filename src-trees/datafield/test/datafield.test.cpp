/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "accountList.h"
#include "ansi.h"

#include "currency.h"
#include "date.h"
#include "category.h"
#include "account.h"
#include "datafield.h"

#include <iostream>


int failTest( std::string testName,
              std::string ansString,
              std::string resultString) {
  std::cout << ansi::RED << "Test Failed: " << ansi::RESET;
  std::cout << "Test " << testName << " should be [" << ansString 
            << "] but was [" << resultString << "]" << std::endl;
  return EXIT_FAILURE;
}

int testElementDisplay(std::string testName,
                       Element     *elementUnderTest,
                       std::string ansString ) {
  if( ansString.compare(elementUnderTest->str(12)) != 0) {
    return failTest(testName, ansString, elementUnderTest->str(12));
  }
  return EXIT_SUCCESS;
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

  // Test setting and printing table elements
  UintField uintfield;
  exitStatus |= testElementDisplay("Uint", &uintfield, "4294967295");
  uintfield.setFromStr("Text");
  exitStatus |= testElementDisplay("Uint", &uintfield, "4294967295");
  uintfield.setFromStr("95");
  exitStatus |= testElementDisplay("Uint", &uintfield, "95");

  BoolField boolfield;
  exitStatus |= testElementDisplay("Bool", &boolfield, "0");
  boolfield.setFromStr("1");
  exitStatus |= testElementDisplay("Bool", &boolfield, "1");
  boolfield.setFromStr("0");
  exitStatus |= testElementDisplay("Bool", &boolfield, "0");
  boolfield.setFromStr("Text");
  exitStatus |= testElementDisplay("Bool", &boolfield, "1");

  StringField stringfield;
  exitStatus |= testElementDisplay("Period", &stringfield, "");
  stringfield.setFromStr("Q1");
  exitStatus |= testElementDisplay("Period", &stringfield, "Q1");
  stringfield.setFromStr("2101");
  exitStatus |= testElementDisplay("Period", &stringfield, "2101");

  Currency currency;
  exitStatus |= testElementDisplay("Currency", &currency, "       $0.00");
  currency.setFromStr("$1.23");
  exitStatus |= testElementDisplay("Currency", &currency, "       $1.23");
  currency.setFromStr("-4.56");
  exitStatus |= testElementDisplay("Currency", &currency, "-      $4.56");
  currency.setFromStr("");
  exitStatus |= testElementDisplay("Currency", &currency, "       $0.00");
  currency.setFromStr("0");
  exitStatus |= testElementDisplay("Currency", &currency, "       $0.00");
  Currency currencyParen(PARENTHESIS);
  currencyParen.setFromStr("$44.44");
  exitStatus |= testElementDisplay("Currency", &currencyParen, "     $44.44 ");
  currencyParen.setFromStr("-5.67");
  exitStatus |= testElementDisplay("Currency", &currencyParen, "(     $5.67)");
  Currency currencyRed(RED_COLOR);
  currencyRed.setFromStr("-6.78");
  exitStatus |= testElementDisplay("Currency", &currencyRed, ansi::SAVE_ATTRIBUTES + ansi::RED + "       $6.78" + ansi::RESTORE_ATTRIBUTES);
  


  Date date;
  exitStatus |= testElementDisplay("Date", &date, "--/--/--");
  date.setFromStr("12/11/2010");
  exitStatus |= testElementDisplay("Date", &date, "12/11/10");
  date.setFromStr("December 10, 2001");
  exitStatus |= testElementDisplay("Date", &date, "--/--/--");

  Category category;
  exitStatus |= testElementDisplay("Category", &category, "************");
  category.setFromStr("Cat1");
  exitStatus |= testElementDisplay("Category", &category, "************");


  AccountList accountList("../../../../res/data/Accounts.2bkcfg");
  Account account(&accountList);
  exitStatus |= testElementDisplay("Account", &account, "");
  account.setFromStr("42");
  exitStatus |= testElementDisplay("Account", &account, "sets:Savings");
  account.setFromStr("Fortytwo");
  exitStatus |= testElementDisplay("Account", &account, "");


  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
