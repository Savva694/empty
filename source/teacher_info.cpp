#include <map>

#include "../include/teacher_info.h"

TeacherInfo::Teacher::Teacher(const Teacher& other) = default;

TeacherInfo::Teacher::Teacher(const std::string& login, const std::string& password) : login(login), password(password) {};

void TeacherInfo::Teacher::add_info(const std::string& surname_, const std::string& name_,
                 const std::string& patronymic_, const std::string& department_, const std::string& subject_) {
    surname = surname_;
    name = name_;
    patronymic = patronymic_;
    department = department_;
    subject = subject_;
}

void TeacherInfo::Teacher::add_exam(const std::string& subject, const myDate& date) {
    exams.push_back(std::make_pair(subject, date));
}

std::string TeacherInfo::Teacher::get_password() const {
    return password;
}

std::string TeacherInfo::Teacher::get_subject() const {
    return subject;
}

std::vector<std::pair<std::string, myDate>> TeacherInfo::Teacher::get_my_exams() const {
    return exams;
}



bool TeacherInfo::exist(const std::string& login, const std::string& password) {
    auto it = teachers.find(login);
    if (it == teachers.end()) return false;
    return it->second.get_password() == password;
}

bool TeacherInfo::add_teacher(const std::string& login, const std::string& password) {
    if (teachers.find(login) != teachers.end()) return false;
    teachers.insert(make_pair(login, Teacher(login, password)));
    return true;
}

void TeacherInfo::add_info(const std::string& login, const std::string& surname, const std::string& name, 
                    const std::string& patronymic, const std::string& department, const std::string& subject) {
    auto it = teachers.find(login);
    it->second.add_info(surname, name, patronymic, department, subject);
}

std::string TeacherInfo::get_subject(const std::string& login) const {
    auto it = teachers.find(login);
    return it->second.get_subject();
}

void TeacherInfo::add_exam(const std::string& login, const std::string& subject, const myDate& date) {
    auto it = teachers.find(login);
    it->second.add_exam(subject, date);
}

std::vector<std::pair<std::string, myDate>> TeacherInfo::get_exams_for_teacher(const std::string& login) const {
    auto it = teachers.find(login);
    return it->second.get_my_exams();
}