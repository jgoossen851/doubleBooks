
#include "transaction.h"

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

/// Create a Record given a pointer to the parent transaction
Record::Record(const Transaction*             parent,
               const std::vector<std::string> strVec)
      : parent_(parent),
        amount_(Currency(NEGATIVE_SIGN)) {
  
  id_       = Strings::toInteger(strVec.at(DB_ID));
  title_    = strVec.at(DB_TITLE);
  period_   = Strings::toInteger(strVec.at(DB_PERIOD));
  memo_     = strVec.at(DB_MEMO);
  category_.setFromStr(strVec.at(DB_CATEGORY));
  amount_.setFromStr(strVec.at(DB_AMOUNT));

}


std::vector<std::string> Record::formatEntry() const {
  std::vector<std::string> strVec;
  strVec.push_back(std::to_string(id_)); // ID
  strVec.push_back(title_); // Title
  strVec.push_back(std::to_string(period_)); // Period
  strVec.push_back(parent_->getDate().str()); // Date
  strVec.push_back(category_.getName()); // Category
  strVec.push_back(amount_.str()); // Amount
  strVec.push_back(memo_); // Memo
  strVec.push_back(std::to_string(parent_->getIsBalanced())); // Balanced
  return strVec;
}

Date        Record::getDate()         const {return parent_->getDate();}
bool        Record::getIsBalanced()   const {return parent_->getIsBalanced();}
std::string Record::getVendor()       const {return parent_->getVendor();}


// TRANSACTION

Transaction::Transaction(const std::vector<std::string> strVec){
  id_         = Strings::toInteger(strVec.at(DB_ID));
  vendor_     = strVec.at(DB_VENDOR);
  isBalanced_ = Strings::toInteger(strVec.at(DB_STATEMENT));
  date_.setFromStr(strVec.at(DB_DATE));

  addRecord(strVec);
}

bool Transaction::addRecord(const std::vector<std::string> strVec) {
  Record new_record(this, strVec);
  records_.push_back(new_record);
  return true;
}

std::vector<std::string> Transaction::formatEntry() const {
  std::vector<std::string> strVec;
  const int numRecords = records_.size();
  if (numRecords == 1) {
    strVec = records_.at(0).formatEntry();
  } else {
    strVec.push_back(std::to_string(id_)); // ID
    strVec.push_back(vendor_ + " Transaction"); // Title
    strVec.push_back(""); // Period
    strVec.push_back(date_.str()); // Date
    strVec.push_back(""); // Category
    strVec.push_back(getAmount().str()); // Amount
    strVec.push_back("Containing " + std::to_string(numRecords) + " records"); // Memo
    strVec.push_back(std::to_string(isBalanced_)); // Balanced
  }
  return strVec;
}
