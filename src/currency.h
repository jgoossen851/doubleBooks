#ifndef CURRENCY_H_
#define CURRENCY_H_

#include <string>

#include "element.h"

/// Allowable formats for negative currencies
enum NegativeFormat{
	NEGATIVE_SIGN, 	/// Value printed to the right of a negative sign
	PARENTHESIS,	/// Value printed inside parenthesis	
	RED_COLOR 		/// Value printed in red
};

class Currency : public Element {
	/// Internal Storage of the currency value, in cents
	int cents;
	
  public:
	Currency(NegativeFormat negativeFormat = NEGATIVE_SIGN)
		: negativeFormat_(negativeFormat)
		{}
		
	// Function Overrides
	/// Format the dollar amount as a string
	std::string str(const unsigned int &max_characters = 10) const;	
	void setFromStr(std::string str) override;
	const void* value_ptr(void) const override {return &cents;}
	/// Comparison operator for two Currency objects
	bool operator<(const Element &rhs) const override;
	
  private:	
	std::string display_magnitude(const int &max_characters) const;
	std::string format_negative_string(std::string positiveString) const;
	const NegativeFormat negativeFormat_;
};

#endif