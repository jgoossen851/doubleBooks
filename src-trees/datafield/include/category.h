/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

#include "element.h"

class CategoryDescriptions {
 public:
  const int           id_;
  const std::string   name_;
  const int           type_; // Change typename
  const int           displayOrder_;
  const bool          isExpense_;
  const bool          isBudgeted_;

  CategoryDescriptions( const int id,
                        const std::string name,
                        const int type,
                        const int displayOrder,
                        const bool isExpense,
                        const bool isBudgeted)
      : id_(id), name_(name), type_(type),
        displayOrder_(displayOrder), isExpense_(isExpense),
        isBudgeted_(isBudgeted) {};

  friend class Category;
};

/// @todo Remove global variable. Construct Categories with a category list.
// extern std::vector<CategoryDescriptions>  gCategoryList_;

class Category : public Element {
  /// @todo Reenable this internal category list. Make a reference to allow all categories to share the same list?
  // static std::vector<CategoryDescriptions>  categoryList_;
  unsigned int    id_;
  
 public:
  Category(){};
  Category(std::string str){
    setFromStr(str);
  }
  
  std::string str(const unsigned int &max_characters = 12) const override {
    return std::string(max_characters, '*'); // Placeholder
  }
  void setFromStr(std::string str) {
    id_ = str.size(); // Placeholder
    return;
  }
  const void* value_ptr(void) const override {return nullptr;} // Placeholder         &gCategoryList_[id_].displayOrder_;}
  bool operator<(const Element &rhs) const override;

  CategoryDescriptions getDescription() const {
    return CategoryDescriptions(0,  "", 0, 0, false, false); // Placeholder
    // if (id_ >= gCategoryList_.size()){ /// @todo Placeholder
    //   std::cout << "ERROR: Id is too high. Id = " << id_ << " and size = " << gCategoryList_.size() << std::endl;
    //   return gCategoryList_.at(0); 
    // }
    // // Do bounds check on id_ in cagetory list
    // assert(id_ < gCategoryList_.size() && "No entry in Category List for this ID");
    // return gCategoryList_.at(id_);
  }
  std::string getName()       const {return getDescription().name_;}
  int         getType()       const {return getDescription().type_;}
  bool        getIsExpense()  const {return getDescription().isExpense_;}
  bool        getIsBudgeted() const {return getDescription().isBudgeted_;}
};

#endif
