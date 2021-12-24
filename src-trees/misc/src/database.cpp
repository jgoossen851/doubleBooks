/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "database.h"

#include <cassert>
// #include <iostream>

#include "strings.h"

template<FormatVersion VER>
Database<VER>::Database(const StringDatabase &strDb)
          : number_of_columns(Format<VER>::columns()),
            header(strDb.header),
            column_width(strDb.column_width) {
  assert(this->number_of_columns == strDb.number_of_columns);
  formatData_(strDb.body);
}
// Template Instantiation
template Database<A1>::Database(const StringDatabase&);


template<FormatVersion VER>
bool Database<VER>::formatData_(const std::vector<std::vector<std::string>> &data_str){
  for (unsigned int ii = 0; ii < data_str.size(); ii++) {

    std::vector<std::string> currentEntry = data_str.at(ii);

    // Create a new transaction if the Parent is self-referring or empty
    if (currentEntry.at(DB_ID) == currentEntry.at(DB_PARENT) || currentEntry.at(DB_PARENT) == "") {
      // std::cout << "Make a new transaction." << std::endl;
      Transaction2 new_transaction(currentEntry);
      body.push_back(new_transaction);

    } else {
      // std::cout << "Adding to an existing transaction" << std::endl;
      unsigned int parentID = Strings::toInteger(currentEntry.at(1));
      // Iterate through the body to find the parent
      auto bodyIterator = body.rbegin(); // Set iterator at the reverse beginning (at the back)
      while (bodyIterator != body.rend()) {
        if (bodyIterator->getId() == parentID) {
          // std::cout << "Found the parent!" << std::endl;
          bodyIterator->addRecord(currentEntry);
          break;
        }
        bodyIterator++; // Iterate toward the reverse end
      }
    }
    // std::cout << "Finished Formatting Record" << std::endl;
  }
  // std::cout << "Finished Formatting Data" << std::endl;
  return true;
}
// Template Instantiation
template bool Database<A1>::formatData_(const std::vector<std::vector<std::string>> &);
