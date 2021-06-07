#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <string>

#include "element.h"

// Placeholder: implement as file with IDs and Categories.
enum CategoryList{
	Savings,
	Taxes,
	Allocations,
	Household,
	WagesSalary,
	Miscellaneous
};


class Category : public Element {
	CategoryList cat;
	
  public:
	Category(){};
	
	std::string str(const unsigned int &max_characters = 12) const override {
		return std::string(max_characters, '*');
	}
	void setFromStr(std::string str) override {
		// cat = (CategoryList)std::stoi(str, nullptr); // Placeholder
		cat = (CategoryList)str.size(); // Placeholder
		return;
	}
	const void* value_ptr(void) const override {return &cat;}
	bool operator<(const Element &rhs) const override {
		return this->cat < *static_cast<const CategoryList*>(rhs.value_ptr());
	}
};

#endif