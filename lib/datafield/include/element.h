#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>

/// Base class for transaction elements
class Element{
  public:
  /// Function to format the element as a string
  virtual std::string str(const unsigned int &max_characters) const =0;
  /// Function to initialize the element from a string
  virtual void setFromStr(std::string str) =0;
  /// Function to return a pointer to the element's value, for comparisons
  virtual const void* value_ptr(void) const =0;
  /// Function to compare two elements
  virtual bool operator<(const Element &rhs) const =0;
  
};

#endif