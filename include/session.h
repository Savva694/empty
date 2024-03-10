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

    // void add_subject(const std::string& name); // make new subject with this name
    // void add_teacher(std::string, ExamId);
    // void add_exam(std::string);
};