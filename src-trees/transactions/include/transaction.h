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
  std::string getName() const override { return name_; };
  void setName(std::string name) override { name_ = name; };
  std::string getMemo() const override { return memo_; };
  void setMemo(std::string memo) override { memo_ = memo; };
  std::string getPeriod() const override { return period_; };
  void setPeriod(std::string period) override { period_ = period; };
  Date getDate() const override { return date_; };
  void setDate(Date date) override { date_ = date; };
  std::string getVendor() const override { return vendor_; };
  void setVendor(std::string vendor) override { vendor = vendor_; };
  unsigned int getId() const { return id_; };
  void setId(unsigned int id) { id_ = id; };

  Currency getDebitSum() const override { return Currency(); };
  Currency getCreditSum() const override { return Currency(); };

};

#endif // TRANSACTION_H_
