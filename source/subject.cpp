#include "../include/subject.h"

Subject::Subject() {
    // myDate d(2024, 1, 14, 15, 30);
    // Exam e(d);
    // exams.insert(std::make_pair(d, e));
}

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