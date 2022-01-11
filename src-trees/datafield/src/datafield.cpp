/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "datafield.h"

#include <string>

#include "prettyString.h"
#include "strings.h"

// Stringfield implementation

StringField::StringField(){
}

StringField::StringField(std::string str){
  setFromStr(str);
}

PrettyString StringField::str(const unsigned int &max_characters) const {
  return PrettyString((str_.size() <= max_characters) ? str_ : str_.substr(0, max_characters - 1) + "\u2026", 0);
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

UintField::UintField(uint val){
  uint_ = val;
}

PrettyString UintField::str(const unsigned int &max_characters) const {
  std::string idStr = std::to_string(uint_);
  return PrettyString((idStr.size() <= max_characters) ? idStr : std::string(max_characters, '*'), 0);
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

PrettyString BoolField::str(const unsigned int &max_characters) const {
  std::string idStr = std::to_string(bool_);
  return PrettyString((idStr.size() <= max_characters) ? idStr : std::string(max_characters, '*'), 0);
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
