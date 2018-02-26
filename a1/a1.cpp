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

using namespace std;

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
	} 
	else if(fn == 2)
	{
		cout << "Enter the name of the second file: ";
	}
	getline(cin, filename);
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

	vector<string>::iterator scoop;
	vector<string>::iterator sloop;
	string scooper;	

	for (scoop = names1.begin(); scoop != names1.end(); scoop++)
	{
		cout << *scoop << endl;
	}
	cout << endl;
	for (sloop = names2.begin(); sloop != names2.end(); sloop++)
	{
		cout << *sloop << endl;
	}	
	


	file1.close();
	file2.close();	
}
