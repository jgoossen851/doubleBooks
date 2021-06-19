#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <string>
#include <vector>

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


class Category : public Element {
  static std::vector<CategoryDescriptions>  categoryList_;
  int                                       id_;
  
 public:
  Category(){
    categoryList_.clear();
  };
  
  std::string str(const unsigned int &max_characters = 12) const override {
    return std::string(max_characters, '*'); // Placeholder
  }
  void setFromStr(std::string str) override {
    id_ = str.size(); // Placeholder
    return;
  }
  const void* value_ptr(void) const override {return &categoryList_[id_].displayOrder_;}
  bool operator<(const Element &rhs) const override;

  std::string getName()       const {return categoryList_[id_].name_;}
  int         getType()       const {return categoryList_[id_].type_;}
  bool        getIsExpense()  const {return categoryList_[id_].isExpense_;}
  bool        getIsBudgeted() const {return categoryList_[id_].isBudgeted_;}
};

#endif