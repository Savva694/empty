#include "../include/server.h"
#include <string.h>

std::string to_string(const char* str) {
    std::string ans = "";
    for (int i = 0; i < strlen(str); ++i) {
        ans += str[i];
    }
    return ans;
}

char* to_cstring(const std::string& str) {
    char* ans = new char[str.size() + 1];
    for (size_t i = 0; i < str.size(); ++i) {
        ans[i] = str[i];
    }
    ans[str.size()] = '\0';
    return ans;
}

std::vector<std::string> split_space(char* str) {
    std::vector<std::string> ans;
    std::string word = "";
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == ' ' && word != "") {
            ans.push_back(word);
            word = "";
        } else {
            word += str[i];
        }
    }
    if (word != "") ans.push_back(word);
    return ans;
}




Server::Server(int port) {
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    sListen = socket(AF_INET, SOCK_STREAM, 0);
    bind(sListen, (sockaddr*)&server_address, sizeof(server_address));
    listen(sListen, 10000);

    std::cerr << "start\n";
    std::thread Find(&Server::find_clients, std::ref(*this));
    Find.join();
}

void Server::find_clients() {
    socklen_t sz = sizeof(server_address);

    while(true) {
        int newConnection = accept(sListen, (sockaddr*)&server_address, &sz);

        if (newConnection == 0) {
            std::cerr << "Error of connection\n";
            continue;
        }
        std::cout << "Client connected\n";

        connections.push_back(newConnection);
        std::thread Read(&Server::communicate, std::ref(*this), static_cast<int>(connections.size()) - 1);
        Read.detach();
    }
}



void Server::teacher_login(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(teacher_info.exist(str[1], str[2])) + '0';
    send(connections[index], &msg, 1, 0);
}

void Server::teacher_register(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(teacher_info.add_teacher(str[1], str[2])) + '0';
    send(connections[index], &msg, 1, 0);
}

void Server::teacher_add_info(const std::vector<std::string>& str, size_t index) {
    teacher_info.add_info(str[1], str[2], str[3], str[4], str[5], str[6]);
}

std::string Server::get_subject(const std::string& login) const {
    return teacher_info.get_subject(login);
}

void Server::add_subject(const std::vector<std::string>& str, size_t index) {
    std::string subject = get_subject(str[1]);
    if (session.add_subject(subject)) {
        char* msg = to_cstring(subject);
        send(connections[index], msg, subject.size() + 1, 0);
        delete[] msg;
    } else {
        char msg = '0';
        send(connections[index], &msg, 1, 0);
    }
}

void Server::add_exam(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.add_exam(get_subject(str[1]), myDate(str[2]))) + '0';
    send(connections[index], &msg, 1, 0);
}

void Server::teacher_register_to_exam(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.add_teacher(str[1], str[2], myDate(str[3]))) + '0';
    if (msg == '1') teacher_info.add_exam(str[1], str[2], myDate(str[3]));
    send(connections[index], &msg, 1, 0);
}

void Server::get_exams_for_teacher(const std::vector<std::string>& str, size_t index) const {
    std::vector<std::pair<std::string, myDate>> exams = teacher_info.get_exams_for_teacher(str[1]);
    std::string str_exams;
    for (auto exam : exams) {
        str_exams += exam.first;
        str_exams += ' ';
        str_exams += exam.second.to_string();
        str_exams += ' ';
    }
    char* message = to_cstring(str_exams);
    send(connections[index], message, str_exams.size() + 1, 0);
    delete[] message;
}

void Server::add_question(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.add_question(get_subject(str[1]), stoi(str[2]), str[3])) + '0';
    send(connections[index], &msg, 1, 0);
}

void Server::teacher_start_exam(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.start_exam(str[2], myDate(str[3]))) + '0';
    send(connections[index], &msg, 1, 0);
}




void Server::student_login(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(student_info.exist(str[1], str[2])) + '0';
    send(connections[index], &msg, 1, 0);
}

void Server::student_register(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(student_info.add_student(str[1], str[2])) + '0';
    send(connections[index], &msg, 1, 0);
}

void Server::student_add_info(const std::vector<std::string>& str, size_t index) {
    student_info.add_info(str[1], str[2], str[3], str[4], stoi(str[5]), str[6]);
}

void Server::get_subjects(size_t index) {
    std::string sub = session.get_subjects();
    char* msg = to_cstring(sub);
    send(connections[index], msg, sub.size() + 1, 0);
    delete[] msg;
}

void Server::get_exams(const std::vector<std::string>& str, size_t index) const {
    std::vector<myDate> dates = session.get_exams(str[1]);
    std::string str_date;
    for (auto date : dates) {
        str_date += date.to_string();
        str_date += ' ';
    }
    char* message = to_cstring(str_date);
    send(connections[index], message, str_date.size() + 1, 0);
    delete[] message;
}

void Server::student_register_to_exam(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.add_student(str[1], str[2], myDate(str[3]))) + '0';
    if (msg == '1') student_info.add_exam(str[1], str[2], myDate(str[3]));
    send(connections[index], &msg, 1, 0);
}

void Server::get_exams_for_student(const std::vector<std::string>& str, size_t index) const {
    std::vector<std::pair<std::string, myDate>> exams = student_info.get_exams_for_student(str[1]);
    std::string str_exams;
    for (auto exam : exams) {
        str_exams += exam.first;
        str_exams += ' ';
        str_exams += exam.second.to_string();
        str_exams += ' ';
    }
    char* message = to_cstring(str_exams);
    send(connections[index], message, str_exams.size() + 1, 0);
    delete[] message;
}

void Server::get_marks_for_student(const std::vector<std::string>& str, size_t index) const {
    std::vector<std::pair<std::string, size_t>> marks = student_info.get_marks(str[1]);
    std::string str_marks;
    for (auto mark : marks) {
        str_marks += mark.first;
        str_marks += ' ';
        str_marks += std::to_string(mark.second);
        str_marks += ' ';
    }
    char* message = to_cstring(str_marks);
    send(connections[index], message, str_marks.size() + 1, 0);
    delete[] message;
}

// void Server::student_start_exam(const std::vector<std::string>& str, size_t index) const {
//     char msg = static_cast<char>(session.check_student_in_exam(str[2], myDate(str[3]), str[1])) + '0';
//     send(connections[index], &msg, 1, 0);
// }

// void Server::get_questions(const std::vector<std::string>& str, size_t index) {
//     std::string questions = session.get_questions(str[2], myDate(str[3]), str[1], stoi(str[4]));
//     char * msg = to_cstring(questions)
// }

void Server::communicate (int index) {
    char msg[1024];
    std::vector<std::string> str;
    while (true) {
        int cnt = recv(connections[index], &msg, sizeof(msg), 0);
        if (cnt == 0) break;
        std::cout << msg << '\n';
        str = split_space(msg);

        if (str[0] == "slg") {
            student_login(str, index);
        } else if (str[0] == "srg") {
            student_register(str, index);
        } else if (str[0] == "sai") {
            student_add_info(str, index);
        } else if (str[0] == "sgs") {
            get_subjects(index);
        } else if (str[0] == "sge") {
            get_exams(str, index);
        } else if (str[0] == "sre") {
            student_register_to_exam(str, index);
        } else if (str[0] == "sme") {
            get_exams_for_student(str, index);
        } else if (str[0] == "ssr") {
            get_marks_for_student(str, index);
        // } else if (str[0] == "sse") {
        //     student_start_exam(str, index);
        // } else if (str[0] == "ssp") {
        //     get_questions(str, index);
        } else if (str[0] == "tlg") {
            teacher_login(str, index);
        } else if (str[0] == "trg") {
            teacher_register(str, index);
        } else if (str[0] == "tai") {
            teacher_add_info(str, index);
        } else if (str[0] == "tas") {
            add_subject(str, index);
        } else if (str[0] == "tae") {
            add_exam(str, index);
        } else if (str[0] == "tre") {
            teacher_register_to_exam(str, index);
        } else if (str[0] == "tme") {
            get_exams_for_teacher(str, index);
        } else if (str[0] == "tap") {
            add_question(str, index);
        } else if (str[0] == "tse") {
            teacher_start_exam(str, index);
        }
    }
}
