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
#include "transaction_old.h"
#include "register.h"

#include <iostream>

int main(int argc, char* argv[]) {

  // Check that a single argument was given
  if (argc != 2) {
    std::cout << argv[0] << " Version " << PROJECT_VERSION << std::endl;
    std::cerr << argv[0] << " requires a single argument containing the file to parse." << std::endl;
    return 1;
  }

  // Set up files
  Csv transactionsList(argv[1]);
  std::cout << "CSV opened." << std::endl;
  
  // Load database
  // Database<A1> data = transactionsList.load();
  Register reg(transactionsList.load(), "../res/data/Accounts.2bkcfg");
  std::cout << "Database loaded." << std::endl;
  
  // Print Table
  reg.printSplits();
  // Table table(data);
  // std::cout << "Table constructed." << std::endl;
  // table.print();
  
  
  
  return 0;
}
