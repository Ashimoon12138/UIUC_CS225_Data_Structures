/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        //find all elements of words in file_word_maps[i]
        for (size_t j = 0; j < words.size(); j++) {
          string findWord = words[j];
          map<string, unsigned int>::iterator lookup = file_word_maps[i].find(findWord);
        if(lookup != file_word_maps[i].end()) {
          file_word_maps[i][findWord] ++;
        }else {
          file_word_maps[i][findWord] = 1;
        }
      }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
      //@ hint : there may be several same elements in a same file
      //@ but there is no douplicate keys in each map
      for (size_t i = 0; i < file_word_maps.size(); i ++) {
        for (auto & files_key_val : file_word_maps[i]) {
         auto lookup = common.find(files_key_val.first);
         if (lookup == common.end()) {
           common[files_key_val.first] = 1;
         } else {
           common[files_key_val.first] ++;
         }
      }
    }
  }

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for (const std::pair<string, unsigned int> & common_key_val : common) {
      if (common_key_val.second == file_word_maps.size()) {
        bool check = true;
        for (auto & files :file_word_maps) {
          if(files.find(common_key_val.first)->second < n) {
            check = false;
          }
      }
      if(check == true) {
        out.push_back(common_key_val.first);
      }
    }
  }
  return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
