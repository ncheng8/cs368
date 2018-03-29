//
//
//

#include <iostream>
#include "UndergradStudent.hpp"

static int UndergradStudent::numUndergradStudents = 0;
// has 3 parameters
// calls the constructor of Student 
UndergradStudent::UndergradStudent(std::string name,
                     int yearOfBirth,
                     const std::vector<double> &assignmentsScore,
                     double projectScore,
                     std::string residenceHall,
                     std::string yearInCollege) : Student(name,yearOfBirth,assignmentsScore,projectScore) {
    this->residenceHall = residenceHall;
    this->yearInCollege = yearInCollege;
    ++numUndergradStudents;
}

// polymorphic function...notice its implementation
// does NOT include 'virtual' or 'override'
// also notice that the first line calls printStudent in the base class
void UndergradStudent::printDetails() {
    Student::printDetails();
    std::cout << "residenceHall = " << residenceHall << std::endl;
    std::cout << "Type = Undergraduate Student" << std::endl;
}

std::string UndergradStudent::getResidenceHall() {
    return residenceHall;
}

std::string UndergradStudent::getYearInCollege() {
    return yearInCollege;
}

static int UndergradStudent::getNumStudents() {
    return numUndergradStudents;
}
/*
// another polymorphic function
std::string UndergradStudent::getType() {
    return "Undergrad";
}
 */

