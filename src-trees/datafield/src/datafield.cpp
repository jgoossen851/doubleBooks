/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "datafield.h"

#include <string>

#include "strings.h"

// Stringfield implementation

StringField::StringField(){
}

StringField::StringField(std::string str){
  setFromStr(str);
}

std::string StringField::str(const unsigned int &max_characters) const {
  return (str_.size() <= max_characters) ? str_ : std::string(max_characters, '*');
}

void StringField::setFromStr(std::string str) {
  str_ = str;
}

const void* StringField::value_ptr(void) const {
  return &str_;
}

bool StringField::operator<(const Element &rhs) const {
  return this->str_ < *static_cast<const std::string*>(rhs.value_ptr());
}

// UintField implementation

UintField::UintField(){
}

UintField::UintField(std::string str){
  setFromStr(str);
}

std::string UintField::str(const unsigned int &max_characters) const {
  std::string idStr = std::to_string(uint_);
  return (idStr.size() <= max_characters) ? idStr : std::string(max_characters, '*');
}

void UintField::setFromStr(std::string str) {
  uint_ = Strings::toInteger(str);
}

const void* UintField::value_ptr(void) const {
  return &uint_;
}

bool UintField::operator<(const Element &rhs) const {
  return this->uint_ < *static_cast<const unsigned int*>(rhs.value_ptr());
}

// BoolField implementation

BoolField::BoolField(){
}

BoolField::BoolField(std::string str){
  setFromStr(str);
}

std::string BoolField::str(const unsigned int &max_characters) const {
  std::string idStr = std::to_string(bool_);
  return (idStr.size() <= max_characters) ? idStr : std::string(max_characters, '*');
}

void BoolField::setFromStr(std::string str) {
  bool_ = Strings::toInteger(str);
}

const void* BoolField::value_ptr(void) const {
  return &bool_;
}

bool BoolField::operator<(const Element &rhs) const {
  return this->bool_ < *static_cast<const bool*>(rhs.value_ptr());
}
