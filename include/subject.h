#include <vector>
#include <string>

#include "exam.h"

class Subject {
    std::vector<std::string> question3;
    std::vector<std::string> question4;
    std::vector<std::string> question5;

    std::map<myDate, Exam> exams;

public:
    Subject();

    std::vector<myDate> get_exams() const;

    bool add_student(const std::string&, const myDate&);

    bool add_exam(const myDate&);

    // Subject(const std::vector<std::string>&, 
    //         const std::vector<std::string>&, 
    //         const std::vector<std::string>&);
    // const std::vector<std::string>& get_random_questions(int mark, int num) const; // returns num question for this mark
    // void add_question(size_t mark, const std::string& question);

    // void add_exam(const myDate&);
    // void add_teacher(ExamId);
    // std::vector<myDate> get_all_myDates() const;
};
