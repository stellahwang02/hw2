#include <iostream>
#include "util.h"
#include <iomanip>  
#include <sstream>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const string& category, const string& name, double price, int qty,
                   const string& size, const string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand)
{

}

Clothing::~Clothing() 
{

}

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
  std::ostringstream inf;
  inf << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" 
      << fixed << setprecision(2) << price_ << " " << qty_ << " left.\n";
  return inf.str();
  }

void Clothing::dump(ostream &os) const {
  // Product::dump(os);
  // os << size_ << "\n";
  // os << brand_ << endl;
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}


