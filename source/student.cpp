#include "../include/student.h"

Student::Student(const std::string& login, const std::string& password): 
                            login(login), password(password), id(StudentId()) {}

void Student::add_info(const std::string& _name,
                    const std::string& _patronymic, 
                    const std::string& _surname,
                    size_t _course,
                    const std::string& _group) {
    name = _name;
    patronymic = _patronymic;
    surname = _surname;
    course = _course;
    group = _group;
}