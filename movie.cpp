#include <sstream>
#include <iomanip>
#include "movie.h"
#include <set>
#include "util.h"

using namespace std;


Movie::Movie(std::string genre, std::string rating, std::string name_, double price_, int qty_, std::string category_) : Product( name_, price_, qty_, category_),
    genre_(genre),
    rating_(rating)
{

}


Movie::~Movie()
{

}

//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Movie::keywords() const {
    set<std::string>words;
    std::string keywords[4] = { genre_, rating_,  name_ , category_};

    for(int i = 0; i < 4; i++) {
        set<std::string> more_keywords;
        std::string the_string = convToLower(keywords[i]);
        more_keywords = parseStringToWords(the_string);


        //adding all the words from parseStringToWords to the overall keyword set
        words.insert(more_keywords.begin(), more_keywords.end());
    }


    return words;

}

/*
bool Movie::isMatch(std::vector<std::string>&searchTerms)const
{
    return 0;
}
*/



//Returns a string to display the product info for hits of the search
std::string Movie::displayString() const
{
    std::string movie_info;
    movie_info = name_ + "\n" + "Genre: " + genre_ + " " +
                          "Rating: " + (rating_) + "\n" + std::to_string(price_) + " " + std::to_string(qty_)  + " left.";
    return movie_info;
}



void Movie::dump(std::ostream& os) const
{
    os << genre_ << "\n" << rating_ << "\n" << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}




