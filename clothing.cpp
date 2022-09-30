#include <sstream>
#include <iomanip>
#include "clothing.h"
#include <set>
#include "util.h"

using namespace std;


Clothing::Clothing(std::string size, std::string brand, std::string category_, std::string name_, double price_, int qty_ ) : Product(category_, name_, price_, qty_),
    size_(size),
    brand_(brand)
{

}


Clothing::~Clothing()
{

}

//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Clothing:: keywords() const {
    set<std::string>words;
    std::string keywords[] = { size_, brand_, category_, name_ };

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
bool Clothing::isMatch(std::vector<std::string>&searchTerms)const
{
    return 0;
}
*/
//Returns a string to display the product info for hits of the search



std::string Clothing::displayString() const
{
    std::string clothing_info;
    clothing_info = name_ + "\n" + "Size: " + size_ + " " +
                          "Brand: " + (brand_) + "\n" + std::to_string(price_) + " " + std::to_string(qty_)  + " left.";
    return clothing_info;
}



void Clothing::dump(std::ostream& os) const
{
    os << size_ << "\n" << brand_ << "\n" << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}


