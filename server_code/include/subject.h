#include <vector>
#include <string>

#include "exam.h"

class Subject {
    std::vector<std::string> questions[3];

    std::map<myDate, Exam> exams;

public:
    Subject();

    std::vector<myDate> get_exams() const;

    bool add_student(const std::string&, const myDate&);

    bool add_teacher(const std::string&, const myDate&);

    bool add_exam(const myDate&);

    bool add_question(size_t, const std::string&);

    bool start_exam(const myDate&);

    const std::unordered_set<std::string>& teacher_watch_examinees(const myDate&, const std::string&) const;

    bool end_exam(const myDate&);

    bool end_exam(const myDate&);

    // bool check_student_in_exam(const myDate&, const std::string&) const;

    bool check_student_in_exam(const myDate&, const std::string&) const;


    std::string get_questions(const myDate&, const std::string&) const;

    bool save_mark(const myDate&, const std::string&, size_t);

    bool student_end_exam(const myDate&, const std::string&);

    std::pair<bool, const std::string&> save_solution(const myDate&, const std::string&, const std::string&);

    bool rate_student(const myDate&, const std::string&, const std::string&, size_t);

    std::string check_solution(const myDate&, const std::string&, const std::string&);
};
