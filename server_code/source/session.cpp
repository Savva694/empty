#include "../include/session.h"

Session::Session() = default;

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

const std::string& Session::teacher_watch_examinees(const std::string& subject, const myDate& date, const std::string& teacher_login) const {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return 0;
    return it->second.teacher_watch_examinees(date, teacher_login);
}

bool Session::end_exam(const std::string& subject, const myDate& date) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return 0;
    return it->second.end_exam(date);
}

// bool Session::check_student_in_exam(const std::string& subject, const myDate& date, const std::string& login) const {
//     auto it = subjects.find(subject);
//     if (it == subjects.end()) return false;
//     return it->second.check_student_in_exam(date, login);
// }

bool Session::check_student_in_exam(const std::string& subject, const myDate& date, const std::string& login) const {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return false;
    return it->second.check_student_in_exam(date, login);
}

std::string Session::get_questions(const std::string& subject, const myDate& date, const std::string& login) const {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return "0";
    return it->second.get_questions(date, login);
}

bool Session::save_mark(const std::string& subject, const myDate& date, const std::string& login, size_t mark) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return false;
    return it->second.save_mark(date, login, mark);
}

bool Session::student_end_exam(const std::string& subject, const myDate& date, const std::string& login) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return false;
    return it->second.student_end_exam(date, login);
}

std::pair<bool, const std::string&> Session::save_solution(
        const std::string& subject, const myDate& date, const std::string& login, const std::string& sol) {
    auto it = subjects.find(subject);
    if (it == subjects.end()) return {false, ""};
    return it->second.save_solution(date, login, sol);
}

bool Session::rate_student(const std::string& subject, const myDate& date, const std::string& login, 
        const std::string& student_login, size_t mark) {
    auto it = subjects.find(subject);
    if (it != subjects.end()) return false;
    return it->second.rate_student(date, login, student_login, mark);
}

std::string Session::check_solution(const std::string& subject, const myDate& date, const std::string& login, 
        const std::string& student_login) {
    auto it = subjects.find(subject);
    if (it != subjects.end()) return "0";
    return it->second.check_solution(date, login, student_login);
}

