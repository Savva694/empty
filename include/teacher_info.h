#include <iostream>
#include <map>

class TeacherInfo {
    struct Teacher {
        std::string login;
        std::string password;
        std::string surname;
        std::string name;
        std::string patronymic;
        std::string department;
        std::string subject;

        Teacher(const Teacher&);
        Teacher(const std::string&, const std::string&);
        void add_info(const std::string&, const std::string&, const std::string&, 
                        const std::string&, const std::string&);
    };
    std::map<std::string, Teacher> teachers;

public:
    TeacherInfo() = default;
    bool add_teacher(const std::string&, const std::string&);
    void add_info(const std::string&, const std::string&, const std::string&, 
                    const std::string&, const std::string&, const std::string&);
    bool exist(const std::string&, const std::string&);
    std::string TeacherInfo::get_subject(const std::string&) const;
};
