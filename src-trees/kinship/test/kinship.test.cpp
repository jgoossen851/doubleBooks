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
#include <sstream>
#include <string>
#include <vector>

int test_parentAddress_class();
int test_childAddress_class();
int test_derivedClass_Construction();
int test_derivedClass_addRelationship();
int test_movingCopyingParentChildClasses();

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

  exitStatus |= test_parentAddress_class();
  std::cout << "Done with parentAddress test." << std::endl;
  exitStatus |= test_childAddress_class();
  std::cout << "Done with childAddress test." << std::endl;
  exitStatus |= test_derivedClass_Construction();
  std::cout << "Done with derived class construction test." << std::endl;
  exitStatus |= test_derivedClass_addRelationship();
  std::cout << "Done with derived class relationship test." << std::endl;
  exitStatus |= test_movingCopyingParentChildClasses();
  std::cout << "Done with move copy test." << std::endl;

  // ****** CLEAN UP ****** //

  // Display Test Status
  std::cout << (exitStatus ? ansi::RED : ansi::GREEN)
            << std::string(15, '#')
            << " Tests " << (exitStatus ? "Failed!" : "Passed!") << " "
            << std::string(15, '#')
            << ansi::RESET << std::endl;

  return exitStatus;
}

/**
 * @brief Test construction and basic functions of the parentAddress Class.
 */
int test_parentAddress_class(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  // Default Construction
  // parentAddress<DerivedParent> c1; //! Error: Deleted

  // Test Param Constructor (single pointer)
  parentAddress<DerivedParent> parAddr(nullptr);
  // Test validity check
  exitStatus |= testStrings(std::to_string(parAddr.isValid()), "0");

  // Test Destructor of empty address
  {
    parentAddress<DerivedParent> destruc(nullptr);
  }

  // Copy Construction
  // parentAddress<DerivedParent> c2(parAddr); //! Error: Deleted

  // Move Construction
  // parentAddress<DerivedParent> c3(std::move(parAddr)); //! Error: Deleted

  // Test Param Constructor (double pointer)
  DerivedParent parentObject;
  parentObject.name = "Parent";
  parentAddress<DerivedParent> parAddr2(nullptr, &parentObject);
  exitStatus |= testStrings(std::to_string(parAddr2.isValid()), "1");

  // Test Dereference
  exitStatus |= testStrings((*parAddr2).name, parentObject.name);

  // Test Structure Dereference
  exitStatus |= testStrings(parAddr2->name,
                            parentObject.name);

  // Test Copy Assignement Operator
  parentAddress<DerivedParent> parAddr3(nullptr);
  parAddr3 = parAddr2;
  exitStatus |= testStrings(parAddr3->name, parentObject.name);
  exitStatus |= testStrings(std::to_string(parAddr2.isValid()), "1");
  exitStatus |= testStrings(std::to_string(parAddr3.isValid()), "1");

  // Test Move Assignement Operator
  parentAddress<DerivedParent> parAddr4(nullptr);
  parAddr4 = std::move(parAddr2);
  exitStatus |= testStrings(parAddr4->name, parentObject.name);
  exitStatus |= testStrings(std::to_string(parAddr2.isValid()), "0");
  exitStatus |= testStrings(std::to_string(parAddr3.isValid()), "1");
  exitStatus |= testStrings(std::to_string(parAddr4.isValid()), "1");

  // Test Set Parent Function
  DerivedParent Parent1;
  Parent1.name = "Parent 1";
  parentAddress<DerivedParent> parAddrSet(nullptr);
  parAddrSet.setParent(&Parent1);
  exitStatus |= testStrings(parAddrSet->name, Parent1.name);

  // Test Replace Parent function
  DerivedParent Parent2;
  Parent2.name = "Parent 2";
  parAddrSet.replaceParent(&Parent2);
  exitStatus |= testStrings(parAddrSet->name, Parent2.name);

  // Test Remove Parent function
  exitStatus |= testStrings(std::to_string(parAddrSet.isValid()), "1");
  parAddrSet.removeParent();
  exitStatus |= testStrings(std::to_string(parAddrSet.isValid()), "0");

  // Verify parent has been removed and test ostring operator
  std::ostringstream os;
  os << parAddrSet;
  exitStatus |= testStrings(os.str(), "0");

  return exitStatus;
}

int test_childAddress_class(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
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
  // chiAddr2.notifyAddition(&Child2);
  exitStatus |= testStrings(chiAddr2.dereference(0).name + chiAddr2.dereference(1).name,
                            childObject.name + Child2.name);

  // Test Move Notification
  DerivedChild Child3;
  Child3.name = "Child3";
  // chiAddr2.notifyMove(&childObject, &Child3);
  exitStatus |= testStrings(chiAddr2.dereference(0).name + chiAddr2.dereference(1).name,
                            Child3.name + Child2.name);

  // Test Copy Assignement Operator
  childAddress<DerivedChild> chiAddr3(nullptr);
  // chiAddr3 = chiAddr2; //! Error

  // Test Move Assignement Operator
  chiAddr3 = std::move(chiAddr2);
  exitStatus |= testStrings(chiAddr3.dereference(0).name + chiAddr3.dereference(1).name,
                            Child3.name + Child2.name);
  
  return exitStatus;
}

int test_derivedClass_Construction(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  DerivedParent ParentObj;
  DerivedChild ChildObj1;
  exitStatus |= testStrings(ParentObj.getParentClassString(),
                            "Parent Class");
  exitStatus |= testStrings(ChildObj1.getChildClassString(),
                            "Child Class");
  DerivedChild ChildObj2;
  ChildObj2.name = "Child2";

  // Add a relationship between objects
  ChildObj1.setParent(&ParentObj);
  ChildObj2.setParent(&ParentObj);

  // Test Child to Parent Access
  exitStatus |= testStrings(ChildObj1.getParentPtr()->name,
                            "Parent Name");
  // Test Parent to Child Access
  exitStatus |= testStrings(ParentObj.getChildPtr(0)->name + ParentObj.getChildPtr(1)->name,
                            "Child Name" "Child2");
  
  return exitStatus;
}

int test_derivedClass_addRelationship(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  DerivedParent ParentObj;
  DerivedChild ChildObj1;
  DerivedChild ChildObj2;
  ChildObj2.name = "Child2";

  // Add a relationship between objects
  ParentObj.addChild(&ChildObj1);
  ParentObj.addChild(&ChildObj2);

  // Test Child to Parent Access
  exitStatus |= testStrings(ChildObj1.getParentPtr()->name,
                            "Parent Name");
  // Test Parent to Child Access
  exitStatus |= testStrings(ParentObj.getChildPtr(0)->name + ParentObj.getChildPtr(1)->name,
                            "Child Name" "Child2");

  return exitStatus;
}

int test_movingCopyingParentChildClasses(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  DerivedParent ParentObj;
  ParentObj.name = "Original Parent";
  DerivedChild ChildObj;
  ChildObj.name = "Original Child";
  ChildObj.setParent(&ParentObj);
  {
    DerivedChild SecondChild;
    SecondChild.removeParent();
    // Test Copy Assignment of Child
    SecondChild = ChildObj;
    exitStatus |= testStrings(SecondChild.getParentPtr()->name,
                              "Original Parent");
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->name + ParentObj.getChildPtr(1)->name,
                              "Original Child" "Original Child");

    DerivedChild Child3;
    // Test Move Assignment of Child
    Child3 = std::move(ChildObj);
    SecondChild.name = "Second Child";
    exitStatus |= testStrings(Child3.getParentPtr()->name,
                              "Original Parent");
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->name + ParentObj.getChildPtr(1)->name,
                              "Original Child" "Second Child");
    // Original Child should be in a valid, but default, state.
    exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "2");

    // Test Move Constructor
    DerivedChild TempChild;
    TempChild.name = "TempChild";
    TempChild.setParent(&ParentObj);
    DerivedChild Child4(std::move(Child3));


    exitStatus |= testStrings(Child4.getParentPtr()->name,
                              "Original Parent");
    Child4.name = "This is Child4";
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->name + ParentObj.getChildPtr(1)->name,
                              "This is Child4" "Second Child");
    // Original Child should be in a valid, but default, state.
    exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "2");
  }

  {
    DerivedParent NewParent;
    NewParent.name = "New Parent";
    DerivedChild NewChild;
    NewChild.name = "New Child 1";
    NewChild.setParent(&NewParent);

    // Test Move Assignment of Parent
    ParentObj = std::move(NewParent);

    exitStatus |= testStrings(ParentObj.name,
                            "New Parent");
    exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "1");
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->name,
                              "New Child 1");
    exitStatus |= testStrings(ParentObj.getChildPtr(0)->getParentPtr()->name,
                              "New Parent");
  }
  exitStatus |= testStrings(ParentObj.name,
                            "New Parent");
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "0");
  // exitStatus |= testStrings(ParentObj.getChildPtr(0)->name,
  //                           "New Child 1"); //! Error

  // Test Parent destructor
  DerivedChild PersistentChild;
  PersistentChild.name = "Persistent";
  {
    DerivedParent TempParent;
    TempParent.name = "Temporary";
    TempParent.addChild(&PersistentChild);

    exitStatus |= testStrings(PersistentChild.name,
                              "Persistent");
    exitStatus |= testStrings(PersistentChild.getParentPtr()->name,
                              "Temporary");
  }
  exitStatus |= testStrings(PersistentChild.name,
                            "Persistent");
  // exitStatus |= testStrings(PersistentChild.getParentPtr()->name,
  //                           "Temporary"); //! Error

  return exitStatus;
}

