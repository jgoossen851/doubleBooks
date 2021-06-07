#ifndef CURRENCY_H_
#define CURRENCY_H_

#include <string>

/// Allowable formats for negative currencies
enum NegativeFormat{
	NEGATIVE_SIGN, 	/// Value printed to the right of a negative sign
	PARENTHESIS,	/// Value printed inside parenthesis	
	RED_COLOR 		/// Value printed in red
};

class Currency{
  public:
	Currency(NegativeFormat negativeFormat = NEGATIVE_SIGN)
		: negativeFormat_(negativeFormat)
		{}

	/// Internal Storage of the currency value, in cents
	int cents;
	/// Getter function for the currency value in dollars
	float dollars(void) const;
	/// Display the formatted dollar amount
	std::string display(const int &max_characters = 10) const;
	/// Comparison operator for two Currency objects
	bool operator<(const Currency &rhs) const;
	
	Currency setFromStr(std::string str);
	
  private:	
	std::string display_magnitude(const int &max_characters) const;
	std::string format_negative_string(std::string positiveString) const;
	const NegativeFormat negativeFormat_;
};

#endif