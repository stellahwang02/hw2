#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{ 
  std::set<T> intersectionSet;
  typename std::set<T>::const_iterator it1 = s1.begin();
  typename std::set<T>::const_iterator it2 = s2.begin();
    
  // Iterate through set1
  for (it1 = s1.begin(); it1 != s1.end(); ++it1) {
    // If the element exists in set2, add it to intersectionSet
      if (s2.find(*it1) != s2.end()) {
          intersectionSet.insert(*it1);
      }
  }
  return intersectionSet;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{ // iterate thru s1, add aback to vector, add everything tthat's in s2 but not s1
  // for loop and if statments

  std::set<T> unionSet;
  typename std::set<T>::const_iterator it1 = s1.begin();
  typename std::set<T>::const_iterator it2 = s2.begin();
    
  // Insert all elements of set1 into unionSet
  unionSet.insert(s1.begin(), s1.end());
    
  // Insert elements of set2 into unionSet if they don't already exist
  for (it1 = s2.begin(); it1 != s2.end(); ++it1) {
      if (unionSet.find(*it1) == unionSet.end()) {
          unionSet.insert(*it1);
      }
    }
  return unionSet;
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
