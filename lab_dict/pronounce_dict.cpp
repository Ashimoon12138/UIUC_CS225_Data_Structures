/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/**
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if (pronun_dict_file.is_open()) {
        while (getline(pronun_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator<string> line_begin(line_ss);
            istream_iterator<string> line_end;
            if (line[0] != '#' && *line_begin != ";;;") {
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                istream_iterator<string> temp_itr = line_begin;
                dict[*temp_itr] = vector<string>(++line_begin, line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/**
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map<string, vector<string>>& pronun_dict)
    : dict(pronun_dict)
{
    /* Nothing to see here. */
}

/**
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
    //@ word1 word2 const can not transform
    string wordCopy1 = word1;
    string wordCopy2 = word2;
    std::transform(wordCopy1.begin(), wordCopy1.end(), wordCopy1.begin(), ::toupper);
    std::transform(wordCopy2.begin(), wordCopy2.end(), wordCopy2.begin(), ::toupper);
    //@ auto!!!!
    auto it1 = dict.find(wordCopy1);
    //@const_iterator not iterator
    std::map<std::string, std::vector<std::string>>::const_iterator it2 = dict.find(wordCopy2);
    if (it1 == dict.end() || it2 == dict.end()) {
      return false;
    }

    return it1->second == it2->second;
    // std::vector<std::string> v1 = it1->second;
    // std::vector<std::string> v2 = it2->second;
    // bool same = false;
    // for (std::string & s1 : v1) {
    //   for (std::string & s2 :v2) {
    //     if (s1 == s2) {
    //       same = true;
    //     }
    //   }
    // }
    // if(same == true) {
    //   return true;
    // }
    // else {
    //   return false;
    // }
}
