#include <iostream>
#include <vector>
#include <map>

#include "exam_id.h"
#include "date.h"
#include "teacher.h"
#include "student.h"

class Exam {
    ExamId id;
    Date start_date;
    std::vector<TeacherId> teachers_id;
    std::vector<StudentId> students_id;
    std::map<StudentId, TeacherId> examiners;
    std::map<TeacherId, std::vector<StudentId>> students_for_teacher;

public:
    Exam(const date&);
    void add_teacher(TeacherId tid);
    void add_student(StudentId sid);
    void find_random_examiner() const; // find examiner for every student, send student his examiner/turn student to examiner
    std::string get_date() const;
};