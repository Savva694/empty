#include "../include/teacher.h"

Teacher::Teacher(const std::string& login, const std::string& password): 
                            login(login), password(password), id(TeacherId()) {}

void Teacher::add_info(const std::string& _name,
                    const std::string& _patronymic, 
                    const std::string& _surname,
                    const std::string& _department,
                    const std::string& _subject) {
    name = _name;
    patronymic = _patronymic;
    surname = _surname;
    department = _department;
    subject = _subject;
}