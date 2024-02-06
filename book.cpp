#include "book.h"
#include <iostream>
#include "util.cpp"
#include "product.cpp"
using namespace std;

Book::Book(const string& category, const string& name, double price, int qty,
           const string& isbn, const string& author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

set<string> Book::keywords() const {
  set<string> name = parseStringToWords(name_);
  set<string> author = parseStringToWords(author_);
  set<string> isbn = parseStringToWords(isbn_);

  set<string> result;
  for (set<string>::iterator it = name.begin(); it != name.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = author.begin(); it != author.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = isbn.begin(); it != isbn.end(); ++it) {
    result.insert(*it);
  }

  // add to the same vector and return that vector 
  return result;
}

string Book::displayString() const {
    return name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ +
           "\n$" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Book::dump(ostream &os) const {
  Product::dump(os);
  cout << isbn_ << "\n";
  cout << author_;
}
