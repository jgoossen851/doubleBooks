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
  const AccountList *pAcctList_;
  Account debitAccount_;
  Account creditAccount_;

 public:

  Split(AccountList *pAcctList)
      : pAcctList_(pAcctList),
        debitAccount_(pAcctList_),
        creditAccount_(pAcctList_)
      {};
  
  StringField getName() const override;
  void setName(const std::string name) override { name_ = name; };
  StringField getMemo() const override;
  void setMemo(const std::string memo) override { memo_ = memo; };
  StringField getPeriod() const override;
  void setPeriod(const std::string period) override { period_ = period; };
  Date getDate() const override;
  void setDate(const Date date) override { date_ = date; };
  StringField getVendor() const override;
  void setVendor(const std::string vendor) override { vendor_ = vendor; };
  Currency getAmount() const { return amount_; };
  void setAmount(const Currency amount) { amount_ = amount; };
  unsigned int getId() const { return id_; };
  void setId(const unsigned int id) { id_ = id; };


  Currency getDebitSum() const override { return Currency(); };
  Currency getCreditSum() const override { return Currency(); };
  unsigned int getDebitAccountInd() const {
    return debitAccount_.getAccountInd();
  };
  unsigned int getCreditAccountInd() const {
    return creditAccount_.getAccountInd();
  };
  Account getDebitAccount() const { return debitAccount_; };
  void setDebitAccount(std::string acctNum) {
    debitAccount_.setFromStr(acctNum);
  };
  Account getCreditAccount() const { return creditAccount_; };
  void setCreditAccount(std::string acctNum) {
    creditAccount_.setFromStr(acctNum);
  };

  void setParentTransaction(Transaction *testTransaction) {
    pParent_ = testTransaction;
  };

};

#endif // SPLIT_H_
