//
// Created by Adalbert Gerald Soosai Raj on 10/26/16.
//

#include <iostream>
#include "GradStudent.hpp"

int GradStudent::numGradStudents = 0;

GradStudent::GradStudent(std::string name,
                         int yearOfBirth,
                         const std::vector<double> &assignmentsScore,
                         double projectScore,
                         std::string researchArea,
                         std::string advisor) : Student(name, yearOfBirth, assignmentsScore, projectScore) {

    this->researchArea = researchArea;
    this->advisor = advisor;
    ++numGradStudents;
}

void GradStudent::printDetails() {
    Student::printDetails();
    std::cout << "Grade = " << this->getGrade() << std::endl;
    std::cout << "Type = Graduate Student" << std::endl;
    std::cout << "Research Area = " << researchArea << std::endl;
    std::cout << "Advisor = " << advisor << std::endl;
}

std::string GradStudent::getResearchArea() {
    return researchArea;
}

std::string GradStudent::getAdvisor() {
    return advisor;
}

int GradStudent::getNumStudents() {
    return numGradStudents;
}

double GradStudent::getTotal() {
    return 0.0;
    double pavg = 0;
    std::vector<double> assignments = this->getAssignmentsScore();
    for (auto it = this->getAssignmentsScore().begin(); it != this->getAssignmentsScore().end(); it++) {
        pavg += *it;
    }
    double avg = pavg / 7.0;
    double total = avg * 0.5 + this->getProjectScore() * 0.5;
    return total;
}

std::string GradStudent::getGrade() {
    if (this->getTotal() >= 80) {
        return "CR";
    } else {
        return "N";
    }
}
/*
std::string GradStudent::getType() {
    return "Grad";
}
 */
