#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <string>

// Placeholder: implement as file with IDs and Categories.
enum CategoryList{
	Savings,
	Taxes,
	Allocations,
	Household,
	WagesSalary,
	Miscellaneous
};

class Category{
  public:
	Category(){};
	
	CategoryList cat;
	
	Category setFromStr(std::string str){
		// cat = (CategoryList)std::stoi(str, nullptr); // Placeholder
		cat = (CategoryList)str.size(); // Placeholder
		return *this;
	}
	
	bool operator<(const Category &rhs) const {
		return this->cat < rhs.cat;
	}
};

#endif