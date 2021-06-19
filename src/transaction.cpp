
#include "transaction.h"

#include <iostream>
#include <cassert>

#include "format.h"
#include "strings.h"

// ENTRY

bool Entry::operator<(const Entry &rhs) const {
  return (*this).getSortValue() < rhs.getSortValue();
}


// RECORD

int Record::getSortValue() const {
  return 17;
}

// Record::Record() 
//     : parent_(nullptr),
//       amount_(Currency(NEGATIVE_SIGN)){
// }

// /// Create a Record given a reference to the parent transaction
// Record::Record(Transaction                    &parent,
//                const std::vector<std::string> &strVec)
//       : parent_(parent),
//         amount_(Currency(NEGATIVE_SIGN)) {
  
//   id_       = Strings::toInteger(strVec.at(DB_ID));
//   title_    = strVec.at(DB_TITLE);
//   period_   = Strings::toInteger(strVec.at(DB_PERIOD));
//   memo_     = strVec.at(DB_MEMO);
//   category_.setFromStr(strVec.at(DB_CATEGORY));
//   amount_.setFromStr(strVec.at(DB_AMOUNT));

// }

/// Create a Record
Record::Record( const unsigned int    id,
                const std::string   title,
                const int           period, // Change to class Period
                const Date          date,
                const Category      category,
                const Currency      amount,
                const std::string   vendor,
                const std::string   memo,
                const bool          isBalanced
                )
    : amount_(Currency(NEGATIVE_SIGN)) {

  id_         = id;
  title_      = title;
  period_     = period;
  date_       = date;
  category_   = category;
  amount_     = amount;
  vendor_     = vendor;
  memo_       = memo;
  isBalanced_ = isBalanced;
}




std::vector<std::string> Record::formatEntry() const {
      std::cout << "Beginning to format entry for Record." << std::endl;
  std::vector<std::string> strVec;
  strVec.push_back(std::to_string(id_));                      // ID
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back("");         // Parent
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(title_);                                   // Title
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(std::to_string(period_));                  // Period
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
      std::cout << "0" << std::endl;
      // std::cout << parent_ << std::endl;
      // Date theDate = parent_.getDate();
      std::cout << "1" << std::endl;
      // std::string theDateString = theDate.str();
      std::cout << "2" << std::endl;
      // strVec.push_back(theDateString);                 // Date
  strVec.push_back(date_.str());                              // Date
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(category_.getName());                      // Category
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(amount_.str());                            // Amount
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(vendor_);                     // Vendor
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(memo_);                                    // Memo
      std::cout << "Pushed Record #" << strVec.size() << std::endl;
  strVec.push_back(std::to_string(isBalanced_)); // Balanced
      std::cout << "Finished to format entry for Record." << std::endl;
  assert(strVec.size() == Format<A1>::columns() && "Vector does not contain enought elements after formatting Record");
  return strVec;
}

// Date        Record::getDate()         const {return parent_.getDate();}
// bool        Record::getIsBalanced()   const {return parent_.getIsBalanced();}
// std::string Record::getVendor()       const {return parent_.getVendor();}

Date        Record::getDate()         const {return date_;}
bool        Record::getIsBalanced()   const {return isBalanced_;}
std::string Record::getVendor()       const {return vendor_;}


// TRANSACTION

Transaction::Transaction(const std::vector<std::string> strVec){
  id_         = Strings::toInteger(strVec.at(DB_ID));
  vendor_     = strVec.at(DB_VENDOR);
  isBalanced_ = Strings::toInteger(strVec.at(DB_STATEMENT));
  date_.setFromStr(strVec.at(DB_DATE));
  std::cout << "Transaction date set to " << date_.str() << std::endl;

  addRecord(strVec);
  // addRecord(id_, 
  //           strVec.at(DB_TITLE), 
  //           Strings::toInteger(strVec.at(DB_PERIOD)), 
  //           date_, 
  //           Category(strVec.at(DB_CATEGORY)), 
  //           Currency(strVec.at(DB_AMOUNT)), 
  //           vendor_, 
  //           strVec.at(DB_MEMO), 
  //           isBalanced_);
}

bool Transaction::addRecord(const std::vector<std::string> strVec) {
  return addRecord( id_, 
                    strVec.at(DB_TITLE), 
                    Strings::toInteger(strVec.at(DB_PERIOD)), 
                    date_, 
                    Category(strVec.at(DB_CATEGORY)), 
                    Currency(strVec.at(DB_AMOUNT)), 
                    vendor_, 
                    strVec.at(DB_MEMO), 
                    isBalanced_);
}
bool Transaction::addRecord(const unsigned int  id,
                            const std::string   title,
                            const int           period, // Change to class Period
                            const Date          date,
                            const Category      category,
                            const Currency      amount,
                            const std::string   vendor,
                            const std::string   memo,
                            const bool          isBalanced
                            ){
  Record new_record(id, title, period, date, category, amount, vendor, memo, isBalanced);
  records_.push_back(new_record);
  return true;
}

std::vector<std::string> Transaction::formatEntry() const {
  std::cout << "Beginning to format entry for Transaction." << std::endl;
  std::vector<std::string> strVec;
  const int numRecords = records_.size();
  if (numRecords == 1) {
    strVec = records_.at(0).formatEntry();
    assert(strVec.size() == Format<A1>::columns() && "Vector does not contain enought elements after formatting Transaction with single Record");
  } else {
    strVec.push_back(std::to_string(id_));      // ID
    strVec.push_back("");                       // Parent
    strVec.push_back(vendor_ + " Transaction"); // Title
    strVec.push_back("");                       // Period
    strVec.push_back(date_.str());              // Date
    strVec.push_back("");                       // Category
    strVec.push_back(getAmount().str());        // Amount
    strVec.push_back("");                       // Vendor
    strVec.push_back("Containing " + std::to_string(numRecords) + " records"); // Memo
    strVec.push_back(std::to_string(isBalanced_)); // Balanced
    assert(strVec.size() == Format<A1>::columns() && "Vector does not contain enought elements after formatting Transaction with multiple Record");
  }
  return strVec;
}
