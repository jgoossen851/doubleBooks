/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef ENTRY_H_
#define ENTRY_H_

#include <string>

#include "date.h"
#include "currency.h"

class Entry {
  std::string name_;
  std::string memo_;
  std::string period_;
  Date date_;
  std::string vendor_;
  
 public:
  /// Getter/Setter Functions
  virtual std::string getName() const =0;
  virtual void setName(std::string name) =0;
  virtual std::string getMemo() const =0;
  virtual void setMemo(std::string memo) =0;
  virtual std::string getPeriod() const =0;
  virtual void setPeriod(std::string period) =0;
  virtual Date getDate() const =0;
  virtual void setDate(Date date) =0;
  virtual std::string getVendor() const =0;
  virtual void setVendor(std::string vendor) =0;

  virtual Currency getDebitSum() const =0;
  virtual Currency getCreditSum() const =0;

};

#endif // ENTRY_H_
