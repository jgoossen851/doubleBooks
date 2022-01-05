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
  AccountList                     accountList_;
  uint                            numColumns_;
  std::vector<std::string>        vHeader_;
  std::vector<uint>               vColumnWidth_; //!< in characters
  std::vector<Transaction>        vTransaction_;
  std::vector<Split>              vSplit_;

 public:
  Register(){};
  Register(StringDatabase data, const char *accountListFile);
  /// Move Constructor
  Register(Register&& rhs) noexcept = default;
  /// Move Assignment Operator
  Register& operator=(Register&& other) noexcept = default;
  void printSplits(void) const;
  void printTransactions(void) const;
 private:
  /// @brief Function to print either vector of transactions or splits
  void printEntry(const Entry *entry) const;
  void printHeader() const;
  void printElement(std::string str, uint width, uint space) const;
};

#endif // REGISTER_H_
