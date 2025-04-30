#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

// helper to recursively build words
void build_words(string current, const string& in, string floating, const set<string>& dict, set<string>& result, int index);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;
    build_words("", in, floating, dict, result, 0);
    return result;
}

// Define any helper functions here
void build_words(string current, const string& in, string floating, const set<string>& dict, set<string>& result, int index) {
    // base case - if current word == target length
    if (current.size() == in.size()) {
        // check if all floating letters used
        if (floating.empty() && dict.find(current) != dict.end()) {
            result.insert(current);
        }
        return;
    }

    // if fixed letter exists at current position
    if(in[index] != '-') {
        build_words(current + in[index], in, floating, dict, result, index + 1);
    }
    else {
        // count number of blanks remaining
        int blanks_left = 0;
        for(int i = index; i < in.size(); ++i) {
            if(in[i] == '-') blanks_left++;
        }

        // if number of blanks == number of floating letters
        if(blanks_left == floating.size()) {
            // must place only floating letters
            for(size_t i = 0; i < floating.size(); ++i) {
                char c = floating[i];
                string next_floating = floating;
                next_floating.erase(i, 1);
                build_words(current + c, in, next_floating, dict, result, index + 1);
            }
        }
        else {
            // can use any letter
            for(char c = 'a'; c <= 'z'; ++c)
            {
                string next_floating = floating;
                size_t pos = next_floating.find(c);
                if(pos != string::npos) {
                    next_floating.erase(pos, 1);
                }
                build_words(current + c, in, next_floating, dict, result, index + 1);
            }
        }
    }
}
