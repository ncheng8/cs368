cmake_minimum_required(VERSION 3.9)
project(a3)

set(CMAKE_CXX_STANDARD 11)

add_executable(a3 main.cpp processStudent.cpp GradStudent.cpp UndergradStudent.cpp Student.cpp)