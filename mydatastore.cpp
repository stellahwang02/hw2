#include "mydatastore.h"
using namespace std;

MyDataStore::~MyDataStore() {
    // Clean up users
    for (set<string>::iterator it = users.begin(); set<string>::iterator it != users.end(); ++it) {
        delete it->second;
    }

    // Clean up products
    for (set<string>::iterator it = products.begin(); set<string>::iterator it != products.end(); ++it) {
        delete *it;
    }
}

void MyDataStore::addUser(User* user) {
    users[user->getUser()] = user;
}

void MyDataStore::addProduct(Product* product) {
    products.insert(product);
}

User* MyDataStore::getUser(const string& username) const {
    set<string>::iterator it = users.find(username);
    return (it != users.end()) ? it->second : nullptr;
}

std::set<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> result;
    if (type == 0) {
        // set intersection for AND search
        result = setIntersection(terms, products);
    } else {
        // set union for OR search
        result = setUnion(terms, products);
    }
    return result;
}

void MyDataStore::addToCart(const string& username, Product* product) {
    set<string>::iterator it = userCarts.find(username);
    if (it != userCarts.end()) {
        it->second.insert(product);
    } else {
        set<Product*> cart;
        cart.insert(product);
        userCarts[username] = cart;
    }
}

void MyDataStore::viewCart(const string& username) const {
    set<string>::iterator it = userCarts.find(username);
    if (it != userCarts.end()) {
        cout << "Shopping Cart for " << username << ":\n";
        for (product : it->second) {
          cout << product->displayString() << "\n";
        }
    } else {
        cout << "No shopping cart found for " << username << "\n";
    }
}

void MyDataStore::buyCart(const string& username) {
    set<string>::iterator it = userCarts.find(username);
    if (it != userCarts.end()) {
        for (product : it->second) {
            if (product->getQty() > 0 && it->second.count(product) > 0) {
                product->subtractQty(1);
                userCarts[username].erase(product);
            }
        }
    }
}

void MyDataStore::dump(ostream& ofile) {
    // Save users
    ofile << "<users>\n";
    for (auto it = users.begin(); it != users.end(); ++it) {
        ofile << it->second->getName() << " " << it->second->getPassword() << "\n";
    }
    ofile << "<users>\n";

    // Save products
    ofile << "<products>\n";
    for (auto it = products.begin(); it != products.end(); ++it) {
        ofile << (*it)->dump() << "\n";
    }
    ofile << "<products>";
}
