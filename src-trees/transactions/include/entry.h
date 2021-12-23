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
#include "datafield.h"

class Entry {
 protected:
  StringField name_;
  StringField memo_;
  StringField period_;
  Date date_;
  StringField vendor_;
  
 public:
  /// Getter/Setter Functions
  virtual StringField getName() const =0;
  virtual void setName(const std::string name) =0;
  virtual StringField getMemo() const =0;
  virtual void setMemo(const std::string memo) =0;
  virtual StringField getPeriod() const =0;
  virtual void setPeriod(const std::string period) =0;
  virtual Date getDate() const =0;
  virtual void setDate(const Date date) =0;
  virtual StringField getVendor() const =0;
  virtual void setVendor(const std::string vendor) =0;

  virtual Currency getDebitSum() const =0;
  virtual Currency getCreditSum() const =0;

};

#endif // ENTRY_H_
