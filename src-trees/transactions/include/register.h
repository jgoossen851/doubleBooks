/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef REGISTER_H_
#define REGISTER_H_

#include "csv.h"
#include "transaction.h"
#include "split.h"
#include "entry.h"

#include <vector>
#include <string>

class Register {
  const AccountList               accountList_;
  const uint                      numColumns_;
  const std::vector<std::string>  vHeader_;
  const std::vector<uint>         vColumnWidth_; //!< in characters
  std::vector<Transaction>        vTransaction_;
  std::vector<Split>              vSplit_;

 public:
  Register(StringDatabase data, const char *accountListFile);
  void printSplits(void) const;
  void printTransactions(void) const;
 private:
  /// @brief Function to print either vector of transactions or splits
  void printEntry(const Entry *entry) const;
};

#endif // REGISTER_H_
