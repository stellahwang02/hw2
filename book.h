#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <vector>
#include "product.h"

using namespace std;

class Book : public Product {
  public:
      // Constructor
    Book(const string& category, const string& name, double price, int qty,
        const string& isbn, const string& author);
      // destructor 
    ~Book();

      // Member functions
    set<string> keywords() const;
    string displayString() const;
    void dump(ostream &os) const;

  private:
      // Data members
    string isbn_;
    string author_;
};

#endif // BOOK_H
