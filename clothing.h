#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing: public Product {
    public:
        Clothing(std::string size, std::string brand, std::string name_, double price_, int qty_, std::string category_);


        /**
         * Returns the appropriate keywords that this product should be associated with
         */
        std::set<std::string> keywords() const override;

        /**
         * Allows for a more detailed search beyond simple keywords
         */
        bool isMatch(std::vector<std::string>& searchTerms);

        /**
         * Returns a string to display the product info for hits of the search
         */
        std::string displayString() const override;

        /**
         * Outputs the product info in the database format
         */
        void dump(std::ostream& os) const override;

    protected:
        std::string size_;
        std::string brand_;


};
#endif