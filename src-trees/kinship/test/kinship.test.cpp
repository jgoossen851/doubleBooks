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
  std::string name = "Child Name";
  std::string getChildClassString(void) const { return childClassString_; };
};

// Define derived parent class
class DerivedParent : public parentOf<DerivedChild> {
  std::string parentClassString_ = "Parent Class";
 public:
  std::string name = "Parent Name";
  std::string getParentClassString(void) const { return parentClassString_; };
};

int main() {

  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  // ****** TEST PARENTADDRESS CLASS ****** //

  // Default Construction
  // parentAddress<DerivedParent> c1; //! Error

  // Test Param Constructor
  parentAddress<DerivedParent> parAddr(nullptr);

  // Copy Construction
  // parentAddress<DerivedParent> c2(parAddr); //! Error

  // Move Construction
  // parentAddress<DerivedParent> c3(std::move(parAddr)); //! Error

  // Test Param Constructor
  DerivedParent parentObject;
  parentObject.name = "Parent";
  parentAddress<DerivedParent> parAddr2(nullptr, &parentObject);

  // Test Dereference
  exitStatus |= testStrings((*parAddr2).name, parentObject.name);

  // Test Structure Dereference
  exitStatus |= testStrings(parAddr2->name,
                            parentObject.name);

  // Test Move Notification
  DerivedParent newParent;
  newParent.name = "New Parent";
  parAddr2.notifyMove(&parentObject, &newParent);
  exitStatus |= testStrings(parAddr2->name, newParent.name);

  // Test Copy Assignement Operator
  parentAddress<DerivedParent> parAddr3(nullptr);
  parAddr3 = parAddr2;
  exitStatus |= testStrings(parAddr3->name, newParent.name);

  // Test Move Assignement Operator
  parentAddress<DerivedParent> parAddr4(nullptr);
  parAddr4 = std::move(parAddr2);
  exitStatus |= testStrings(parAddr4->name, newParent.name);


  // ****** TEST CHILDADDRESS CLASS ****** //

  // Default Construction
  // childAddress<DerivedChild> c4; //! Error

  // Test Param Constructor
  childAddress<DerivedChild> chiAddr(nullptr);

  // Copy Construction
  // childAddress<DerivedChild> c5(chiAddr); //! Error

  // Move Construction
  // childAddress<DerivedChild> c6(std::move(chiAddr)); //! Error

  // Test Param Constructor
  DerivedChild childObject;
  childObject.name = "Child1";
  childAddress<DerivedChild> chiAddr2(nullptr, &childObject);

  // Test Dereference
  exitStatus |= testStrings(chiAddr2.dereference(0).name, childObject.name);

  // Test Child Addition
  DerivedChild Child2;
  Child2.name = "Child2";
  chiAddr2.notifyAddition(&Child2);
  exitStatus |= testStrings(chiAddr2.dereference(0).name + chiAddr2.dereference(1).name,
                            childObject.name + Child2.name);

  // Test Move Notification
  DerivedChild Child3;
  Child3.name = "Child3";
  chiAddr2.notifyMove(&childObject, &Child3);
  exitStatus |= testStrings(chiAddr2.dereference(0).name + chiAddr2.dereference(1).name,
                            Child3.name + Child2.name);

  // Test Copy Assignement Operator
  childAddress<DerivedChild> chiAddr3(nullptr);
  // chiAddr3 = chiAddr2; //! Error

  // Test Move Assignement Operator
  chiAddr3 = std::move(chiAddr2);
  exitStatus |= testStrings(chiAddr3.dereference(0).name + chiAddr3.dereference(1).name,
                            Child3.name + Child2.name);


  // ****** TEST DERIVED CLASSES OF PARENTOF AND CHILDOF ****** //

  {
    DerivedParent ParentObj;
    DerivedChild ChildObj;
    exitStatus |= testStrings(ParentObj.getParentClassString(),
                              "Parent Class");
    exitStatus |= testStrings(ChildObj.getChildClassString(),
                              "Child Class");

    // Add a relationship between objects
    ChildObj.setParent(&ParentObj);

    // Test Child to Parent Access
    exitStatus |= testStrings(ChildObj.getParentPtr()->name,
                              "Parent Name");
    // Test Parent to Child Access
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->name,
                              "Child Name");
  }

  // Test adding relationship from parent
  {
    DerivedParent ParentObj;
    DerivedChild ChildObj;

    // Add a relationship between objects
    ParentObj.addChild(&ChildObj);

    // Test Child to Parent Access
    exitStatus |= testStrings(ChildObj.getParentPtr()->name,
                              "Parent Name");
    // Test Parent to Child Access
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->name,
                              "Child Name");
  }


  // ****** CLEAN UP ****** //

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}
