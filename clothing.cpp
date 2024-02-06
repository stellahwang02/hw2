#include "clothing.h"
#include <iostream>
#include "util.cpp"
#include "product.cpp"
#include <iostream>
using namespace std;

Clothing::Clothing(const string& category, const string& name, double price, int qty,
                   const string& size, const string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}

set<string> Clothing::keywords() const {
  set<string> name = parseStringToWords(name_);
  set<string> size = parseStringToWords(size_);
  set<string> brand = parseStringToWords(brand_);

  set<string> result;
  for (set<string>::iterator it = name.begin(); it != name.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = size.begin(); it != size.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = brand.begin(); it != brand.end(); ++it) {
    result.insert(*it);
  }
  // add to the same vector and return that vector 
  return result;
}

string Clothing::displayString() const {
    return name_ + "\nSize: " + size_ +
           "\n$" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Clothing::dump(ostream &os) const {
  Product::dump(os);
  cout << size_ << "\n";
  cout << brand_;
}


