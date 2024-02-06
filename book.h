#ifndef BOOK_H
#define BOOK_H
using namespace std;

#include "product.h"
#include <string>
#include <vector>

class Book : public Product {
  public:
      // Constructor
    Book(const string& category, const string& name, double price, int qty,
        const string& isbn, const string& author);

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
