#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Movie: public Product {
    public:
        Movie(std::string genre, std::string rating, std::string category_, std::string name_, double price_, int qty_);

        virtual ~Movie();

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
        std::string genre_;
        std::string rating_;


};
#endif