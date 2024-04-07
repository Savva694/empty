#include "../include/subject.h"

Subject::Subject() = default;

std::vector<myDate> Subject::get_exams() const {
    std::vector<myDate> ans;
    for (auto j : exams) {
        ans.push_back(j.first);
    }
    return ans;
}

bool Subject::add_student(const std::string& login, const myDate& myDate) {
    auto it = exams.find(myDate);
    if (it == exams.end()) return false;
    return it->second.add_student(login);
}

bool Subject::add_teacher(const std::string& login, const myDate& date) {
    auto it = exams.find(date);
    if (it == exams.end()) return false;
    return it->second.add_teacher(login);
}

bool Subject::add_exam(const myDate& date) {
    auto it = exams.lower_bound(date);
    if (it != exams.end() && it->first.get_only_date() == date.get_only_date()) return false;
    if (it != exams.begin()) {
        --it;
        if (it->first.get_only_date() == date.get_only_date()) return false;
    }
    exams.insert(std::make_pair(date, Exam(date)));
    return true;
}

bool Subject::add_question(size_t rate, const std::string& question) {
    questions[rate - 3].push_back(question);
    return true;
}

bool Subject::start_exam(const myDate& date) {
    auto it = exams.find(date);
    if (it == exams.end()) return false;
    return it->second.start();
}

const Subject::std::unordered_set<std::string>& teacher_watch_examinees(const myDate& date, const std::string& teacher_login) const {
    auto it = exams.find(date);
    if (it == exams.end()) return std::unordered_set<std::string>("228_1337_void_login");
    return it->second.teacher_watch_examinees(teacher_login);
}

bool Subject::end_exam(const myDate& date) {
    auto it = exams.find(date);
    if (it == exams.end()) return 0;
    return it->second.end_exam();
}

// bool Subject::check_student_in_exam(const myDate& date, const std::string& login) const {
// }

bool Subject::check_student_in_exam(const myDate& date, const std::string& login) const {
    auto it = exams.find(date);
    if (it == exams.end()) return false;
    return it->second.check_student_in_exam(login);
}

std::string Subject::get_questions(const myDate& date, const std::string& login) const {
    auto it = exams.find(date);
    if (it == exams.end()) return "0";
    std::vector<std::pair<size_t, size_t>> vect = it->second.get_questions(login);
    std::string ans = "";
    for (std::pair<size_t, size_t> question : vect) {
        ans += questions[question.first][question.second];
        ans += "\n";
    }
    return ans;
}

bool Subject::save_mark(const myDate& date, const std::string& login, size_t mark) {
    auto it = exams.find(date);
    if (it == exams.end()) return false;
    return it->second.save_mark(login, mark);
}

bool Subject::student_end_exam(const myDate& date, const std::string& login) {
    auto it = exams.find(date);
    if (it == exams.end()) return false;
    return it->second.student_end_exam(login);
}

std::pair<bool, const std::string&> Subject::save_solution(const myDate& date, 
        const std::string& login, const std::string& sol) {
    auto it = exams.find(date);
    if (it == exams.end()) return {false, ""};
    return it->second.save_solution(login, sol);
}

bool Subject::rate_student(const myDate& date, const std::string& login, const std::string& student_login, size_t mark) {
    auto it = exams.find(date);
    if (it == exams.end()) return false;
    return it->second.rate_student(login, student_login, mark);
}

std::string Subject::check_solution(const myDate& date, const std::string& login, const std::string& student_login) {
    auto it = exams.find(date);
    if (it == exams.end()) return "0";
    return it->second.check_solution(login, student_login);
}
