/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021, Jeremy Goossen jeremyg995@gmail.com
 */
 
#ifndef KINSHIP_H_
#define KINSHIP_H_

class Parent;

class Child {
  virtual void setParent(Parent* pNewParent) =0;
  virtual void replaceParent(Parent* pNewParent) =0;
  virtual void removeParent(void) =0;
};

class Parent {
  virtual void addChild(Child* pNewChild) =0;
  virtual void replaceChild(Child* pOldChild, Child* pNewChild) =0;
  virtual void removeChild(Child* pOldChild) =0;
  virtual bool isContainsChild(const Child* pChild) const =0;
};

#endif // KINSHIP_H_
