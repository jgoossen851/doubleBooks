/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <vector>

#include "currency.h"
#include "parentOf.h"
#include "split.h"
#include "entry.h"
#include "account.h"

class Transaction : public Entry, public parentOf<Split> {
  unsigned int id_;

 public:
  StringField getName() const override { return name_; };
  void setName(const std::string name) override { name_ = name; };
  StringField getMemo() const override { return memo_; };
  void setMemo(const std::string memo) override { memo_ = memo; };
  StringField getPeriod() const override { return period_; };
  void setPeriod(const std::string period) override { period_ = period; };
  Date getDate() const override { return date_; };
  void setDate(const Date date) override { date_ = date; };
  StringField getVendor() const override { return vendor_; };
  void setVendor(const std::string vendor) override { vendor_ = vendor; };
  uint getId() const override { return id_; };
  void setId(const unsigned int id) { id_ = id; };

  Currency getDebitSum() const override;
  Currency getCreditSum() const override;
  Currency getAmount() const override {
    // Get sum of all debits (since debits and credits should be equal across transaction)
    return getDebitSum();
  }
  Account getCreditAccount(void) const override;
  Account getDebitAccount(void) const override;

};

#endif // TRANSACTION_H_