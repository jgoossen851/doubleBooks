#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <vector>

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
  unsigned int	id_;
  std::string   title_;
  int			      period_; // Change to class Period
  Category      category_;
  Currency		  amount_;
  std::string	  memo_;
  Transaction*  parent_;
  
  int getSortValue() const override;
  
 public:
  Record();
  Record(std::vector<std::string> strVec);

  std::vector<std::string> formatEntry() const override;

  std::string getTitle()        const {return title_;}
  int			    getPeriod()       const {return period_;} // change to class Period
  std::string	getCategoryName() const {return category_.getName();}
  int			    getType()         const {return category_.getType();} // change to class Type
  bool			  getIsExpense()    const {return category_.getIsExpense();}
  bool			  getIsBudgeted()   const {return category_.getIsBudgeted();}
  Currency		getAmount()       const {return amount_;}
  Currency 		getActualAmount() const {return getIsExpense() ? amount_ : -amount_;}
  std::string	getMemo()         const {return memo_;}
  Date			  getDate()         const;
  bool			  getIsBalanced()   const;
  std::string	getVendor()       const;
};


class Transaction : public Entry {
 private:
  unsigned int  id_;
  Date			    date_;
  std::string	  vendor_;
  bool			    isBalanced_;
  
  std::vector<Record>	records_;
  
  int getSortValue() const override {
    return 13; // Placeholder
  }
  
 public:
  Transaction()	{};
  Transaction(const std::vector<std::string> strVec) {
    std::vector<std::string> temp;
    temp = strVec;
  };

  std::vector<std::string> formatEntry() const override;
  
  Currency		  getAmount()     const {return Currency(0);} // Placeholder
  Date			    getDate()       const {return date_;}
  bool			    getIsBalanced() const {return isBalanced_;}
  std::string	  getVendor()     const {return vendor_;}
};

#endif