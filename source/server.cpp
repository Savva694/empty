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
    char* msg = "0";
    size_t len = 1;
    std::string subject = get_subject(str[1]);
    bool is_added = session.add_subject(subject);
    if (is_added) {
        msg = to_cstring(subject);
        len = subject.size();
    }
    send(connections[index], &msg, len, 0);
    if (is_added) delete[] msg;
}

void Server::add_exam(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.add_exam(get_subject(str[1]), myDate(str[2]))) + '0';
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
    send(connections[index], msg, sub.size(), 0);
    delete[] msg;
}

void Server::get_exams(const std::vector<std::string>& str, size_t index) {
    std::vector<myDate> dates = session.get_exams(str[1]);
    std::string str_date;
    for (auto date : dates) {
        str_date += date.to_string();
        str_date += ' ';
    }
    char* message = to_cstring(str_date);
    send(connections[index], message, str_date.size(), 0);
    delete[] message;
}

void Server::student_register_to_exam(const std::vector<std::string>& str, size_t index) {
    char msg = static_cast<char>(session.add_student(str[1], str[2], myDate(str[3]))) + '0';
    if (msg == '1') student_info.add_exam(str[1], str[2], myDate(str[3]));
    send(connections[index], &msg, 1, 0);
}

void Server::get_exams_for_student(const std::vector<std::string>& str, size_t index) {
    std::vector<std::pair<std::string, myDate>> exams = student_info.get_exams_for_student(str[1]);
    std::string str_exams;
    for (auto exam : exams) {
        str_exams += exam.first;
        str_exams += ' ';
        str_exams += exam.second.to_string();
        str_exams += ' ';
    }
    char* message = to_cstring(str_exams);
    send(connections[index], message, str_exams.size(), 0);
    delete[] message;
}

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
        }
    }
}

int main() {
    Server server;
}