#include "../include/subject.h"

Subject::Subject() {
    myDate d(2024, 1, 14, 15, 30);
    Exam e(d);
    exams.insert(std::make_pair(d, e));
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