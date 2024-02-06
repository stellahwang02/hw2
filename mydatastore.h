#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <set>
#include <map>

class MyDataStore : public DataStore {
public:
    virtual ~MyDataStore();

    // Add a user to the data store
    void addUser(User* user);

    // Add a product to the data store
    void addProduct(Product* product);

    // Get a user by their username
    User* getUser(const std::string& username) const;

    // Search for products based on search terms and type (AND or OR)
    std::set<Product*> search(std::vector<std::string>& terms, int type);

    // Add a product to a user's shopping cart
    void addToCart(const std::string& username, Product* product);

    // View the contents of a user's shopping cart
    void viewCart(const std::string& username) const;

    // Buy items in the user's shopping cart, updating product quantities
    void buyCart(const std::string& username);

    // Save users and products to a file
    void dump(std::ostream& ofile);

private:
    // Map for storing users by their usernames
    std::map<std::string, User*> users;

    // Set to store all products
    std::set<Product*> products;

    // Map for storing user shopping carts
    std::map<std::string, std::set<Product*>> userCarts;
};

#endif // MYDATASTORE_H
