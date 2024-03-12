#include "../include/exam.h"

Exam::Exam(const myDate& myDate) : start_myDate(myDate) {};

bool Exam::add_student(const std::string& login) {
    if (students_login.find(login) != students_login.end()) return false;
    students_login.insert(login);
    return true;
}

bool Exam::add_teacher(const std::string& login) {
    if (teachers_login.find(login) != teachers_login.end()) return false;
    teachers_login.insert(login);
    return true;
}

bool Exam::distribute() {
    if (!students_login.empty() && teachers_login.empty()) return false;
    std::vector<std::string> teachers_copy;
    for (std::string it : teachers_login) {
        teachers_copy.push_back(it);
    }
    for (std::string login : students_login) {
        size_t teacher = rand() % teachers_login.size();
        students_for_teacher[teachers_copy[teacher]].insert(login);
        examiners[login] = teachers_copy[teacher];
    }
    return true;
}

bool Exam::start() {
    return distribute();
}

// bool Exam::check_student_in_exam(const std::string& login) const {
// }

// std::string Exam::get_questions(const std::string& login, size_t mark) const {
// }
