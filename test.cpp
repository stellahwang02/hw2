#include "mydatastore.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "mydatastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.cpp"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    // std::string username; // added
    
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }

            else if ( cmd == "ADD") {
              string username;
              if (ss >> username) {
                if (ds.findUser(username) == nullptr) {
                  cout << "Error" << endl;
                }
                // else {
                  // ds.addToCart(username);
                //}
              }
            }
          
            /*
              string username;
              int hitNum;
              if (ss >> username >> hitNum) {
               if (ds.findUser(username) == nullptr) {
                cout << "error" << endl;
               }
               else if (hitNum < 1 || hitNum > hits.size()) {
                cout << "Error: Invalid hit number." << endl;
               }
               else {
                Product* selectedProduct = hits[hitNum-1];
                ds.addToCart(username, selectedProduct);
               }
              }
            }
            */

            else if (cmd == "BUY CART") {
              string username;
              if (ss >> username) {
                if (ds.findUser(username) == nullptr) {
                  cout << "Error" << endl;
                }
                else {
                  ds.buyCart(username);
                }
              }
            }

            else if (cmd == "VIEW CART") {
              string username;
              if (ss >> username) {
                if (ds.findUser(username) == nullptr) {
                  cout << "Error" << endl;
                }
                else {
                  ds.viewCart(username);
                }
            }
         }
         else {
          cout << "Unknown command" << endl;
         }

       return 0;
  }
}
}
  

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

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

set<Product*> MyDataStore::search(vector<string>& terms, int type) {
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
    // Save products
    cout << "calling dump";
    ofile << "<products>\n";
    for (vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        // Modify according to the structure of Product class
        (*it)->dump(ofile);
       // ofile << "\n";
    }
    cout << "hey";
    ofile << "</products>";

    // Save users
    ofile << "\n<users>\n";
    for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
      it->second.dump();
    }
    ofile << "</users>\n";
}
