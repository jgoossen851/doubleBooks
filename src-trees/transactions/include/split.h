/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef SPLIT_H_
#define SPLIT_H_

#include "account.h"
#include "childOf.h"
#include "currency.h"
#include "entry.h"

class Transaction;

class Split : public Entry, public childOf<Transaction> {
  unsigned int id_;
  Currency amount_;
  Account debitAccount_;
  Account creditAccount_;

 public:

  Split(AccountList *pAcctList)
      : debitAccount_(pAcctList),
        creditAccount_(pAcctList)
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
  Currency getAmount() const override { return amount_; };
  void setAmount(const Currency amount) { amount_ = amount; };
  uint getId() const override { return id_; };
  void setId(const unsigned int id) { id_ = id; };


  Currency getDebitSum() const override {
    return getDebitAccountInd() == 0 ? Currency() : amount_;
  };
  Currency getCreditSum() const override {
    return getCreditAccountInd() == 0 ? Currency() : amount_;
  };
  unsigned int getDebitAccountInd() const {
    return debitAccount_.getAccountInd();
  };
  unsigned int getCreditAccountInd() const {
    return creditAccount_.getAccountInd();
  };
  Account getDebitAccount() const override { return debitAccount_; };
  void setDebitAccount(std::string acctNum) {
    debitAccount_.setFromStr(acctNum);
  };
  Account getCreditAccount() const override { return creditAccount_; };
  void setCreditAccount(std::string acctNum) {
    creditAccount_.setFromStr(acctNum);
  };

};

#endif // SPLIT_H_
