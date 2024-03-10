#include "../include/server.h"

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

        char msg[256];
        int cnt = recv(newConnection, &msg, sizeof(msg), 0);
        if (cnt == 0) {

        }
        int id = 0;
        int j = 2;
        // while (msg[j] < '0' || msg[j] > '9') ++j;
        while (msg[j] >= '0' && msg[j] <= '9') {
            id = id * 10 + msg[j] - '0';
            ++j;
        }
        if (msg[0] == 'T') {
            teachers.push_back({newConnection, id});
            std::thread Read(&Server::comm_teacher, std::ref(*this), static_cast<int>(teachers.size()) - 1);
            Read.detach();
        } else {
            students.push_back({newConnection, id});
            std::thread Read(&Server::comm_student, std::ref(*this), static_cast<int>(students.size()) - 1);
            Read.detach();
        }
    }
}

void Server::comm_teacher(int index) {
    // std::cout << "comm_teacher\n";
    char msg[256];
    while (true) {
        int cnt = recv(teachers[index].first, &msg, sizeof(msg), 0);
        if (cnt == 0) break;
        std::cout << msg << '\n';

        if (msg == "make exam") {

        } else if (msg == "add teacher") {

        } else if (msg == "start exam") {

        } else if (msg == "send questions") {

        } else if (msg == "send my question") {

        }
        // make answer in msg
        // cin.getline(msg, sizeof(msg));
        // send(teachers[index].first, &msg, sizeof(msg), 0);
    }
}

void Server::comm_student (int index) {
    // std::cout << "comm_student\n";
    char msg[256];
    while (true) {
        int cnt = recv(students[index].first, &msg, sizeof(msg), 0);
        if (cnt == 0) break;
        std::cout << msg << '\n';

        if (msg == "take all exams") {

        } else if (msg == "register") {

        } else if (msg == "take subjects") {

        } else if (msg == "send answer") {

        }
        // make answer in msg
        // cin.getline(msg, sizeof(msg));
        // send(students[index].first, &msg, sizeof(msg), 0);
    }
}