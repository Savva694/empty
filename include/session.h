#include <string>
#include <unordered_map>

#include "subject.h"

class Session {
    std::unordered_map<std::string, Subject> subjects;

public:
    Session();

    std::string get_subjects() const;

    std::vector<myDate> get_exams(std::string subj) const;

    bool add_student(const std::string&, const std::string&, const myDate&);

    bool add_teacher(const std::string&, const std::string&, const myDate&);

    bool add_subject(const std::string&);

    bool add_exam(const std::string&, const myDate&);

    bool add_question(const std::string&, size_t, const std::string&);

    bool start_exam(const std::string&, const myDate&);

    // bool check_student_in_exam(const std::string&, const myDate&, const std::string&) const;

    // std::string Session::get_questions(const std::string&, const myDate&, const std::string&, size_t);
};
