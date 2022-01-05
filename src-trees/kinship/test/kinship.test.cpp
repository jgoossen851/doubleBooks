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

#define VERBOSE_DEBUG 0

int testDerivedClassConstruction_childOf_parentOf();
int testClass_parentAddress();
int testClass_childAddress();
int testClass_parentOf();
int testClass_childOf();
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
  #if VERBOSE_DEBUG
    std::cout << "Testing: " << testString << "   Ans: " << ansString << std::endl;
  #endif
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

  exitStatus |= testDerivedClassConstruction_childOf_parentOf();
  std::cout << ansi::YELLOW << "Done with derived class construction test." << ansi::RESET << std::endl;
  exitStatus |= testClass_parentAddress();
  std::cout << ansi::YELLOW << "Done with parentAddress test." << ansi::RESET << std::endl;
  exitStatus |= testClass_childAddress();
  std::cout << ansi::YELLOW << "Done with childAddress test." << ansi::RESET << std::endl;
  exitStatus |= testClass_parentOf();
  std::cout << ansi::YELLOW << "Done with parentOf test." << ansi::RESET << std::endl;
  exitStatus |= testClass_childOf();
  std::cout << ansi::YELLOW << "Done with childOf test." << ansi::RESET << std::endl;
  exitStatus |= test_movingCopyingParentChildClasses();
  std::cout << ansi::YELLOW << "Done with move copy test." << ansi::RESET << std::endl;

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
 * @brief Test Construction of derived classes
 */
int testDerivedClassConstruction_childOf_parentOf(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  // Construct original parent and child objects
  DerivedParent ParentObj;
  DerivedChild ChildObj1;
  exitStatus |= testStrings(ParentObj.name,
                            "Parent Name");
  exitStatus |= testStrings(ChildObj1.name,
                            "Child Name");
  exitStatus |= testStrings(ParentObj.getParentClassString(),
                            "Parent Class");
  exitStatus |= testStrings(ChildObj1.getChildClassString(),
                            "Child Class");

  return exitStatus;
}

/**
 * @brief Test construction and basic functions of the parentAddress Class.
 */
int testClass_parentAddress(){
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

/**
 * @brief Test construction and basic functions of the childAddress Class.
 */
int testClass_childAddress(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;
  
  // Default Construction
  // childAddress<DerivedChild> c4; //! Error: Deleted

  // Test Param Constructor (single pointer)
  childAddress<DerivedChild> chiAddr(nullptr);
  // Test vector size
  exitStatus |= testStrings(std::to_string(chiAddr.vectorSize()), "0");

  // Test ostream operator on empty vector
  std::ostringstream os;
  os << chiAddr;
  exitStatus |= testStrings(os.str(), "[]");

  // Test Destructor of empty address
  {
    childAddress<DerivedChild> destruc(nullptr);
  }

  // Copy Construction
  // childAddress<DerivedChild> c5(chiAddr); //! Error: Deleted

  // Move Construction
  // childAddress<DerivedChild> c6(std::move(chiAddr)); //! Error: Deleted

  // Test Param Constructor (double pointer)
  DerivedChild childObject;
  childObject.name = "Child1";
  childAddress<DerivedChild> chiAddr2(nullptr, &childObject);
  exitStatus |= testStrings(std::to_string(chiAddr2.vectorSize()), "1");
  std::ostringstream os2;
  os2 << chiAddr2;
  std::ostringstream expectedResult;
  expectedResult << "[" << &childObject << "]";
  exitStatus |= testStrings(os2.str(),
                            expectedResult.str());

  // Test Dereference
  exitStatus |= testStrings(chiAddr2.dereference(0).name, childObject.name);

  // Test Child Addition
  DerivedChild Child2;
  Child2.name = "Child2";
  chiAddr2.addChild(&Child2, nullptr);
  exitStatus |= testStrings(std::to_string(chiAddr2.vectorSize()), "2");
  exitStatus |= testStrings(chiAddr2.dereference(0).name + chiAddr2.dereference(1).name,
                            childObject.name + Child2.name);
  std::ostringstream os3;
  os3 << chiAddr2;
  std::ostringstream expectedResult3;
  expectedResult3 << "[" << &childObject << ", " << &Child2 << "]";
  exitStatus |= testStrings(os3.str(),
                            expectedResult3.str());

  // Test Copy Assignement Operator
  childAddress<DerivedChild> chiAddr3(nullptr);
  // chiAddr3 = chiAddr2; //! Error: Deleted

  // Test Move Assignement Operator
  chiAddr3 = std::move(chiAddr2);
  exitStatus |= testStrings(std::to_string(chiAddr2.vectorSize()), "0");
  exitStatus |= testStrings(std::to_string(chiAddr3.vectorSize()), "2");
  exitStatus |= testStrings(chiAddr3.dereference(0).name + chiAddr3.dereference(1).name,
                            childObject.name + Child2.name);

  // Test Replace Child
  DerivedChild Child3;
  Child3.name = "Child3";
  chiAddr3.replaceChild(&childObject, &Child3, nullptr);
  exitStatus |= testStrings(std::to_string(chiAddr3.vectorSize()), "2");
  exitStatus |= testStrings(chiAddr3.dereference(0).name + chiAddr3.dereference(1).name,
                            Child3.name + Child2.name);
  // From End
  DerivedChild Child4;
  Child4.name = "Child4";
  chiAddr3.replaceChild(&Child2, &Child4, nullptr);
  exitStatus |= testStrings(std::to_string(chiAddr3.vectorSize()), "2");
  exitStatus |= testStrings(chiAddr3.dereference(0).name + chiAddr3.dereference(1).name,
                            Child3.name + Child4.name);

  // Test function to search for children
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&childObject)), "0");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&Child2)), "0");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&Child3)), "1");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&Child4)), "1");

  // Test Remove Child function
  chiAddr3.removeChild(&Child3);
  exitStatus |= testStrings(std::to_string(chiAddr3.vectorSize()), "1");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&childObject)), "0");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&Child2)), "0");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&Child3)), "0");
  exitStatus |= testStrings(std::to_string(chiAddr3.isContainsChild(&Child4)), "1");

  return exitStatus;
}

int testClass_parentOf(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  // Construct original parent and child objects
  DerivedParent ParentObj;
  DerivedChild ChildObj1;
  DerivedChild ChildObj2;
  ChildObj2.name = "Child2";

  // Add a relationship between objects
  ParentObj.addChild(&ChildObj1);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "1");
  ParentObj.addChild(&ChildObj2);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "2");

  // Test searching for children
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj2)), "1");
  DerivedChild ChildObj3;
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj3)), "0");

  // Test dereferencing child object
  exitStatus |= testStrings(ParentObj.getChildPtr(0)->name + ParentObj.getChildPtr(1)->name,
                            "Child Name" "Child2");

  // Test Move Assignment
  DerivedParent Parent2;
  Parent2 = std::move(ParentObj);
  exitStatus |= testStrings(std::to_string(Parent2.getNumChildren()), "2");
  exitStatus |= testStrings(Parent2.getChildPtr(0)->name + Parent2.getChildPtr(1)->name,
                            "Child Name" "Child2");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "0");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj2)), "0");
  exitStatus |= testStrings(std::to_string(Parent2.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(Parent2.isContainsChild(&ChildObj2)), "1");
  
  // Test Move Constructor
  DerivedParent Parent3(std::move(Parent2));
  exitStatus |= testStrings(std::to_string(Parent3.getNumChildren()), "2");
  exitStatus |= testStrings(Parent3.getChildPtr(0)->name + Parent3.getChildPtr(1)->name,
                            "Child Name" "Child2");
  exitStatus |= testStrings(std::to_string(Parent2.isContainsChild(&ChildObj1)), "0");
  exitStatus |= testStrings(std::to_string(Parent2.isContainsChild(&ChildObj2)), "0");
  exitStatus |= testStrings(std::to_string(Parent3.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(Parent3.isContainsChild(&ChildObj2)), "1");
  
  // Test Replacing Child
  ChildObj3.name = "Child3";
  Parent3.replaceChild(&ChildObj2, &ChildObj3);
  exitStatus |= testStrings(std::to_string(Parent3.getNumChildren()), "2");
  exitStatus |= testStrings(Parent3.getChildPtr(0)->name + Parent3.getChildPtr(1)->name,
                            "Child Name" "Child3");
  exitStatus |= testStrings(std::to_string(Parent3.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(Parent3.isContainsChild(&ChildObj2)), "0");
  exitStatus |= testStrings(std::to_string(Parent3.isContainsChild(&ChildObj3)), "1");
  
  // Test removing child
  Parent3.removeChild(&ChildObj3);
  exitStatus |= testStrings(std::to_string(Parent3.getNumChildren()), "1");
  exitStatus |= testStrings(std::to_string(Parent3.isContainsChild(&ChildObj1)), "1");
  Parent3.removeChild(&ChildObj1);
  exitStatus |= testStrings(std::to_string(Parent3.getNumChildren()), "0");

  return exitStatus;
}

int testClass_childOf(){
  // Initialize exit status
  int exitStatus = EXIT_SUCCESS;

  // Construct original parent and child objects
  DerivedParent ParentObj;
  DerivedChild ChildObj1;
  DerivedChild ChildObj2;
  ChildObj2.name = "Child2";

  // Add a relationship between objects
  ChildObj1.setParent(&ParentObj);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "1");
  ChildObj2.setParent(&ParentObj);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "2");

  // Test dereferencing parent object
  exitStatus |= testStrings(ChildObj1.getParentPtr()->name,
                            "Parent Name");
  exitStatus |= testStrings(ChildObj2.getParentPtr()->name,
                            "Parent Name");

  // Test Copy Assignment Operator
  DerivedChild Child3;
  Child3 = ChildObj1;
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "3");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj2)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child3)), "1");
  exitStatus |= testStrings(Child3.getParentPtr()->name,
                            "Parent Name");

  // Test Move Assignment Operator
  DerivedChild Child4;
  Child4 = std::move(ChildObj2);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "3");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj2)), "0");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child3)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child4)), "1");
  exitStatus |= testStrings(Child4.getParentPtr()->name,
                            "Parent Name");

  // Test Move Constructor
  DerivedChild Child5 = std::move(Child3);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "3");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj2)), "0");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child3)), "0");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child4)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child5)), "1");
  exitStatus |= testStrings(Child5.getParentPtr()->name, "Parent Name");

  // Test Replacing Parent
  DerivedParent Parent2;
  Parent2.name = "Parent2";  
  Child4.replaceParent(&Parent2);
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "2");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child5)), "1");
  exitStatus |= testStrings(std::to_string(Parent2.getNumChildren()), "1");
  exitStatus |= testStrings(std::to_string(Parent2.isContainsChild(&Child4)), "1");
  exitStatus |= testStrings(Child4.getParentPtr()->name, "Parent2");
  
  // Test Removing Parent
  Child5.removeParent();
  exitStatus |= testStrings(std::to_string(ParentObj.getNumChildren()), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&ChildObj1)), "1");
  exitStatus |= testStrings(std::to_string(ParentObj.isContainsChild(&Child5)), "0");

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

