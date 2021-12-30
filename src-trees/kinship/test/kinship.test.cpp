/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */

#include "ansi.h"

#include "childOf.h"
#include "parentAddress.h"
#include "childAddress.h"
#include "parentOf.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int failTest( std::string testName,
              std::string ansString,
              std::string resultString) {
  std::cout << ansi::RED << "Test Failed: " << ansi::RESET;
  std::cout << "Test " << testName << " should be [" << ansString 
            << "] but was [" << resultString << "]" << std::endl;
  return EXIT_FAILURE;
}

int testStrings(std::string testString,
                std::string ansString ) {
  if( ansString.compare(testString) != 0) {
    return failTest("Compare", ansString, testString);
  }
  return EXIT_SUCCESS;
}

// Forward declare derived parent class
class DerivedParent;

// Define derived child class
class DerivedChild : public childOf<DerivedParent> {
  std::string childClassString_ = "Child Class";
 public:
  std::string getChildClassString(void) const { return childClassString_; };
};

// Define derived parent class
class DerivedParent : public parentOf<DerivedChild> {
  std::string parentClassString_ = "Parent Class";
 public:
  std::string getParentClassString(void) const { return parentClassString_; };
};

int main() {

  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  // ****** TEST PARENTADDRESS CLASS ****** //

  // Default Construction
  // parentAddress<int> c1; // Error

  // Test Param Constructor
  parentAddress<int> parAddr(nullptr);

  // Copy Construction
  // parentAddress<int> c2(parAddr); // Error

  // Move Construction
  // parentAddress<int> c3(std::move(parAddr)); // Error

  // Test Param Constructor
  std::string parentObject = "Parent";
  parentAddress<std::string> parAddr2(nullptr, &parentObject);

  // Test Dereference
  exitStatus |= testStrings(*parAddr2, parentObject);

  // Test Structure Dereference
  exitStatus |= testStrings(std::to_string(parAddr2->size()),
                            std::to_string(parentObject.size()));

  // Test Move Notification
  std::string newParent = "New Parent";
  parAddr2.notifyMove(&parentObject, &newParent);
  exitStatus |= testStrings(*parAddr2, newParent);

  // Test Copy Assignement Operator
  parentAddress<std::string> parAddr3(nullptr);
  parAddr3 = parAddr2;
  exitStatus |= testStrings(*parAddr3, newParent);

  // Test Move Assignement Operator
  parentAddress<std::string> parAddr4(nullptr);
  parAddr4 = std::move(parAddr2);
  exitStatus |= testStrings(*parAddr4, newParent);


  // ****** TEST CHILDADDRESS CLASS ****** //

  // Default Construction
  // childAddress<int> c4; // Error

  // Test Param Constructor
  childAddress<int> chiAddr(nullptr);

  // Copy Construction
  // childAddress<int> c5(chiAddr); // Error

  // Move Construction
  // childAddress<int> c6(std::move(chiAddr)); // Error

  // Test Param Constructor
  std::string childObject = "Child1";
  childAddress<std::string> chiAddr2(nullptr, &childObject);

  // Test Dereference
  exitStatus |= testStrings(chiAddr2.dereference(0), childObject);

  // Test Child Addition
  std::string Child2 = "Child2";
  chiAddr2.notifyAddition(&Child2);
  exitStatus |= testStrings(chiAddr2.dereference(0) + chiAddr2.dereference(1),
                            childObject + Child2);

  // Test Move Notification
  std::string Child3 = "Child3";
  chiAddr2.notifyMove(&childObject, &Child3);
  exitStatus |= testStrings(chiAddr2.dereference(0) + chiAddr2.dereference(1),
                            Child3 + Child2);

  // Test Copy Assignement Operator
  childAddress<std::string> chiAddr3(nullptr);
  // chiAddr3 = chiAddr2; // Error

  // Test Move Assignement Operator
  chiAddr3 = std::move(chiAddr2);
  exitStatus |= testStrings(chiAddr3.dereference(0) + chiAddr3.dereference(1),
                            Child3 + Child2);


  // ****** TEST DERIVED CLASSES OF PARENTOF AND CHILDOF ****** //

  DerivedParent ParentObj;
  DerivedChild ChildObj;
  exitStatus |= testStrings(ParentObj.getParentClassString(),
                            "Parent Class");
  exitStatus |= testStrings(ChildObj.getChildClassString(),
                            "Child Class");

  // Add a relationship between objects
  ChildObj.setParent(ParentObj);
  ParentObj.addChild(ChildObj);
  // TODO Make this automatic, where the child calls the parent to add itself.
  // TODO This requires the []Address classes to know something about the T return types.


  // ****** CLEAN UP ****** //

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
