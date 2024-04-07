#include "../include/exam.h"

Exam::Exam(const myDate& myDate) : start_myDate(myDate) {};

bool Exam::add_student(const std::string& login) {
    if (students.find(login) != students.end()) return false;
    students.insert(login, {});
    return true;
}

bool Exam::add_teacher(const std::string& login) {
    if (teachers_login.find(login) != teachers_login.end()) return false;
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
    it->second.wanted_mark = mark;
    return true;
}

bool Exam::student_end_exam(const std::string& login) {
    auto it = students.find(login);
    if (it == students.end()) return false;
    students.erase(it);
    return true;
}

std::pair<bool, const std::string&> Exam::save_solution(const std::string& login, const std::string& sol) {
    auto it = students.find(login);
    if (it == students.end()) return {false, ""};
    it->second.solution += sol;
    return {true, it->second.examiner};
}

bool Exam::rate_student(const std::string& login, const std::string& student_login, size_t mark) {
    if (teachers_login.find(login) == teachers_login.end() || 
            teacher_to_students[login].find(student_login) == teacher_to_students[login].end()) return false;
    students[student_login].mark = mark;
    return true;
}

std::string Exam::check_solution(const std::string& login, const std::string& student_login) {
    if (teachers_login.find(login) == teachers_login.end() || 
            teacher_to_students[login].find(student_login) == teacher_to_students[login].end()) return "0";
    return students[student_login].solution;
}