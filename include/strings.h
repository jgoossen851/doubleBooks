/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef STRINGS_H_
#define STRINGS_H_

#include <string>

namespace Strings {

  bool          isInteger(const std::string str);
  unsigned long toInteger(const std::string str);
  float         toFloat(const std::string str);
  double        toDouble(const std::string str);

} // namespace Strings

#endif
