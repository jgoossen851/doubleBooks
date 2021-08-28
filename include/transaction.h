/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <vector>
// #include <iostream>

#include "currency.h"
#include "date.h"
#include "category.h"

class Entry {
 private:
  virtual int getSortValue() const =0;
  
 public:
  /// @brief Function to format the entry as a vector of strings
  virtual std::vector<std::string> formatEntry() const =0;
  
  bool operator<(const Entry &rhs) const;
};

// Forward declare classes
class Transaction;

class Record : public Entry {
 private:
  unsigned int        id_;
  // Transaction &       parent_;
  std::string         title_;
  int                 period_; // Change to class Period
  Category            category_;
  Currency            amount_;
  std::string         memo_;
  Date          date_;
  std::string   vendor_;
  bool          isBalanced_;
  
  int getSortValue() const override;
  
 public:
  // Record();
  // Record(Transaction              &parent,
  //        const std::vector<std::string> &strVec);
  Record( const unsigned int    id,
                  const std::string   title,
                  const int           period, // Change to class Period
                  const Date          date,
                  const Category      category,
                  const Currency      amount,
                  const std::string   vendor,
                  const std::string   memo,
                  const bool          isBalanced
                  );


  std::vector<std::string> formatEntry() const override;

  unsigned int        getId()           const {return id_;}
  std::string         getTitle()        const {return title_;}
  int                 getPeriod()       const {return period_;} // change to class Period
  std::string         getCategoryName() const {return category_.getName();}
  int                 getType()         const {return category_.getType();} // change to class Type
  bool                getIsExpense()    const {return category_.getIsExpense();}
  bool                getIsBudgeted()   const {return category_.getIsBudgeted();}
  Currency            getAmount()       const {return amount_;}
  Currency            getActualAmount() const {return getIsExpense() ? amount_ : -amount_;}
  std::string         getMemo()         const {return memo_;}
  Date                getDate()         const;
  bool                getIsBalanced()   const;
  std::string         getVendor()       const;
  // Transaction &       getParent()       const {return parent_;}
};


class Transaction : public Entry {
 private:
  unsigned int  id_;
  Date          date_;
  std::string   vendor_;
  bool          isBalanced_;
  
  std::vector<Record>  records_;
  
  int getSortValue() const override {
    return 13; // Placeholder
  }
  
 public:
  Transaction()  {};
  Transaction(const std::vector<std::string> strVec);

  std::vector<std::string> formatEntry() const override;

  bool addRecord(const std::vector<std::string> strVec);
  
  unsigned int  getId()         const {return id_;}
  Currency      getAmount()     const {return Currency(0);} // Placeholder
  Date          getDate()       const {return date_;}
  bool          getIsBalanced() const {return isBalanced_;}
  std::string   getVendor()     const {return vendor_;}
};

#endif
