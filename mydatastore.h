#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore: public DataStore {
    public:
        MyDataStore();

        virtual ~MyDataStore() { 
            //delete all the products
            std::set< Product* >::iterator it;
            for (it = productSet.begin(); it != productSet.end(); ++it)
            {
                delete *it;
             }
            //delete all the users
            for(std::map<User*, std::vector<Product*>>::iterator itr = userMap.begin(); itr != userMap.end(); ++itr) {
                User* user = itr->first;
                delete user;
            }
        }

        /**
         * Adds a product to the data store
         */
        void addProduct(Product* p) override;

        /**
         * Adds a user to the data store
         */
        void addUser(User* u) override;

        void addtoCart(std::string username, Product* p);

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile) override;
        void viewCart(std::string username);
        User* findUser(std::string username);
        void buyCart(std::string username);
        User* findUsername(std::string username);


    protected:
        //keys are users and values are a vector of Products which is basically the user's cart
        std::map<User*, std::vector<Product*> > userMap;
        std::set< Product* > productSet;



};
#endif