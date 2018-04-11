///////////////////////////////////////////////////////////////////////////////
// File Name:      processStudent.cpp
//
// Author:         <your name>
// CS email:       <your CS email>
//
// Description:    Methods to perform some processing on student objects.
///////////////////////////////////////////////////////////////////////////////

#include "processStudent.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>


void fillStudents(std::ifstream &inFile,
                  std::vector<GradStudent> &gstudents,
                  std::vector<UndergradStudent> &ugstudents) {
    std::string s;
    //read each line of the file for a new student
    while (std::getline(inFile, s)) {
        //make new istringstream, then call getline with ',' delimiter to populate a vector for easy reading
        std::istringstream iss(s);
        std::vector<std::string> line;
        std::string b;
        //populate the vector with individual fields
        for (int i = 0; i < 12; i++) {
            std::getline(iss, b, dlm);
            line.push_back(b);
        }
        //get the last data value, its delimiter is '\n' instead
        std::getline(iss, b);
        line.push_back(b);
        //identify each data value based on position
        std::string type = line[0];
        std::string name = line[1];
        //I guess atoi and atof only take c-strings? whatever those are? read up dude
        int yearOfBirth = atoi(line[2].c_str());
        std::vector<double> assignmentScores;
        //read in all the assignment scores and put them in a double vector
        for (int j = 3; j < 10; j++) {
            double score = atof(line[j].c_str());
            assignmentScores.push_back(score);
        }
        double projectScore = atof(line[10].c_str());
        //read in the last two fields; careful, these are different depending on the type of student
        std::string T1 = line[11];
        std::string T2 = line[12];
        //build a student depending on type; use the last 2 fields per type of student
        if (type == "G") {
            GradStudent newStudent(name, yearOfBirth, assignmentScores, projectScore, T1, T2);
            gstudents.push_back(newStudent);
        } else if (type == "U") {
            UndergradStudent newStudent(name, yearOfBirth, assignmentScores, projectScore, T1,
                                        T2);
            ugstudents.push_back(newStudent);
        }
    }
    return;
}

void printStudents(const std::vector<std::reference_wrapper<Student>> &students) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        it->get().printDetails();
        std::cout << std::endl;
    }
    return;
}

void computeStatistics(std::vector<std::reference_wrapper<Student>> &students) {
    // compute the # of students based on the type of students.
    double numStudents;
    if (typeid(students[0].get()) == typeid(UndergradStudent)) {
        std::cout << "Number of students = " << UndergradStudent::getNumStudents() << std::endl;
        numStudents = UndergradStudent::getNumStudents();
    } else {
        std::cout << "Number of students = " << GradStudent::getNumStudents() << std::endl;
        numStudents = GradStudent::getNumStudents();
    }
    // compute the mean of the total score.
    double mean = 0;
    for (auto it = students.begin(); it != students.end(); ++it) {
        mean += it->get().getTotal();
    }
    mean = mean / numStudents;
    std::cout << "The mean of the total score = " << mean << std::endl;
    // sort and print the students based on their total.
    std::sort(students.begin(), students.end(),
              [](const std::reference_wrapper<Student> &lhs, const std::reference_wrapper<Student> &rhs) {
                  return lhs.get().getTotal() > rhs.get().getTotal();
              });
    std::cout << "The sorted list of students (id, name, total, grade) in descending order of total:" << std::endl;
    for (auto it = students.begin(); it != students.end(); ++it) {
        std::cout << it->get().getId() << ", " << it->get().getName() << ", " << it->get().getTotal() << ", "
                  << it->get().getGrade() << std::endl;
    }
    std::cout << std::endl;
    return;
}

