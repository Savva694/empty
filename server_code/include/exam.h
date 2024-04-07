#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>

#include "date.h"

class Exam {
    enum ExamStatus {
        not_started = 0,
        started = 1,
        finished = 2;
    }

    struct ExamTaker {
        size_t mark = 0;
        size_t wanted_mark;
        std::vector<std::pair<size_t, size_t>> questions;
        std::string solution = "";
        std::string examiner;
    };

    myDate start_myDate;
    std::unordered_set<std::string> teachers_login;
    std::unordered_map<std::string, ExamTaker> students;
    std::map<std::string, std::unordered_set<std::string>> teacher_to_students;
    ExamStatus status;

    bool distribute();

public:
    Exam(const myDate&);

    bool add_student(const std::string&);

    bool add_teacher(const std::string&);

    bool start();

    bool check_student_in_exam(const std::string&) const;

    std::vector<std::pair<size_t, size_t>> get_questions(const std::string&) const;

    bool save_mark(const std::string&, size_t);

    bool student_end_exam(const std::string&);

    const std::unordered_set<std::string>& teacher_watch_examinees(const std::string&) const;

    bool end_exam();

    std::pair<bool, const std::string&> save_solution(const std::string&, const std::string&);

    bool rate_student(const std::string&, const std::string&, size_t);

    std::string check_solution(const std::string&, const std::string&);
};

