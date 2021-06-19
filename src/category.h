#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <string>
#include <vector>
#include <iostream>

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

extern std::vector<CategoryDescriptions>  gCategoryList_;



class Category : public Element {
  // static std::vector<CategoryDescriptions>  categoryList_;
  unsigned int    id_;
  
 public:
  Category(){
    // categoryList_.clear();
  };
  Category(std::string str){
    setFromStr(str);
  }
  
  std::string str(const unsigned int &max_characters = 12) const override {
    return std::string(max_characters, '*'); // Placeholder
  }
  void setFromStr(std::string str) override {
    id_ = str.size(); // Placeholder
    return;
  }
  const void* value_ptr(void) const override {return &gCategoryList_[id_].displayOrder_;}
  bool operator<(const Element &rhs) const override;

  /// @todo Placeholder
  CategoryDescriptions getDescription() const {
    if (id_ >= gCategoryList_.size()){
      std::cout << "ERROR: Id is too high. Id = " << id_ << " and size = " << gCategoryList_.size() << std::endl;
      return gCategoryList_.at(0);
    }
    return gCategoryList_.at(id_);
  }
  std::string getName()       const {return getDescription().name_;}
  int         getType()       const {return getDescription().type_;}
  bool        getIsExpense()  const {return getDescription().isExpense_;}
  bool        getIsBudgeted() const {return getDescription().isBudgeted_;}
};

#endif