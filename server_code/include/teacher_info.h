#include <iostream>
#include <map>
#include <vector>

#include "date.h"

class TeacherInfo {
    struct Teacher {
    private:
        std::string login;
        std::string password;
        std::string surname;
        std::string name;
        std::string patronymic;
        std::string department;
        std::string subject;
        std::vector<std::pair<std::string, myDate>> exams;

    public:
        Teacher(const Teacher&);

        Teacher(const std::string&, const std::string&);

        void add_info(const std::string&, const std::string&, const std::string&, 
                        const std::string&, const std::string&);

        std::string get_password() const;

        std::string get_subject() const;
        
        void add_exam(const std::string&, const myDate&);

        std::vector<std::pair<std::string, myDate>> get_my_exams() const;
    };
    std::map<std::string, Teacher> teachers;

public:
    TeacherInfo() = default;

    bool add_teacher(const std::string&, const std::string&);

    void add_info(const std::string&, const std::string&, const std::string&, 
                    const std::string&, const std::string&, const std::string&);

    bool exist(const std::string&, const std::string&);

    std::string get_subject(const std::string&) const;

    void add_exam(const std::string&, const std::string&, const myDate&);
    
    std::vector<std::pair<std::string, myDate>> get_exams_for_teacher(const std::string&) const;
};
