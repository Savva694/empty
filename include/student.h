#include <string>

#include "student_id.h"

class Student {
    std::string login;
    std::string password;
    StudentId id;

public:
    std::string name;
    std::string patronymic;
    std::string surname;
    size_t course;
    std::string group;

    Student(const std::string&, const std::string&); // only login and password
    void add_info(const std::string&, const std::string&, const std::string&, size_t, const std::string&);
};