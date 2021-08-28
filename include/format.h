/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef FORMAT_H_
#define FORMAT_H_

/// Database formats and versions
enum FormatVersion {
  A1,
};

template<FormatVersion VER>
class Format {
 public:
  static unsigned int columns(void) {
    switch (VER) {
      case A1 :
        return 10;
        break;
      default :
        return 0;
        break;
    };
  };
};
// Template instantiation
template unsigned int Format<A1>::columns(void);

enum DatabaseColumns {
  DB_ID,
  DB_PARENT,
  DB_TITLE,
  DB_PERIOD,
  DB_DATE,
  DB_CATEGORY,
  DB_AMOUNT,
  DB_VENDOR,
  DB_MEMO,
  DB_STATEMENT,
};

#endif
