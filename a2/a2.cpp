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
    // Implement this method.
    // # of lines of code in Gerald's implementation: 13
    // Do the following operations on each review before
    // storing it to the output file:
    //   1. Replace hyphens with spaces.x
    //   2. Split the line of text into individual words.x
    //   3. Remove the punctuation marks from the words.x
    //   4. Remove the trailing and the leading whitespaces in each word.x
    //   5. Remove the empty words.x
    //   6. Remove words with just one character in them. You should NOT remove
    //      numbers in this step because if you do so, you'll lose the ratings.
    //   7. Remove stopwords.

    //vector<string> reviews;
    string scooper;
    while(getline(inFile, scooper)) {
        replaceHyphensWithSpaces(scooper);
        vector<string> vLine, v2Line;
        splitLine(scooper, vLine);
        v2Line.push_back("");
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
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
    string scooper;
    while(getline(newInFile, scooper)) {
        vector<string> cLine;
        splitLine(scooper, cLine);
        int rating = stoi(cLine[0]);
        for(vector<string>::iterator it = cLine.begin() + 1; it != cLine.end(); it++) {
            unordered_map<string, pair<long, long>>::iterator elem = dict.find(*it);
            if (elem == dict.end()) {
                dict.emplace(*it, make_pair<long, long>(rating,1));
            } else {
                (elem->second).first = (elem->second).first + rating;
                (elem->second).second++;
            }
        }
    }
    for(unordered_map<string, pair<long, long>>::iterator it = dict.begin();
        it != dict.end(); ++it) {
        std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }
}


void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    string currsw;
    while(getline(inFile, currsw)) {
        stopwords.insert(currsw);
    }
}

void rateReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
}

void removeEmptyWords(std::vector<std::string> &tokens) {
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    vector<string>::iterator it = tokens.begin();
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
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    vector<string>::iterator it;
    string result;
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
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    vector<string>::iterator it = tokens.begin();
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
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    vector<string>::iterator it = tokens.begin();
    while (it != tokens.end()) {
        if (stopwords.find(*it) != stopwords.end()) {
            it = tokens.erase(it);
        } else {
            it++;
        }
    }
}

void removeWhiteSpaces(std::vector<std::string> &tokens) {
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    // You may want to use the trim() method from the trim.*pp files in a2.
    vector<string>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); it++) {
        *it = trim(*it);
    }
}

void replaceHyphensWithSpaces(std::string &line) {
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '-') {
            line[i] = ' ';
        }
    }
}

void splitLine(std::string &line, std::vector<std::string> &words) {
    // Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    stringstream ssLine(line);
    string w;
    while (ssLine >> w) {
        words.push_back(w);
    }
}

