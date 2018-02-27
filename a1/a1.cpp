///////////////////////////////////////////////////////////////////////
// File Name:      a1.cpp
//
// Author:         Nicholas Cheng
// CS email:       nicholasc@cs.wisc.edu
// 
// Course:         CS 368 (C++)
// Section:        2
// Instructor:     Kuemmel       
//
// Description: This program reads two files of class rosters, analyzes them,
// and prints their stats. In addition, it prints students in the intersection
// and union of the two classes to separate files.
//
// Sources: Inserter suggestion from stackoverflow
//          c++ api website
//
// URL(s) of sources: http://www.cplusplus.com/
// https://stackoverflow.com/questions/13448064/how-to-find-the-intersection-of-two-stdset-in-c
///////////////////////////////////////////////////////////////////////



#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

string class1;
string class2;

/**
 * @brief This function simply acquires a filename from the
 *	  user and appends ".txt" to it
 * 
 * @param fn The number of the requests, used solely to
 * 	     dictate the text displayed to the user.
 *
 */
string getFileName(int fn) {
    string filename;
    //differentiate between first and second class
    if (fn == 1) {
        cout << "Enter the name of the first file: ";
        getline(cin, filename);
        class1 = filename;
    } else if (fn == 2) {
        cout << "Enter the name of the second file: ";
        getline(cin, filename);
        class2 = filename;
    }
    //append ".txt" so the file can be propertly identified and opened
    filename.append(".txt");

    return filename;
}

/**
 * @brief This function uses the previous function to
 * 	  ask for a file name and attempt to open it.
 *
 * @param infile A reference to the yet-to-be-opened 
 *		 input file stream object.
 * @param fn The number of the requests, used solely to 
	     dictate the text displayed to the user.
 *
 */
void openFile(ifstream &infile, int fn) {
    string filename;
    filename = getFileName(fn);
    infile.open(filename.c_str());
    //loop if the given file name cannot be resolved to an actual file
    while (!infile) {
        if (fn == 1) {
            cout << "Input file " << class1 << " is NOT found. Please try again." << endl;
        } else {
            cout << "Input file " << class2 << " is NOT found. Please try again." << endl;
        }
        filename = getFileName(fn);
        infile.open(filename.c_str());
    }
}

/**
 * @brief This function reads the names of students from an input
 *     	  file stream object and stores them in a vector.
 * 
 * @param infile A reference to the input file stream object.
 * @param studentsList A reference to the vector that will store the students' names. 
 *
 */
void getStudents(ifstream &infile, vector<string> &studentsList) {
    string scooper;
    //read the file line by line and push the names into the vector
    while (getline(infile, scooper)) {
        studentsList.push_back(scooper);
    }
}

/**
 * @brief This function reads the names of students from a
 *     	  sorted set and prints them to a file.
 *
 * @param list A reference to the list that contains the students' names.
 * @param fName The name of the file to be opened and written to.

 */
void printToFile(set<string> &list, string fName) {
    ofstream print;
    print.open(fName.c_str());
    set<string>::iterator it;
    //open file based on fName and print names into the file
    for (it = list.begin(); it != list.end(); it++) {
        print << *it << endl;
    }
}

int main() {
    //create two ifstream references and use them to open and read the class files
    ifstream file1;
    ifstream file2;

    openFile(file1, 1);
    openFile(file2, 2);

    vector<string> names1;
    vector<string> names2;

    getStudents(file1, names1);
    getStudents(file2, names2);

    //it is common courtesy to close files once you are done with them
    file1.close();
    file2.close();

    cout << "Number of students in " << class1 << " = " << names1.size() << endl;
    cout << "Number of students in " << class2 << " = " << names2.size() << endl;

    //set_intersection and set_union only work on sorted vectors; I learned the hard way
    sort(names1.begin(), names1.end());
    sort(names2.begin(), names2.end());

    set<string> intersect;
    set<string> unified;
    set<string>::iterator stroop;

    //find the intersect of the two classes and put those names into intersect
    set_intersection(names1.begin(), names1.end(), names2.begin(), names2.end(),
                     inserter(intersect, intersect.begin()));
    //find the union of hte two classes and put those names into unified ("union" is reserved);
    set_union(names1.begin(), names1.end(), names2.begin(), names2.end(),
              inserter(unified, unified.begin()));

    cout << "Number of students that are present in BOTH " <<
         class1 << " AND " << class2 << " = " << intersect.size() << endl;
    cout << "Number of students that are present in EITHER " <<
         class1 << " OR " << class2 << " = " << unified.size() << endl;

    cout << endl;

    //print all students that are in both classes
    cout << "List of students that are present in BOTH " << class1 << " AND " << class2
         << ":\n";
    for (stroop = intersect.begin(); stroop != intersect.end(); stroop++) {
        cout << *stroop << endl;
    }
    cout << endl;

    //conditional code for printing the results of sending students' names
    // to the intersection.txt and union.txt files
    printToFile(intersect, "intersection.txt");
    if (intersect.empty()) {
        cout << "The file intersection.txt is EMPTY since there are no students that are present in BOTH "
             << class1 << " AND " << class2 << endl;
    } else {
        cout << "The names of the " << intersect.size() << " students that are present in BOTH "
             << class1 << " AND " << class2 << " are written to the file named intersection.txt\n";
    }

    printToFile(unified, "union.txt");
    if (unified.empty()) {
        cout << "The file union.txt is EMPTY since there are no students in the 2 files "
             << class1 << " AND " << class2 << endl;
    } else {
        cout << "The names of the " << unified.size() << " students that are present in EITHER "
             << class1 << " AND " << class2 << " are written to the file named union.txt\n";
    }
    return 0;
}
