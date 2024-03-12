#include "../include/session.h"

Session::Session() {
    // Subject sub;
    // subjects.insert(std::make_pair("matan", sub));
}

std::string Session::get_subjects() const {
    std::string ans = "";
    for (auto j : subjects) {
        ans += j.first;
        ans += ' ';
    }
    return ans;
}

std::vector<myDate> Session::get_exams(std::string subj) const {
    auto it = subjects.find(subj);
    if (it == subjects.end()) return std::vector<myDate>();
    return it->second.get_exams();
}

bool Session::add_student(const std::string& login, const std::string& subj, const myDate& date) {
    auto it = subjects.find(subj);
    if (it == subjects.end()) return false;
    return it->second.add_student(login, date);
}

bool Session::add_teacher(const std::string& login, const std::string& subj, const myDate& date) {
    auto it = subjects.find(subj);
    if (it == subjects.end()) return false;
    return it->second.add_teacher(login, date);
}

bool Session::add_subject(const std::string& subject) {
    auto it = subjects.find(subject);
    if (it != subjects.end()) return false;
    subjects.insert(std::make_pair(subject, Subject()));
    return true;
}

bool Session::add_exam(const std::string& subject, const myDate& date) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return false;
    return it->second.add_exam(date);
}

bool Session::add_question(const std::string& subject, size_t rate, const std::string& question) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return false;
    return it->second.add_question(rate, question);
}

bool Session::start_exam(const std::string& subject, const myDate& date) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return false;
    return it->second.start_exam(date);
}

// bool Session::check_student_in_exam(const std::string& subject, const myDate& date, const std::string& login) const {
//     auto it = subjects.find(subject);
//     if (it == subjects.end()) return false;
//     return it->second.check_student_in_exam(date);
// }