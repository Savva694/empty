#include <vector>
#include <string>

#include "exam.h"

class Subject {
    std::vector<std::string> question3;
    std::vector<std::string> question4;
    std::vector<std::string> question5;

    std::vector<Exam> exams;

public:
    Subject() = default;
    Subject(const std::vector<std::string>&, 
            const std::vector<std::string>&, 
            const std::vector<std::string>&);
    const std::vector<std::string>& get_random_questions(int mark, int num); // returns num question for this mark
    void add_question(size_t mark, const std::string& question);

    void add_exam(size_t, size_t, size_t, size_t, size_t);
    void add_student(size_t exam_num);
    void add_teacher(size_t exam_num);
    std::vector<std::string> get_all_dates();
};