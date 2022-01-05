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
#include <map>
#include <functional>
#include <string>

enum COMMANDS {
  LOAD,
  PRINT
};

Register loadData(const char * filename){
  // Set up files
  Csv transactionsList(filename);
  std::cout << "CSV opened." << std::endl;

  // Get installed location of configuration file
  char *env_home;
  env_home = getenv("HOME");
  std::string pathStr = env_home;
  pathStr.append("/.local/share/doublebooks/Accounts.dbkcfg");

  // Load database
  std::cout << "Database loaded." << std::endl;
  return Register(transactionsList.load(), pathStr.c_str());
}

int main(int argc, char* argv[]) {

  // Check that a single argument was given
  if (argc != 2) {
    std::cout << argv[0] << " Version " << PROJECT_VERSION << std::endl;
    std::cerr << argv[0] << " requires a single argument containing the file to parse." << std::endl;
    return 1;
  }
  
  // Define user commands
  std::map< std::string, COMMANDS > dictionary;
  dictionary["l"] = LOAD;
  dictionary["p"] = PRINT;

  // Initialize state variables
  Register accountRegister;

  std::string input;
  while(std::getline(std::cin, input)) { // quit the program with Ctrl+D (EOF) or Ctrl+C (SIGINT)
    auto itr = dictionary.find(input);
    if ( itr != end(dictionary)) {
      switch (itr->second) {
        case LOAD : // Reload data
          accountRegister = loadData(argv[1]);
          break;
        case PRINT : // Reprint output
          accountRegister.printSplits();
          break;
        default :
          std::cout << "Command \"" << input << "\" Not Implemented" << std::endl; 
      }
    } else {
      std::cout << "command \"" << input << "\" not known" << std::endl;
    }
  }

  return 0;
}
