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
// Description:   
//
// Sources:       
//
// URL(s) of sources:           
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
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
string getFileName(int fn)
{
	string filename;
	if (fn == 1) 
	{
		cout << "Enter the name of the first file: ";
        getline(cin, filename);
        class1 = filename;
	} 
	else if(fn == 2)
	{
		cout << "Enter the name of the second file: ";
        getline(cin, filename);
        class2 = filename;
	}
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
 
 */	
void openFile(ifstream &infile, int fn) 
{
	string filename;
	filename = getFileName(fn);
	infile.open(filename.c_str());
	while (!infile) 
	{
		cout << "Input file " << filename << " is NOT found. Please try again." << endl;
		filename = getFileName(fn);
		infile.open(filename.c_str());
	}
	return;
}
/**
 * @brief This function reads the names of students from an input
 *     	  file stream object and stores them in a vector.
 * 
 * @param infile A reference to the input file stream object.
 * @param studentsList A reference to the vector that will store the students' names. 
 
 */
void getStudents(ifstream &infile, vector<string> &studentsList) 
{
	string scooper;
	while (getline(infile,scooper))
	{
		studentsList.push_back(scooper);
	}
}
int main()
{
	ifstream file1;
	ifstream file2;

	openFile(file1,1);
	openFile(file2,2);	

	vector<string> names1;	
	vector<string> names2;

	getStudents(file1,names1);
	getStudents(file2,names2);

    cout << "Number of students in " << class1 << " = " << names1.size() << endl;
    cout << "Number of students in " << class2 << " = " << names2.size() << endl;

	vector<string>::iterator scoop;
	vector<string>::iterator sloop;
	string scooper;

    sort(names1.begin(),names1.end());
    sort(names2.begin(),names2.end());
/*
	for (scoop = names1.begin(); scoop != names1.end(); scoop++)
	{
		cout << *scoop << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	for (sloop = names2.begin(); sloop != names2.end(); sloop++)
	{
		cout << *sloop << endl;
	}	
*/

    set<string> intersect;
    set<string> unified;
    set<string>::iterator stroop;

    set_intersection(names1.begin(),names1.end(),names2.begin(),names2.end(),
                     inserter(intersect,intersect.begin()));

    set_union(names1.begin(),names1.end(),names2.begin(),names2.end(),
                     inserter(unified,unified.begin()));

    cout << "Number of students that are present in BOTH " <<
         class1 << " AND " << class2 << " = " << intersect.size() << endl;
    cout << "Number of students that are present in EITHER " <<
         class1 << " OR " << class2 << " = " << unified.size() << endl;

    for (stroop = intersect.begin(); stroop != intersect.end(); stroop++)
    {
        cout << *stroop << endl;
    }


/*
    for (stroop = unified.begin(); stroop != unified.end(); stroop++)
    {
        cout << *stroop << endl;
    }
*/
	file1.close();
	file2.close();
	return 0;
}
