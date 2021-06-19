
#ifndef STRINGS_H_
#define STRINGS_H_

#include <string>

namespace Strings {

  bool          isInteger(const std::string str);
  unsigned long toInteger(const std::string str);
  float         toFloat(const std::string str);

} // namespace Strings

#endif
