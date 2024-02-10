#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"

class MyDataStore : public DataStore {
public:
    
    MyDataStore();
    ~MyDataStore();

    // Add a user to the data store
    void addUser(User* user);

    // Add a product to the data store
    void addProduct(Product* product);

    // Get a user by their username
    // User* getUser(const std::string& username) const;

    // Search for products based on search terms and type (AND or OR)
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    // Add a product to a user's shopping cart
    void addToCart(std::string& username, Product* product);

    // View the contents of a user's shopping cart
    void viewCart(std::string& username);

    // Buy items in the user's shopping cart, updating product quantities
    void buyCart(std::string& username);

    // Save users and products to a file
    void dump(std::ostream& ofile);

  // if the user exists
    User* findUser(std::string username);

// private:
    // Map for storing users by their usernames
    std::map<std::string, User*> users;

    // Set to store all products
    std::vector<Product*> products;

    // Map for storing user shopping carts
    std::map<std::string, std::vector<Product*>> userCarts;

    // index of the product in the last search result 
    std::map<std::string, std::set<Product*>> prod_ind;
    // user's last search result
    // std::vector<Product*> lastSearchResults;
};

#endif // MYDATASTORE_H
