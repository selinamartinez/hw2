#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */

//if s1 is empty, copy s2 to s1
//else add from s2 to s1 only if s1 appears in s2
//delete from s2 if s1 doesn't have s2;
//return s1
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T>::iterator it;
    //iterate through the set you're keeping and delete items that aren't present in the other set
    for(it = s1.begin(); it != s1.end(); ++it) {
        T theProduct = *it;
        bool is_in = s2.find(theProduct) != s2.end();
        //if the element WAS NOT found, delete it from s1
        if (!is_in) {
            s1.erase(theProduct);
        }
    }

    return s1;

}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T>::iterator it;
    //insert everything from s2 to s1 and return s1;
    for(it = s2.begin(); it != s2.end(); ++it) {
        T theProduct = *it;
        s1.insert(theProduct);
    }
    
    return s1;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
