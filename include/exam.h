#include <iostream>
#include <vector>

#include "teacher.h"
#include "student.h"
#include "teacherid.h"
#include "studentid.h"

class Exam {
    struct Date {
        size_t year;
        size_t month;
        size_t day;
        size_t hour;
        size_t min;

        // Date() : year(0), month(0), day(0), hour(0), min(0) {}
        Date(size_t year, size_t month, size_t day, size_t hour, size_t min) :
                year(year), month(month), day(day), hour(hour), min(min) {}
    };

    Date start_date;
    std::vector<TeacherId> teachers_id;
    std::vector<StudentId> students_id;
    std::map<StudentId, TeacherId> examiners;

public:
    Exam(size_t, size_t, size_t, size_t, size_t);
    void add_teacher(TeacherId tid);
    void add_student(StudentId sid);
    void find_random_examiner(); // find examiner for every student, send student his examiner/turn student to examiner
    std::string get_date();
};