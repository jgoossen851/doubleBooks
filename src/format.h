
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