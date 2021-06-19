
#include "category.h"

// std::vector<CategoryDescriptions> Category::categoryList_;

bool Category::operator<(const Element &rhs) const {
  return *(static_cast<const int*>(this->value_ptr())) < *(static_cast<const int*>(rhs.value_ptr()));
}
