#include <vector>
#include <string>

#include "exam.h"

class Subject {
    std::vector<std::string> question3;
    std::vector<std::string> question4;
    std::vector<std::string> question5;

    std::map<ExamId, Exam> exams;

public:
    Subject() = default;
    Subject(const std::vector<std::string>&, 
            const std::vector<std::string>&, 
            const std::vector<std::string>&);
    const std::vector<std::string>& get_random_questions(int mark, int num) const; // returns num question for this mark
    void add_question(size_t mark, const std::string& question);

    void add_exam(const Date&);
    void add_student(ExamId);
    void add_teacher(ExamId);
    std::vector<Date> get_all_dates() const;
};