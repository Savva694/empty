#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <vector>
#include "../include/session.h"
#include "../include/student_info.h"
// #include "../include/teacher_info.h"

struct Server {
    Session session;
    StudentInfo student_info;
    // TeacherInfo teacher_info;
    int sListen;
    sockaddr_in server_address;
    std::vector<int> connections;

public:
    Server(int port = 32245);

    void find_clients();

    void student_login(const std::vector<std::string>&, size_t);

    void student_register(const std::vector<std::string>&, size_t);

    void student_add_info(const std::vector<std::string>&, size_t);

    void get_subjects(size_t);

    void get_exams(const std::vector<std::string>&, size_t);

    void student_register_to_exam(const std::vector<std::string>&, size_t);

    void communicate (int index);
};
