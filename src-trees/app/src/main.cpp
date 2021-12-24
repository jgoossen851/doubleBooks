/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "version.h"
#include "csv.h"
#include "currency.h"
#include "register.h"

#include <iostream>
#include <cstdlib>

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

  // Get installed location of configuration file
  char *env_home;
  env_home = getenv("HOME");
  std::string pathStr = env_home;
  pathStr.append("/.local/share/doublebooks/Accounts.dbkcfg");

  // Load database
  Register reg(transactionsList.load(), pathStr.c_str());
  std::cout << "Database loaded." << std::endl;
  
  // Print Table
  reg.printSplits();

  return 0;
}
