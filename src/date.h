#ifndef DATE_H_
#define DATE_H_

// Placeholder
class Date{
  public:
	std::string date_str;
	bool operator<(const Date &rhs) const{
		return this->date_str < rhs.date_str;
	};
};

#endif