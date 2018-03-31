//
//
//

#include <iostream>
#include "Student.hpp"

int Student::numStudents = 0;

/*
    int Student::id;
    std::string Student::name;
    int Student::yearOfBirth;
    std::vector<double> Student::assignmentsScore;
    double Student::projectScore;
*/
/*
Student::Student() {
    name = "noname";
    yearOfBirth = 0;
    ++Student::numStudents;
}
 */

Student::Student(std::string name,
                 int yearOfBirth,
                 const std::vector<double> &assignmentsScore,
                 double projectScore) {
    this->name = name;
    this->yearOfBirth = yearOfBirth;
    this->assignmentsScore = assignmentsScore;
    this->projectScore = projectScore;
    ++numStudents;
    this->id = numStudents;
}

int Student::getId() {
    return id;
}

std::string Student::getName() {
    return name;
}

int Student::getYearOfBirth() {
    return yearOfBirth;
}

int Student::getAge() {
    return current_year - yearOfBirth;
}

const std::vector<double> &Student::getAssignmentsScore() {
    return assignmentsScore;
}

double Student::getProjectScore() {
    return projectScore;
}

int Student::getNumStudents() {
    return numStudents;
}

/*   void Student::setYearOfBirth(int year) {
       yob = year;
   }

   void Student::setName(std::string name) {
       // this->name = name;
       Student::name = name;
   }
*/
void Student::printDetails() {
    std::cout << "Id = " << getId() << std::endl;
    std::cout << "Name = " << getName() << std::endl;
    std::cout << "Age = " << getAge() << std::endl;
    std::cout << "Assignments = [";
    for (auto it = assignmentsScore.begin(); it != assignmentsScore.end(); it++) {
        if (it == assignmentsScore.begin()) {
            std::cout << *it;
        } else {
            std::cout << "," << *it;
        }
    }
    std::cout << "]\n";
    std::cout << "Project = " << projectScore << std::endl;
}
/*    virtual void Student::printDetails();

    virtual double Student::getTotal();

    virtual std::string Student::getGrade();
*/


// there is NO implementation of Student::getType() in this class
// because it is purely virtual




