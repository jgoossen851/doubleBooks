/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <vector>

#include "split.h"
#include "entry.h"


class Transaction : public Entry {
  unsigned int id_;
  std::vector<Split*> vSplitAddr_;

 public:
  std::string getName() const override { return ""; };
  void setName(std::string name) override {};
  std::string getMemo() const override { return ""; };
  void setMemo(std::string memo) override {};
  std::string getPeriod() const override { return ""; };
  void setPeriod(std::string period) override {};
  Date getDate() const override { return Date(); };
  void setDate(Date date) override {};
  std::string getVendor() const override { return ""; };
  void setVendor(std::string vendor) override {};
  unsigned int getId() const { return 0; };
  void setId(unsigned int id) {};

  Currency getDebitSum() const override { return Currency(); };
  Currency getCreditSum() const override { return Currency(); };

};

#endif // TRANSACTION_H_
