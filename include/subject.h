#include <vector>
#include <string>

#include "exam.h"

class Subject {
    std::vector<std::string> questions[3];

    std::map<myDate, Exam> exams;

public:
    Subject();

    std::vector<myDate> get_exams() const;

    bool add_student(const std::string&, const myDate&);

    bool add_teacher(const std::string&, const myDate&);

    bool add_exam(const myDate&);

    bool add_question(size_t, const std::string&);

    bool start_exam(const myDate&);

    // Subject(const std::vector<std::string>&, 
    //         const std::vector<std::string>&, 
    //         const std::vector<std::string>&);
    // const std::vector<std::string>& get_random_questions(int mark, int num) const; // returns num question for this mark
};
