/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
// #include <iostream>
#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    std::vector<string> wordList;
    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
    while (getline(wordsFile, word)) {
      wordList.push_back(word);
    }
}
    // wordsFile.close();
    for(string & s : wordList) {
      string subword1 = s.substr(1, s.size());
      // std::cout << s << " " << subword1 << std::endl;
      string subword2 = s.substr(0,1) + subword1.substr(1, subword1.size());
      // std::cout << s << " " << subword2 << std::endl;
      bool check1 = d.homophones(subword1, subword2);
      bool check2 = d.homophones(s, subword2);
      // bool check3 = d.homophones(s, subword1);
      if(check1 && check2) {
        std::tuple<std::string, std::string, std::string> t {s, subword1, subword2};
        ret.push_back(t);
      }
    }
    return ret;
}
