#include "../include/exam.h"

Exam::Exam(const myDate& myDate) : start_myDate(myDate) {};

bool Exam::add_student(const std::string& login) {
    if (status != 0 && students.find(login) != students.end()) return false;
    students.insert(login, {});
    return true;
}

bool Exam::add_teacher(const std::string& login) {
    if (status != 0 && teachers_login.find(login) != teachers_login.end()) return false;
    teachers_login.insert(login);
    return true;
}

bool Exam::distribute() {
    if (!students.empty() && teachers_login.empty()) return false;
    std::vector<std::string> teachers_copy;
    for (std::string it : teachers_login) {
        teachers_copy.push_back(it);
    }
    for (auto login : students) {
        size_t teacher = rand() % teachers_login.size();
        teacher_to_students[teachers_copy[teacher]].insert(login, {});
        students[login.first].examiner = teachers_copy[teacher];
    }
    return true;
}

bool Exam::start() {
    status = 1;
    return distribute();
}

bool Exam::check_student_in_exam(const std::string& login) const {
    return students.find(login) != students.end();
}

std::vector<std::pair<size_t, size_t>> Exam::get_questions(const std::string& login) const {
    auto it = students.find(login);
    if (it == students.end()) return {};
    return it->second.questions;
}

bool Exam::save_mark(const std::string& login, size_t mark) {
    auto it = students.find(login);
    if (it == students.end()) return false;
    it->second.mark = mark;
    return true;
}

bool Exam::student_end_exam(const std::string& login) {
    auto it = students.find(login);
    if (it == students.end()) return false;
    students.erase(it);
    return true;
}

const std::unordered_set<std::string>& Exam::teacher_watch_examinees(const std::string& teacher_login) const {
    return status == 1 && add_students_for_teacher[teacher_login];
}

bool Exam::end_exam() {
    if (status == 1) {
        status = 2;
        return 1;
    }
    return 0;
}
