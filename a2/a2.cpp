////////////////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Gerald
// CS email:       gerald@cs.wisc.edu
//
// Description:    The source file for a2.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A2.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions/methods.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
////////////////////////////////////////////////////////////////////////////////

#include "a2.hpp"
#include "trim.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

void cleanData(std::ifstream &inFile, std::ofstream &outFile,
               std::unordered_set<std::string> &stopwords) {
    string scooper;
    while (getline(inFile, scooper)) {
        replaceHyphensWithSpaces(scooper);
        vector<string> vLine, v2Line;
        splitLine(scooper, vLine);
        removePunctuation(vLine, v2Line);
        removeWhiteSpaces(v2Line);
        removeEmptyWords(v2Line);
        removeSingleLetterWords(v2Line);
        removeStopWords(v2Line, stopwords);
        vector<string>::iterator p;
        for (p = v2Line.begin(); p != v2Line.end(); p++) {
            outFile << *p << " ";
        }
        outFile << endl;
    }

}

void fillDictionary(std::ifstream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    string scooper;
    while (getline(newInFile, scooper)) {
        //split each line to handle each string individually
        vector<string> cLine;
        splitLine(scooper, cLine);
        //rating is the first element in each cleaned line
        int rating = stoi(cLine[0]);
        for (auto it = cLine.begin() + 1; it != cLine.end(); it++) {
            auto elem = dict.find(*it);
            //add new string if not found in map, else update existing string with new values
            if (elem == dict.end()) {
                dict.emplace(*it, make_pair<long, long>(rating, 1));
            } else {
                (elem->second).first = (elem->second).first + rating;
                (elem->second).second++;
            }
        }
    }
}

void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    string currsw;
    //get each string and put them into the stopwords set
    while (getline(inFile, currsw)) {
        stopwords.insert(currsw);
    }
}

void rateReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {
    //set the decimal precision
    ratingsFile << setprecision(2) << fixed;
    string scooper;

    while (getline(testFile, scooper)) {
        //empty review gets a rating of two
        if (scooper.empty()) {
            ratingsFile << 2 << endl;
            continue;
        }
        //split each line into individual strings
        vector<string> cLine;
        splitLine(scooper, cLine);
        vector<double> ratings;
        for (string s : cLine) {
            auto it = dict.find(s);
            //if the string does not exist in the dictionary, give it a tentative rating of two
            //if the string exists in the dictionary, calculate its average rating across all reviews
            if (it == dict.end()) {
                ratings.emplace_back(2.00);
            } else {
                double r = (it->second).first;
                double c = (it->second).second;
                ratings.emplace_back(r / c);
            }
        }
        //obtain average rating over all strings in the line
        double avgRating = 0.00;
        for (auto &n : ratings) {
            avgRating += n;
        }
        avgRating = avgRating / ratings.size();
        ratingsFile << avgRating << endl;
    }
}

void removeEmptyWords(std::vector<std::string> &tokens) {
    //only increment iterator if no erasure takes place
    //otherwise, erase sets iterator to the next element in the vector
    auto it = tokens.begin();
    while (it != tokens.end()) {
        if ((*it).length() == 0) {
            it = tokens.erase(it);
        } else {
            it++;
        }
    }
}

void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {
    vector<string>::iterator it;
    string result;
    //copy the string to result; if any punctuation exists, remove it before pushing result into outTokens
    for (it = inTokens.begin(); it != inTokens.end(); it++) {
        result = "";
        remove_copy_if((*it).begin(), (*it).end(),
                       std::back_inserter(result), //Store output
                       std::ptr_fun<int, int>(&std::ispunct)
        );
        outTokens.push_back(result);
    }
}

void removeSingleLetterWords(std::vector<std::string> &tokens) {
    //check first character of the string; if the string is of length one and is not a digit, remove
    auto it = tokens.begin();
    while (it != tokens.end()) {
        char t = (*it)[0];
        if ((*it).length() == 1 && !isdigit(t)) {
            it = tokens.erase(it);
        } else {
            it++;
        }
    }
}

void removeStopWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &stopwords) {
    //search stopwords set for the current word; if it exists, erase it from tokens
    auto it = tokens.begin();
    while (it != tokens.end()) {
        if (stopwords.find(*it) != stopwords.end()) {
            it = tokens.erase(it);
        } else {
            it++;
        }
    }
}

void removeWhiteSpaces(std::vector<std::string> &tokens) {
    //call trim() on every string
    vector<string>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); it++) {
        *it = trim(*it);
    }
}

void replaceHyphensWithSpaces(std::string &line) {
    //check every character in each line for hyphens and replace them with spaces
    for (char &i : line) {
        if (i == '-') {
            i = ' ';
        }
    }
}

void splitLine(std::string &line, std::vector<std::string> &words) {
    //use a string stream to push each individual word delineated by whitespaces into a vector
    stringstream ssLine(line);
    string w;
    while (ssLine >> w) {
        words.push_back(w);
    }
}

