#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{
  
  rawWords = convToLower(rawWords);

  std::set<std::string> retval;
  std::string tok;
  std::istringstream ss(rawWords);

  while (ss >> tok) {
    size_t i = 0;
    while (tok.size() > 0 && i < tok.size()) {
      if (ispunct(tok[i])) {
        if (i > 1) {
          std::string temp = tok.substr(0,i);
          retval.insert(temp);
        }
        tok = tok.substr(i+1);
        i=0;
        continue;
      }
      i++;
    }
    if (i >= 2) {
      std::string temp = tok.substr(0,i);
      retval.insert(temp);
    }
  }
  return retval;
  /*
  std::set<std::string> setString;
  std::string substr;

  int cnt = 0;

  for (int i = 0; i <= rawWords.length(); i++) {
    if (std::ispunct(rawWords[i]) || i == rawWords.length() ) {
      if (cnt >= 2) {
        substr = rawWords.substr(i-cnt,cnt);
        std::cout<< substr<<std::endl;
        setString.insert(substr);
        cnt = 0;
      }
    }
    else {
      cnt++;
    }
    
  }
  return setString;
  */
}
/*
std::set<std::string> parse(std::string tok) {
  std::set<std::string> words;
  size_t start = 0, end = tok.size();
  while(start < end && ispunct(tok[start])) {
    start++;
  }
  while(end>start && ispunct(tok[end-1])) {
    end--;
  }
  if ((end-start) > 1) {
    tok = tok.substr(start, end-start);

    start=0;
    end = 0;
    for (size_t i=0; i<tok.size(); i++) {
      if (ispunct(tok[i]) && tok[i] != '-') {
        return words;
      }
    }
    convToLower(tok);

    while(tok.size() > 0 && end < tok.size()) {
      if (tok[end] == '-') {
        if (end >1) {
          std::string term = tok.substr(0, end);
          words.insert(term);
        }
        tok = tok.substr(end+1);
        end=0;
        continue;
      }
      end++;
    }
    std::string term = tok.substr(0, end);
    words.insert(term);
  }
  return words;
}
*/
/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
