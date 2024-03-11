#include <iostream>
#include <unordered_set>
#include <map>

#include "date.h"

class Exam {
    myDate start_myDate;
    std::unordered_set<std::string> teachers_login;
    std::unordered_set<std::string> students_login;
    std::map<std::string, std::string> examiners;

public:
    Exam(const myDate&);
    bool add_student(const std::string&);


    // void add_teacher(TeacherId tid);
    // void find_random_examiner() const; // find examiner for every student, send student his examiner/turn student to examiner
    // std::string get_myDate() const;
};
