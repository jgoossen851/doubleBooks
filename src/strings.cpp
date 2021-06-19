
#include "strings.h"

namespace Strings {
  
/// Function to determine if a string is an integer
bool isInteger(const std::string str) {
  
  // Iterate throught the string until a non-digit is encountered
  std::string::const_iterator it = str.begin();
  while (it != str.end() && std::isdigit(*it)) ++it;
  
  return !str.empty() && it == str.end();
}

unsigned long toInteger(const std::string str) {
  return isInteger(str) ? std::stoul(str, nullptr) : (unsigned long)(-1);
}

// bool          isFloat(const std::string str){return false;}

float         toFloat(const std::string str){
  return (str == "") ? 0.0 : std::stof(str, nullptr);
}

} // namespace Strings
