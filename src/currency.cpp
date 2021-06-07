#include "currency.h"

#include <cstdio>
#include <cmath>
#include <cassert>

#include "ansi.h"

float Currency::dollars(void) const {
	return (float)cents/100;
}

std::string Currency::display(const int &max_characters) const {
	if (cents < 0) {
		// Format negative number
		int characters = max_characters;
		switch (negativeFormat_) {
			case NEGATIVE_SIGN :
				characters--; 		// Reserve space for negative sign
				break;
			case PARENTHESIS :
				characters -= 2; 	// Reserve space for parenthesis
				break;
			case RED_COLOR :
			default :
				break;
		}
		return format_negative_string(display_magnitude(characters));
	} else {
		// Format positive number
		return display_magnitude(max_characters);
	}
}

std::string Currency::display_magnitude(const int &max_chars) const {
	constexpr int buffer_len = 16;
	assert(buffer_len > max_chars + 1); // Ensure buffer can fit all characters and null terminator
	char display_value[buffer_len];
	int chars = snprintf( display_value, buffer_len, "$%04.2f", (float)abs(cents)/100);
	return (chars <= max_chars)
				? std::string(display_value)
				: std::string(max_chars, '*');	
}

std::string Currency::format_negative_string(std::string positiveString) const {
	std::string negativeString;
	
	switch (negativeFormat_) {
		case NEGATIVE_SIGN :
			negativeString = "-" + positiveString;
			break;
		case PARENTHESIS :
			negativeString = "(" + positiveString + ")";
			break;
		case RED_COLOR :
			negativeString = ansi::SAVE_ATTRIBUTES + ansi::RED + positiveString + ansi::RESTORE_ATTRIBUTES;
			break;
		default :
			negativeString = "-" + positiveString;
	}
	
	return negativeString;
}

bool Currency::operator<(const Currency &rhs) const {
	return this->cents < rhs.cents;
}

Currency Currency::setFromStr(std::string str) {
	float dollars = std::stof(str, nullptr);
	cents = round(dollars*100);
	float residual = cents - dollars*100;
	assert(abs(residual) < 0.001);
	return *this;
}


