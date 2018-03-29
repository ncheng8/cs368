//
// Created by Adalbert Gerald Soosai Raj on 10/26/16.
//

#include <iostream>
#include "GradStudent.hpp"

GradStudent::GradStudent(std::string name,
                         int yob,
                         std::string rArea) : Student(name, yob){

   this->researchArea = rArea;
}

void GradStudent::printStudent() {
    Student::printStudent();
    std::cout << "researchArea = " << researchArea << std::endl;
    std::cout << "Type = " << getType() << std::endl;
}

std::string GradStudent::getType() {
    return "Grad";
}
