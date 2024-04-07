#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <vector>
#include "../include/session.h"
#include "../include/student_info.h"
#include "../include/teacher_info.h"

struct Server {
    Session session;
    StudentInfo student_info;
    TeacherInfo teacher_info;
    int sListen;
    sockaddr_in server_address;
    std::vector<int> connections;

    void find_clients();


    void teacher_login(const std::vector<std::string>&, size_t);

    void teacher_register(const std::vector<std::string>&, size_t);

    void teacher_add_info(const std::vector<std::string>&, size_t);

    void add_subject(const std::vector<std::string>&, size_t);

    std::string get_subject(const std::string&) const;

    void add_exam(const std::vector<std::string>&, size_t);

    void teacher_register_to_exam(const std::vector<std::string>&, size_t);

    void get_exams_for_teacher(const std::vector<std::string>&, size_t) const;

    void add_question(const std::vector<std::string>&, size_t);

    void teacher_start_exam(const std::vector<std::string>&, size_t);

    void rate_student(const std::vector<std::string>&, size_t);

    void check_solution(const std::vector<std::string>&, size_t);


    void student_login(const std::vector<std::string>&, size_t);

    void student_register(const std::vector<std::string>&, size_t);

    void student_add_info(const std::vector<std::string>&, size_t);

    void get_subjects(size_t);

    void get_exams(const std::vector<std::string>&, size_t) const;

    void student_register_to_exam(const std::vector<std::string>&, size_t);

    void get_exams_for_student(const std::vector<std::string>&, size_t) const;

    void get_marks_for_student(const std::vector<std::string>&, size_t) const;

    void student_start_exam(const std::vector<std::string>&, size_t) const;

    void get_questions(const std::vector<std::string>&, size_t) const;

    void save_mark(const std::vector<std::string>&, size_t);

    void student_end_exam(const std::vector<std::string>&, size_t);

    void save_solution(const std::vector<std::string>&, size_t);


    void communicate (int index);

public:
    Server(int port);
};
