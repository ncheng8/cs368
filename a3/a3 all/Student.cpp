//
//
//

#include <iostream>
#include "Student.hpp"

int Student::numStudents = 0;

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

void Student::printDetails() {
    std::cout << "STUDENT DETAILS:" << std::endl;
    std::cout << "Id = " << getId() << std::endl;
    std::cout << "Name = " << getName() << std::endl;
    std::cout << "Age = " << getAge() << std::endl;
    std::cout << "Assignments = [";
    for (auto it = assignmentsScore.begin(); it != assignmentsScore.end(); it++) {
        if (it == assignmentsScore.begin()) {
            std::cout << *it;
        } else {
            std::cout << ", " << *it;
        }
    }
    std::cout << "]\n";
    std::cout << "Project = " << projectScore << std::endl;
}




