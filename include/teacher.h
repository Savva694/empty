#include <string>

#include "teacherid.h"

class Teacher {
    std::string login;
    std::string password;
    TeacherId id;

public
    std::string name;
    std::string patronymic;
    std::string surname;
    std::string department;
    std::string subject;
    Teacher (const std::string&, const std::string&); // only login and password
    void add_info(const std::string&, const std::string&, const std::string&,
                     const std::string&, const std::string&);
};