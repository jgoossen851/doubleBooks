/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "version.h"
#include "csv.h"
#include "table.h"
#include "currency.h"
#include "transaction.h"

#include <iostream>

 /// @todo Figure out what to do with this global variable
  std::vector<CategoryDescriptions>  gCategoryList_;

int main(int argc, char* argv[]) {

  // Check that a single argument was given
  if (argc != 2) {
    std::cout << argv[0] << " Version " << PROJECT_VERSION << std::endl;
    std::cerr << argv[0] << " requires a single argument containing the file to parse." << std::endl;
    return 1;
  }

  // Placeholder: setup categories, rather than reading from file
  // ID, Name, Type, Display Order, isExpense, isBudgeted
  gCategoryList_.push_back(CategoryDescriptions(0,  "Zeroth Cat",     0, 12,  true,   false));
  gCategoryList_.push_back(CategoryDescriptions(1,  "First Cat",      0, 34,  true,   false));
  gCategoryList_.push_back(CategoryDescriptions(2,  "Second Cat",     0, 4,   false,  false));
  gCategoryList_.push_back(CategoryDescriptions(3,  "Third Cat",      0, 62,  true,   false));
  gCategoryList_.push_back(CategoryDescriptions(4,  "Fourth Cat",     0, 3,   true,   false));
  gCategoryList_.push_back(CategoryDescriptions(5,  "Fifth Cat",      1, 74,  false,  false));
  gCategoryList_.push_back(CategoryDescriptions(6,  "Sixth Cat",      2, 27,  true,   false));
  gCategoryList_.push_back(CategoryDescriptions(7,  "Seventh Cat",    0, 43,  false,  true));
  gCategoryList_.push_back(CategoryDescriptions(8,  "Eighth Cat",     0, 22,  true,   true));
  gCategoryList_.push_back(CategoryDescriptions(9,  "Ninth Cat",      1, 89,  false,  true));
  gCategoryList_.push_back(CategoryDescriptions(10, "Tenth Cat",      1, 23,  true,   true));
  gCategoryList_.push_back(CategoryDescriptions(11, "Eleventh Cat",   0, 24,  true,   true));
  gCategoryList_.push_back(CategoryDescriptions(12, "Twelveth Cat",   1, 1,   false,  true));
  gCategoryList_.push_back(CategoryDescriptions(13, "Thirteenth Cat", 0, 88,  true,   true));

  // Set up files
  Csv transactionsList(argv[1]);
  std::cout << "CSV opened." << std::endl;
  
  // Load database
  Database<A1> data = transactionsList.load();
  std::cout << "Database loaded." << std::endl;
  
  // Print Table
  Table table(data);
  std::cout << "Table constructed." << std::endl;
  table.print();
  
  
  // Currency amount(PARENTHESIS);
  
  // std::cout << "\033[1m";
  
  // amount.cents = -12345;
  // std::cout << amount.display() << std::endl;
  
  // std::cout << "\033[33m";
  
  // amount.cents = -123456;
  // std::cout << amount.display() << std::endl;
  
  // amount.cents = -1234567;
  // std::cout << amount.display() << std::endl;
  
  // amount.cents = -12345678;
  // std::cout << amount.display() << std::endl;
  
  // amount.cents = -123456789;
  // std::cout << amount.display(15) << std::endl;
  
  // amount.cents = 11;
  // std::cout << amount.display() << std::endl;
  
  // amount.cents = -0255;
  // std::cout << amount.display() << std::endl;
  
  // amount.cents = 0;
  // std::cout << amount.display() << std::endl;
  
  // amount.cents = -134;
  // std::cout << amount.display() << std::endl;
  
  // Transaction trans;
  // trans.transaction_amount.cents = -123;
  // std::cout << trans.transaction_amount.display() << std::endl;
  
  
  return 0;
}
