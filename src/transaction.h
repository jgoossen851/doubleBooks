#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <vector>

#include "currency.h"
#include "date.h"
#include "category.h"

class Transaction{
  public:
	Transaction()
		: transaction_amount(Currency(NEGATIVE_SIGN))
		{};
  
	unsigned int 	id;
	std::string 	entry_title;
	unsigned int 	entry_number;
	Date		 	entry_date;
	Category 		category;
	Currency 		transaction_amount;
	std::string 	memo;
	bool 			statement;

	// Define functions to compare fields for std::sort()
	bool IdCmp(Transaction const &A, Transaction const &B) {
		return A.id < B.id;
	}
	bool TitleCmp(Transaction const &A, Transaction const &B) {
		return A.entry_title < B.entry_title;
	}
	bool NumberCmp(Transaction const &A, Transaction const &B) {
		return A.entry_number < B.entry_number;
	}
	bool DateCmp(Transaction const &A, Transaction const &B) {
		return A.entry_date < B.entry_date;
	}
	bool CategoryCmp(Transaction const &A, Transaction const &B) {
		return A.category < B.category;
	}
	bool AmountCmp(Transaction const &A, Transaction const &B) {
		return A.transaction_amount < B.transaction_amount;
	}
	bool MemoCmp(Transaction const &A, Transaction const &B) {
		return A.memo < B.memo;
	}
	bool StatementCmp(Transaction const &A, Transaction const &B) {
		return A.statement < B.statement;
	}
	
};

#endif