#ifndef DATE_H_
#define DATE_H_

#include "element.h"

// Placeholder
class Date : public Element {
	std::string date_str;
	
  public:
	std::string str(const unsigned int &max_characters = 8) const override {
		if (date_str.size() <= max_characters) {
			return date_str;
		} else {
			return std::string(max_characters, '*');
		}
	}
	void setFromStr(std::string str) override {
		date_str = str;
	}
	const void* value_ptr(void) const override {return &date_str;}
	bool operator<(const Element &rhs) const override {
		return this->date_str < *static_cast<const std::string*>(rhs.value_ptr());
	}
};

#endif