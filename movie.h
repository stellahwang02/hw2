#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>
#include "product.h"
using namespace std;

class Movie : public Product {
  public:
  // constructor 
    Movie(const string& category, const string& name, double price, int qty, 
          const string& genre, const string& rating);
    ~Movie();
  // member functions
    set<string> keywords() const;
    string displayString() const;
    void dump(ostream &os) const;

  private:
  // priv data members 
    string genre_;
    string rating_;
};

#endif
