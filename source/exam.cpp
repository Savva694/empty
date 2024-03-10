#include "../include/exam.h"

Exam::Exam(const myDate& myDate) : start_myDate(myDate) {};

bool Exam::add_student(const std::string& login) {
    if (students_login.find(login) != students_login.end()) return false;
    students_login.insert(login);
    return true;
}