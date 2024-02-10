#include <iostream>
#include <iomanip>  
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string& category, const string& name, double price, int qty,
           const string& isbn, const string& author):
      Product(category, name, price, qty), isbn_(isbn), author_(author) {}

Book::~Book() 
{

}

set<string> Book::keywords() const {
  set<string> name = parseStringToWords(name_);
  set<string> author = parseStringToWords(author_);

  set<string> result;
  for (set<string>::iterator it = name.begin(); it != name.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = author.begin(); it != author.end(); ++it) {
    result.insert(*it);
  }
  result.insert(isbn_);
  return result;

}

string Book::displayString() const {
  std::ostringstream inf;
  inf << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_  << "\n" 
  << fixed << setprecision(2) << price_ << " " << qty_ << " left.\n";
  return inf.str();
}

void Book::dump(ostream &os) const {
  // Product::dump(os);
  // os << "\n" << isbn_ << "\n" << author_ << endl; 
  os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
