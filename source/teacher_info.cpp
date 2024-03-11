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

bool TeacherInfo::exist(const std::string& login, const std::string& password) {
    auto it = teachers.find(login);
    if (it == teachers.end()) return false;
    return it->second.password == password;
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
    return it->second.subject;
}