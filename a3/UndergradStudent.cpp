//
//
//

#include <iostream>
#include "UndergradStudent.hpp"

int UndergradStudent::numUndergradStudents = 0;

// has 3 parameters
// calls the constructor of Student 
UndergradStudent::UndergradStudent(std::string name,
                                   int yearOfBirth,
                                   const std::vector<double> &assignmentsScore,
                                   double projectScore,
                                   std::string residenceHall,
                                   std::string yearInCollege) : Student(name, yearOfBirth, assignmentsScore,
                                                                        projectScore) {
    this->residenceHall = residenceHall;
    this->yearInCollege = yearInCollege;
    ++numUndergradStudents;
}

// polymorphic function...notice its implementation
// does NOT include 'virtual' or 'override'
// also notice that the first line calls printStudent in the base class
void UndergradStudent::printDetails() {
    Student::printDetails();
    std::cout << "Grade = " << this->getGrade() << std::endl;
    std::cout << "Type = Undergraduate Student" << std::endl;
    std::cout << "Residence Hall = " << residenceHall << std::endl;
    std::cout << "Year In College = " << yearInCollege << std::endl;
}

std::string UndergradStudent::getResidenceHall() {
    return residenceHall;
}

std::string UndergradStudent::getYearInCollege() {
    return yearInCollege;
}

int UndergradStudent::getNumStudents() {
    return numUndergradStudents;
}

double UndergradStudent::getTotal() {
    //return 0.0;
    double pavg = 0;
    std::vector<double> assignments = this->getAssignmentsScore();
    for (auto it = this->getAssignmentsScore().begin(); it != this->getAssignmentsScore().end(); it++) {
        pavg += *it;
    }
    double avg = pavg / 7.0;
    double total = avg * 0.7 + this->getProjectScore() * 0.3;
    return total;
}

std::string UndergradStudent::getGrade() {
    if (this->getTotal() >= 70) {
        return "CR";
    } else {
        return "N";
    }
}
/*
// another polymorphic function
std::string UndergradStudent::getType() {
    return "Undergrad";
}
 */

