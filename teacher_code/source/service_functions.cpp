#include <iostream>
#include <netinet/in.h>
#include <string.h>

sockaddr_in servAddr;
int connection;

bool connect_to_server(const size_t ip_server, const size_t port) {
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(ip_server);
    servAddr.sin_port = htons(port);

    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(connection, (sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
        return false;
    }
    std::cout << "Connected!\n";
    return true;
}

int send_to_server(std::string message) {
    char* msg = new char[message.size() + 1];
    for (int i = 0; i < message.size(); ++i) {
        msg[i] = message[i];
    }
    msg[message.size()] = '\0';
    return send(connection, msg, message.size() + 1, 0);
    delete[] msg;
}

void recv_from_server(char* message, size_t sz) {
    if (!recv(connection, message, sz, 0)) {
        std::cout << "Потеряно соединение с сервером.\n";
        exit(0);
    }
}

template <typename T>
void safe_cin(T& cin_value) {
    std::cin >> cin_value;
    if (cin_value == "!exit") {
        std::cout << "Вы завершилы выполнение программы.\n";
        exit(0);
    } else if (cin_value == "!help") {
        std::cout << "Список доступных команд:\n";
        std::cout << "!exit - завершение сеанса\n";
        std::cout << "!help - вывод доступных команд\n";
        std::cout << "show_my_exams - выводит список экзаменов, на которые вы зарегистрировались\n";
        std::cout << "show_subjects - выводит список всех предметов\n";
        std::cout << "show_exams subject - выводит список экзаменов по предмету subject\n";
        std::cout << "pick_exam subject time - записаться на экзмен по предмету subject, проходящий во время time\n";
        std::cout << "start_exam subject time - начать сдачу экзамена по предмету subject в time\n";
        std::cout << "set_grade grade - во время сдачи экзамена указать желаемую оценку grade\n";
        std::cout << "write_solution  solution- во время сдачи экзамена отослать решение solution\n";
        std::cout << "leave_exam - покинуть экзамен\n";
        std::cout << "my_grades - выводит список полченных оценок\n";
        safe_cin(cin_value);
    }
}

int ip_to_int(char* str) {
    int ip = 0, m = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            m = m * 10 + str[i] - '0';
        } else {
            ip = ip * 256 + m;
            m = 0;
        }
    }
    ip = ip * 256 + m;
    return ip;
}
