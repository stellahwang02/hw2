// clothing.h
#ifndef CLOTHING_H
#define CLOTHING_H
#include <string>
#include <vector>
#include "product.h"
using namespace std;

class Clothing : public Product {
  public:
    // Constructor 
    Clothing(const string& category, const string& name, double price, int qty,
            const string& size, const string& brand);
    ~Clothing();

    // Member functions
    set<string> keywords() const;
    string displayString() const;
    void dump(ostream &os) const;

  private:
      // Data members
      string size_;
      string brand_;

};

#endif // CLOTHING_H
