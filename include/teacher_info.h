#include <map>

#include "teacherid.h"
#include "teacher.h"

class TeacherInfo {
    std::map<TeacherId, Teacher> teachers;

public
    TeacherInfo() = default;
    void new_teacher(const Teacher& teacher);
};