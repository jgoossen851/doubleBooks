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
  Transaction *pParent_;
  Currency amount_;
  Account debitAccount_;
  Account creditAccount_;

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
  Currency getAmount() const { return Currency(); };
  void setAmount(Currency amount) {};
  unsigned int getId() const { return 0; };
  void setId(unsigned int id) {};


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
  void setParentTransaction(Transaction *testTransaction) {};

};

#endif // SPLIT_H_
