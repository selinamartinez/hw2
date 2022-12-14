#include <sstream>
#include <iomanip>
#include <cmath>
#include "book.h"
#include <set>
#include "util.h"

using namespace std;


Book::Book(std::string author, std::string isbn, std::string name_, double price_, int qty_, std::string category_) : Product( name_, price_, qty_, category_),
    author_(author),
    isbn_(isbn)
{
}


//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Book:: keywords() const {
    set<std::string>words;

    std::string keywords[4] = { author_, isbn_, name_, category_};

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
bool Book::isMatch(std::vector<std::string>&searchTerms)const
{
    return 0;
}
*/

//Returns a string to display the product info for hits of the search
std::string Book::displayString() const
{
    std::string book_info;
    //double price = ( round( price_ * 100.0 ) / 100.0 ) ;
    char s[20];
    sprintf(s,"%.2f",price_);
    book_info = name_ + '\n' + "Author: " + author_ + " " +
                          "ISBN: " + isbn_ + "\n" + s + "  " + std::to_string(qty_) + " left."; 

    return book_info;
}



void Book::dump(std::ostream& os) const
{
    //os << author_ << "\n" << isbn_ << "\n" << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ <<  endl;
}



