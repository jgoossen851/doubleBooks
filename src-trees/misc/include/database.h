/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>

#include "transaction.h"
#include "format.h"
#include "csv.h"

/// Formatted database
template<FormatVersion VER>
struct Database{
 public:
  Database(const StringDatabase &strDb);
    
  const std::vector<std::string>::size_type number_of_columns;
  const std::vector<std::string>            header;
  const std::vector<unsigned int>           column_width; // in characters
  std::vector<Transaction>                  body;
  
 private:
  bool formatData_(const std::vector<std::vector<std::string>> &data_str);
};

#endif
