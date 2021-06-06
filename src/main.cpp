#include "csv.h"
#include "table.h"

int main() {
	// Set up files
	Csv transactionsList("./data/TransactionsList.csv");
	
	// Load database
	Database data = transactionsList.load();
	
	// Print Table
	Table table(data);
	table.print();
	
	return 0;
}
