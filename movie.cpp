#include "movie.h"
#include <iostream>
#include "util.cpp"
#include "product.cpp"

using namespace std;

// constructor definition
Movie::Movie(const string& category, const string& name, double price, int qty,
             const string& genre, const string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

// return keywords
set<string> Movie::keywords() const {
  set<string> name = parseStringToWords(name_);
  set<string> genre = parseStringToWords(genre_);
  set<string> rating = parseStringToWords(rating_);

  set<string> result;
  for (set<string>::iterator it = name.begin(); it != name.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = genre.begin(); it != genre.end(); ++it) {
    result.insert(*it);
  }
  for (set<string>::iterator it = rating.begin(); it != rating.end(); ++it) {
    result.insert(*it);
  }
  // add to the same vector and return that vector 
  return result;
}

// return display string
string Movie::displayString() const {
  string displayStr = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ +
           "\n$" + to_string(price_) + " " + to_string(qty_) + " left.";
  return displayStr;
}

// output database format 
void Movie::dump(ostream &os) const {
  Product::dump(os);
  cout << genre_ << "\n";
  cout <<  rating_;
}