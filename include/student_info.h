#include <map>

#include "StudentId"
#include "Student"

class StudentInfo {
    std::map<StudentId, Student> students;

public
    StudentInfo() = default;
    void new_student(const Student& student);
};