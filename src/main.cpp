#include "csv.h"
#include "table.h"
#include "currency.h"
#include "transaction.h"

#include <iostream>

int main() {
	// Set up files
	Csv transactionsList("./data/TransactionsList.csv");
	
	// Load database
	StringDatabase data = transactionsList.load();
	
	// Print Table
	Table table(data);
	table.print();
	
	
	// Currency amount(PARENTHESIS);
	
	// std::cout << "\033[1m";
	
	// amount.cents = -12345;
	// std::cout << amount.display() << std::endl;
	
	// std::cout << "\033[33m";
	
	// amount.cents = -123456;
	// std::cout << amount.display() << std::endl;
	
	// amount.cents = -1234567;
	// std::cout << amount.display() << std::endl;
	
	// amount.cents = -12345678;
	// std::cout << amount.display() << std::endl;
	
	// amount.cents = -123456789;
	// std::cout << amount.display(15) << std::endl;
	
	// amount.cents = 11;
	// std::cout << amount.display() << std::endl;
	
	// amount.cents = -0255;
	// std::cout << amount.display() << std::endl;
	
	// amount.cents = 0;
	// std::cout << amount.display() << std::endl;
	
	// amount.cents = -134;
	// std::cout << amount.display() << std::endl;
	
	// Transaction trans;
	// trans.transaction_amount.cents = -123;
	// std::cout << trans.transaction_amount.display() << std::endl;
	
	
	return 0;
}
