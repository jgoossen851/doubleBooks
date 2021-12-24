/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#include "csv.h"

#define DEBUG_MODE 0

#include <fstream>
#include <iostream>
#include <exception>

#include "strings.h"

#if DEBUG_MODE
  #include <iostream>
  #include "ansi.h"
#endif

Csv::Csv(const char * filename)
      : filename_(filename) 
      {}

StringDatabase Csv::load(){

  std::ifstream file(filename_);
  try
  {
    if (!file.good()) {
      throw std::runtime_error("Error opening file " + std::string(filename_));
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    exit(EXIT_FAILURE);
  }

  std::string line;
  StringDatabase db;
  
  #if DEBUG_MODE
    std::cout << ansi::UNDERLINE << "Contents of "
          << ansi::BOLD << ansi::ITALIC << filename_
          << ansi::RESET << ":" << std::endl;
  #endif
  
  // Initialize flags
  bool process_widths = false;
  bool process_data = false;

  // Iterate through lines until the end of the file
  while (file.eof() == false) {
    std::getline(file, line);
    #if DEBUG_MODE
      std::cout << ansi::RED << line << ansi::RESET << std::endl;
    #endif
    
    // Read first element to determine if string should be processed
    std::string first_element = line.substr(0, line.find('\t', 0));
    
    if (first_element == "ID") {
      // First, find and process headers
      db.header = delimitString_(line);
      db.number_of_columns = db.header.size();
      process_widths = true;
    } else if (process_widths) {
      // Then, process the field widths for each column
      /// @todo Get column widths from config file rather than transactions list.
      std::vector<std::string> widths = delimitString_(line);
      for (unsigned int ii = 0; ii < widths.size(); ii++) {
        db.column_width.push_back(widths.at(ii).size());
      }
      db.column_width.resize(db.number_of_columns);
      process_widths = false;
      process_data = true;
    } else if (process_data && Strings::isInteger(first_element)){
      // Finally, process the remaining data
      db.body.push_back(delimitString_(line, db.number_of_columns));
    }
  }
  
  return db;
}

std::vector<std::string> Csv::delimitString_(std::string str,
                    std::vector<std::string>::size_type max_entries) {
  
  std::vector<std::string> parsedString;
  std::string element;
  
  std::size_t pos = 0; // position to start
  std::size_t len = 0;  
  while (len != std::string::npos && parsedString.size() < max_entries) {
    len = str.find('\t', pos);
    element = str.substr(pos, len - pos);
    pos = len+1;
    // Do not allow empty elements if no size is given
    if (max_entries == (unsigned int)-1 && element.empty()) break;
    parsedString.push_back(element);
    #if DEBUG_MODE
      std::cout << "[" << ansi::YELLOW << element << ansi::RESET << "]";
    #endif
  }
  #if DEBUG_MODE
    std::cout << std::endl;
  #endif
  if (max_entries != (unsigned int)-1) parsedString.resize(max_entries);
  
  return parsedString;
}
