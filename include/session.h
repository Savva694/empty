#include <string>
#include <map>

#include "subject.h"

class Session {
    std::unordered_map<std::string, Subject> subjects;

public
    Session() = default;
    void add_subject(const std::string& name); // make new subject with this name
    void add_teacher()
    void add_student();
    void add_exam();
    std::vector<std::pair<std::string, std::vector<std::string> > > get_all_exams(); // return name of subject and vector of dates fo this subject
}