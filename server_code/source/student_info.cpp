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

void StudentInfo::Student::add_exam(const std::string& subject, const myDate& date) {
    exams.push_back(std::make_pair(subject, date));
}

std::string StudentInfo::Student::get_password() const {
    return password;
}

std::vector<std::pair<std::string, myDate>> StudentInfo::Student::get_my_exams() const {
    return exams;
}

std::vector<std::pair<std::string, size_t>> StudentInfo::Student::get_marks() const {
    std::vector<std::pair<std::string, size_t>> ans;
    for (auto it : marks) {
        if (it.second > 0) ans.push_back(it);
    }
    return ans;
}



bool StudentInfo::exist(const std::string& login_, const std::string& password_) {
    auto it = students.find(login_);
    if (it == students.end()) return false;
    return it->second.get_password() == password_;
}

bool StudentInfo::add_student(const std::string& login, const std::string& password) {
    if (students.find(login) != students.end()) return false;
    students.insert(make_pair(login, Student(login, password)));
    return true;
}

void StudentInfo::add_info(const std::string& login, const std::string& surname, const std::string& name, 
                    const std::string& patronymic, size_t course, const std::string& group) {
    auto it = students.find(login);
    it->second.add_info(surname, name, patronymic, course, group);
}

void StudentInfo::add_exam(const std::string& login, const std::string& subject, const myDate& date) {
    auto it = students.find(login);
    it->second.add_exam(subject, date);
}

std::vector<std::pair<std::string, myDate>> StudentInfo::get_exams_for_student(const std::string& login) const {
    auto it = students.find(login);
    return it->second.get_my_exams();
}

std::vector<std::pair<std::string, size_t>> StudentInfo::get_marks(const std::string& login) const {
    auto it = students.find(login);
    return it->second.get_marks();
}
