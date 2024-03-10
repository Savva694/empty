#include <iostream>
#include <map>

class StudentInfo {
    struct Student {
        std::string login;
        std::string password;
        std::string name;
        std::string patronymic;
        std::string surname;
        size_t course;
        std::string group;

    public:
        Student(const Student&);
        Student(const std::string&, const std::string&);
        void add_info(const std::string&, const std::string&,
                 const std::string&, size_t, const std::string&);
    };
    std::map<std::string, Student> students;

public:
    StudentInfo() = default;
    bool add_student(const std::string&, const std::string&);
    void add_info(const std::string&, const std::string&, const std::string&, 
                    const std::string&, size_t, const std::string&);
    bool exist(const std::string&, const std::string&);
};