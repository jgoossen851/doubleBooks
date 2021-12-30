

// childAddress.h

#include <ostream>

// Forward declare template friend functions
template<typename T> class childAddress; // pre-declare the template class itself
template<typename T> std::ostream& operator<< (std::ostream& o, const childAddress<T>& x);


// ...

friend std::ostream& operator<< <> (std::ostream& o, const childAddress<T>& x);


// childAddress.tcc

template<typename T>
std::ostream& operator<< (std::ostream& o, const childAddress<T>& x) {
  o << "[";
  for (auto itr = x.vpChildren_.begin(); itr < x.vpChildren_.end(); itr++) {
    if (itr > x.vpChildren_.begin()) { o << ", "; }
    o << *itr;
  }
  return o << "]";
}



// ParentOf.h

  void addChild(Child* pNewChild) override {
    std::cout << "Child Address vector is " << mChildAddr_ << std::endl;
    mChildAddr_.addChild(static_cast<T*>(pNewChild), this);
    std::cout << "Adding child " << pNewChild << std::endl;
    std::cout << "Child Address vector is now " << mChildAddr_ << std::endl;
  }

