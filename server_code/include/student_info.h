#include <iostream>
#include <map>
#include <vector>

#include "date.h"

class StudentInfo {
    struct Student {
    private:
        std::string login;
        std::string password;
        std::string name;
        std::string patronymic;
        std::string surname;
        size_t course;
        std::string group;
        std::vector<std::pair<std::string, myDate>> exams;
        std::map<std::string, size_t> marks;

    public:
        Student(const Student&);

        Student(const std::string&, const std::string&);

        void add_info(const std::string&, const std::string&,
                 const std::string&, size_t, const std::string&);

        std::string get_password() const;

        void add_exam(const std::string&, const myDate&);

        std::vector<std::pair<std::string, myDate>> get_my_exams() const;

        std::vector<std::pair<std::string, size_t>> get_marks() const;
    };
    std::map<std::string, Student> students;

public:
    StudentInfo() = default;

    bool add_student(const std::string&, const std::string&);

    void add_info(const std::string&, const std::string&, const std::string&, 
                    const std::string&, size_t, const std::string&);

    bool exist(const std::string&, const std::string&);

    void add_exam(const std::string&, const std::string&, const myDate&);
    
    std::vector<std::pair<std::string, myDate>> get_exams_for_student(const std::string&) const;

    std::vector<std::pair<std::string, size_t>> get_marks(const std::string&) const;
};
