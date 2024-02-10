#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include "mydatastore.h"
#include "util.h"

using namespace std;

// constructor 
MyDataStore::MyDataStore() {};

// destructor 
MyDataStore::~MyDataStore() {
    // Clean up products
    for (vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        delete *it;
    }   
    // Clean up users
    for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        delete it->second;
    }

}

// add user to the data store
void MyDataStore::addUser(User* user) {
    users[user->getName()] = user;
}
// add a product to data store 
void MyDataStore::addProduct(Product* product) {
    products.push_back(product);
    set<string> prodKey = product->keywords();
    // update the product index 
    for (set<string>::iterator it = prodKey.begin(); it != prodKey.end(); ++it) {
        prod_ind[*it].insert(product);
    }
}

// search for products with the given info 
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    vector<Product*> retval;

  // empty search 
    if(terms.size() == 0) {
      cout << "No keywords entered." << endl;
      return retval;
    }
    // single term search 
    if(terms.size() == 1) {
      for (set<Product*>::iterator it = prod_ind[convToLower(terms[0])].begin(); it != prod_ind[convToLower(terms[0])].end(); ++it) {
        retval.push_back(*it);
      }
      return retval;
    }

    set<Product*> results = prod_ind[convToLower(terms[0])];

    if (type == 0) {
      // and search
      for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it) {
        results = setIntersection(results, prod_ind[convToLower(*it)]);
      }
    }
    else if (type == 1) {
      // or search
      for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it) {
        results = setUnion(results, prod_ind[convToLower(*it)]);
      }
    }
    // result vector 
    for (set<Product*>::iterator it = results.begin(); it != results.end(); ++it) {
      retval.push_back (*it);
    }
    return retval;
}
// add a product to user's cart 
void MyDataStore::addToCart(string& username, Product* product) {
  User* user = findUser(username);
  // Check if the user exists. if so, error message
    if (user == nullptr) {
        cout << "Invalid request" << endl;
        return;
    }
    // add the product to cart 
    userCarts[user->getName()].push_back(product);
  }
// display the user's cart 
void MyDataStore::viewCart(string& username) {
    User* user = findUser(username);
  // Check if the user exists, error message
    if (user == nullptr) {
        cout << "Invalid username" << endl;
        return;
    }
  
    vector<Product*> s = userCarts[user->getName()];
        // Iterate through the cart
        for (size_t i = 0; i < s.size(); ++i) {
            Product* product = s[i];
      cout << "Item " << (i + 1) << "\n" << s[i]->displayString() << endl;
    }
}
    
// process the users cart then purchasing process
void MyDataStore::buyCart(string& username) {

  // Find the user's cart
     User* user = findUser(username);
  // Check if the user exists
    if (user == nullptr) {
        cout << "Invalid username" << endl;
        return;
    }

        // Iterate through the cart
        for (vector<Product*>::iterator i = userCarts[user->getName()].begin(); i != userCarts[user->getName()].end(); ++i) {
            Product* product = *i;
            // Check if the product is in stock and the user has enough credit
            if (product->getQty() > 0 && users[username]->getBalance() >= product->getPrice()) {
                // Reduce the product quantity and deduct the price from the user's credit
                product->subtractQty(1);
                users[username]->deductAmount(product->getPrice());
                // Remove the product from the cart
                userCarts[user->getName()].erase(i);
                --i;
            }
        }
}

// find a user by username
User* MyDataStore::findUser(std::string username) {
  if (users.find(username) != users.end()) {
    return users[username];
  }
  else{
    return nullptr; // user not found 
  }
}
// dump the data store cont
void MyDataStore::dump(ostream& ofile) {
    // Save products
    ofile << "<products>\n";
    for (vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        // Modify according to the structure of Product class
        (*it)->dump(ofile);
    }
    ofile << "</products>\n";
    ofile << "<users>\n";
    for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
      it->second->dump(ofile);
    }
    ofile << "</users>\n";
}