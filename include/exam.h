#include <iostream>
#include <unordered_set>
#include <map>
#include <vector>

#include "date.h"

class Exam {
    myDate start_myDate;
    std::unordered_set<std::string> teachers_login;
    std::unordered_set<std::string> students_login;
    std::map<std::string, std::string> examiners;
    std::map<std::string, std::unordered_set<std::string>> students_for_teacher;

    bool distribute();

public:
    Exam(const myDate&);

    bool add_student(const std::string&);

    bool add_teacher(const std::string&);

    bool start();
};
