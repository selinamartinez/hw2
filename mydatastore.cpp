#include <sstream>
#include <iomanip>
#include <fstream>
#include <set>
#include "util.h"
#include "user.h"
#include "mydatastore.h"
#include "product.h"
#include <map>
using namespace std;

MyDataStore::MyDataStore()
{

}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
 std::vector<Product*> MyDataStore:: search(std::vector<std::string>& terms, int type) {
    //take the term and look through each product seeing if theres a match..if there's a match, add the product to the new set that will be passed into setIntersection

    //use map instead of multiple sets..key will be the term and values will be a set of product pointers that have that term in their keywords
    std::map< std::string, std::set<Product*> > productsInTerms;
    //for each term in the search vector
    int term_count = terms.size();
    
    for(int i =  0; i < term_count; i++) {
         //iterator for iterating through the products
        //look through every product 
        std::set< Product* >::iterator it;
        for (it = productSet.begin(); it != productSet.end(); ++it)
        {

            Product* theProduct = *it;
            //get all the keywords in that product
            std::set<std::string> allTerms = theProduct->keywords();
            //find the term we need:
            const bool is_in = allTerms.find(terms[i]) != allTerms.end();
            if ( is_in ) {
                //element was present so add the corresponding product to the map
                productsInTerms[terms[i]].insert(theProduct);
            }
        }

    }
    
    //At this point we have a map with each term you searched for as a key and each key has a value set of product pointers (meaning these products have that term in their keywords)
    //Now we need to combine these sets based on Intersection of Union rules

     //the final set that will contain all the products we will be returning
    std::set<Product*> finalProducts;

    //if AND, the product must be present in the set of EVERY value of the map
    if ( type == 0 ) {
        std::map<std::string, std::set<Product*> >::iterator itr;
        //iterate through the map and start adding elements to the final set
        for(itr = productsInTerms.begin(); itr != productsInTerms.end(); ++itr) {
            std::set<Product*> s = itr->second;
            //if the finalProducts set is empty, just copy everything from the first set of the map to finalProducts
            //then move onto integrating the next value set in the map
            if (finalProducts.size() == 0) {
                finalProducts = s;
            }
            else {
                finalProducts = setIntersection(finalProducts, s);
            }
        }

    }
    //OR search, we are printing out all the products that appear in EVERY value vector
    //need to convert each vector into  
    //accounts for type 1 which is union, or no indicated type...so union will be the default type
    else {
        std::map<std::string, std::set<Product*> >::iterator it;
        for(it = productsInTerms.begin(); it != productsInTerms.end(); ++it) {
            set<Product*> s = it->second;
            finalProducts = setUnion(finalProducts, s);
        }

    }
    //convert set to vector to be returned
    std::vector<Product*> productVector(finalProducts.begin(), finalProducts.end());

    return productVector;

}


void MyDataStore::addUser(User* u) {
    //adding the user to the map without adding anything to their cart
    userMap[u];
}

void MyDataStore:: addtoCart(std::string username, Product* p) {
    User* theUser = findUsername(username);
    userMap[theUser].push_back(p);
}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p)
{
    //get all the keywords and add them all to the product 
    p->keywords();
    //add product pointer to the set of product pointers
    productSet.insert(p);
}

/**
* Reproduce the database file from the current Products and User values
should also call the deconstructors i think
*/
void MyDataStore::dump(std::ostream& ofile)
{
    //iterate through products
    ofile << "<products>" << endl;
    for(std::set<Product*>::iterator it = productSet.begin(); it != productSet.end(); ++it) {
        Product* prod = *it;
        prod->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(std::map<User*, vector<Product*> >::iterator itr = userMap.begin(); itr != userMap.end(); itr++) {
        User* user = itr->first;
        user->dump(ofile);
    }
    ofile << "</users>" << endl;



    
}

User* MyDataStore::findUsername(std::string username) 
{
    //check to see if the username exists
    for(std::map<User*, std::vector<Product*>>::iterator it = userMap.begin(); it != userMap.end(); ++it) {
        User* user = it->first;
        std::string name_of_user = user->getName();
        if (name_of_user == username) {
            return user;
        }

    }
    return NULL;
}

void MyDataStore:: viewCart(std::string username)
{
    //username was found in the map
    User* the_user = findUsername(username);
    if (the_user != NULL) {     
        std::vector<Product*> cart = userMap[the_user];
        std::map<User*, std::vector<Product*>>::iterator it;
        it = userMap.find(the_user);
        if (it != userMap.end())
        {
            std::vector<Product* >prods = it->second;
            int prodsSize = prods.size();
            for(int i=0; i < prodsSize; i++) {
                Product* prod = prods[i];
                cout << "Item: " << i + 1 << " " << prod->displayString() << std::endl;
            }
            
        }
    }
    else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore:: buyCart(std::string username) 
{
    User* the_user = findUsername(username);
    std::map<User*, std::vector<Product*>>::iterator it;
    it = userMap.find(the_user);
    if (it != userMap.end())
    {
        std::vector<Product* >prods = it->second;
        int prodsSize = prods.size();
        std::cout << prodsSize << std::endl;
        User* user = it->first;
        int i = 0;
       for(std::vector<Product*>::iterator itr = prods.begin(); itr != prods.end(); ++itr) {
            Product* product = *itr;
            double price = product->getPrice();
            double credit = user->getBalance();
            double newBalance = credit - price;
            std::cout << newBalance << std::endl;
            //they have enough money to buy the item so delete it from the cart
            if (newBalance >= 0) {
                user->deductAmount(price);
                product->subtractQty(1);
                prods.erase(prods.begin() + i);
            }
            i++;
        }
     }
        
        else {
            cout << "Username not found." << endl;
        }        

}
