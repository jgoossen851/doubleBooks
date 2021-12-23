/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef SPLIT_H_
#define SPLIT_H_

#include "account.h"
#include "currency.h"
#include "entry.h"

class Transaction;

class Split : public Entry {
  unsigned int id_;
  Transaction *pParent_ = nullptr;
  Currency amount_;
  Account debitAccount_;
  Account creditAccount_;

 public:
  
  std::string getName() const override;
  void setName(std::string name) override { name_ = name; };
  std::string getMemo() const override;
  void setMemo(std::string memo) override { memo_ = memo; };
  std::string getPeriod() const override;
  void setPeriod(std::string period) override { period_ = period; };
  Date getDate() const override;
  void setDate(Date date) override { date_ = date; };
  std::string getVendor() const override;
  void setVendor(std::string vendor) override { vendor_ = vendor; };
  Currency getAmount() const { return amount_; };
  void setAmount(Currency amount) { amount_ = amount; };
  unsigned int getId() const { return id_; };
  void setId(unsigned int id) { id_ = id; };


  Currency getDebitSum() const override { return Currency(); };
  Currency getCreditSum() const override { return Currency(); };
  unsigned int getDebitAccountInd() const {
    return debitAccount_.getAccountInd();
  };
  unsigned int getCreditAccountInd() const {
    return creditAccount_.getAccountInd();;
  };
  void setDebitAccount(unsigned int acctNum) {};
  void setCreditAccount(unsigned int acctNum) {};
  void setParentTransaction(Transaction *testTransaction) {
    pParent_ = testTransaction;
  };

};

#endif // SPLIT_H_
