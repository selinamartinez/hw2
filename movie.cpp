#include <sstream>
#include <iomanip>
#include "movie.h"
#include <set>

using namespace std;


Movie::Movie(std::string genre, std::string rating, std::string category_, std::string name_, double price_, int qty_ ) : Product(category_, name_, price_, qty_),
    genre_(genre),
    rating_(rating)
{

}


Movie::~Movie()
{

}

//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Movie:: keywords() const {
    set<std::string>words;
    std::string keywords[] = { genre_, rating_, category_, name_ };

    for(int i = 0; i < 7; i++) {
        words.insert(keywords[i]);
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
    movie_info = genre_ + " " + rating_ + " " + category_ + " " + name_;
    return movie_info;
}



void Movie::dump(std::ostream& os) const
{
    os << genre_ << "\n" << rating_ << "\n" << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}




