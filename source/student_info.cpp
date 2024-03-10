#include <map>

#include "../include/student_info.h"

StudentInfo::Student::Student(const Student& other) = default;

StudentInfo::Student::Student(const std::string& login, const std::string& password) : login(login), password(password) {};

void StudentInfo::Student::add_info(const std::string& surname_, const std::string& name_,
                 const std::string& patronymic_, size_t course_, const std::string& group_) {
    surname = surname_;
    name = name_;
    patronymic = patronymic_;
    course = course_;
    group = group_;
}

bool StudentInfo::exist(const std::string& login_, const std::string& password_) {
    auto it = students.find(login_);
    if (it == students.end()) return false;
    return it->second.password == password_;
}

bool StudentInfo::add_student(const std::string& login, const std::string& password) {
    if (students.find(login) != students.end()) return false;
    students.insert(make_pair(login, Student(login, password)));
    return true;
}

void StudentInfo::add_info(const std::string& login, const std::string& surname, const std::string& name, 
                    const std::string& patrinomyc, size_t course, const std::string& group) {
    auto it = students.find(login);
    if (it == students.end()) return;
    it->second.add_info(surname, name, patrinomyc, course, group);
}