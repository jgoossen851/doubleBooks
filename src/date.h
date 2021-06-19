#ifndef DATE_H_
#define DATE_H_

#include "element.h"

// Placeholder
class Date : public Element {
	std::string date_str;
	
  public:
  Date(){};
	std::string str(const unsigned int &max_characters = 8) const override;
	void setFromStr(std::string str) override;
	const void* value_ptr(void) const override;
	bool operator<(const Element &rhs) const override;
};

#endif