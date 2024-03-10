#include <iostream>
#include <type_traits>
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

std::string my_login;
sockaddr_in servAddr;
int connection;

// void communicate_recv(int connection) {
//     char msg[256];
//     while (true) {
//         int cnt = recv(connection, &msg, sizeof(msg), 0);
//         if (cnt == 0) break;
//         std::cout << msg << '\n';
//     }
// }

// void communicate_send(int connection) {
//     char msg[256];
//     while (true) {
//         std::cin.getline(msg, sizeof(msg));
//         send(connection, &msg, sizeof(msg), 0);
//     }
// }

bool connect_to_server(const size_t ip_server = 2130706433, const size_t port = 1234) {
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(ip_server);
    servAddr.sin_port = htons(port);

    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(connection, (sockaddr*)&servAddr, sizeof(servAddr)) != 0) {
        return false;
    }
    std::cout << "Connected!\n";
    return true;

    // std::thread Recv(communicate_recv, connection);
    // std::thread Send(communicate_send, connection);
    // Send.join();
    // Recv.join();
}

int send_to_server(std::string message) {
    char* msg = new char[1024];
    for (int i = 0; i < message.length(); ++i) {
        msg[i] = message[i];
    }
    return send(connection, msg, sizeof(message), 0);
    delete[] msg;
}

void recv_from_server(char* message) {
    if (!recv(connection, message, sizeof(message), 0)) {
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
        std::cout << "pick_exam subject date - записаться на экзмен exam по предмету subject\n";
        std::cout << "...\n";
        safe_cin(cin_value);
    }
}

void start_message() {
    std::cout << "Здравствуйте, вы находитесь в системе дистанционной сессии.\n";
    std::cout << "Для завершения сеанса введите !exit.\n";
    std::cout << "Для вывода всех команд введите !help.\n";
    std::cout << "Для для продолжения введите любое сообщение.\n";
    std::string continue_message;
    safe_cin(continue_message);
}

void login_in_system() {
    while (true) {
        std::cout << " Для входа введите логин: \n";
        safe_cin(my_login);

        std::string password;
        std::cout << "Теперь введите пароль: \n";
        safe_cin(password);

        send_to_server("slg " + my_login + " " + password);
        char message[1];
        recv_from_server(message);
        if (message[0] != '0') {
            break;
        }
        std::cout << "Логин или пароль некорректен.\n";
    }
    std::cout << "Вы вошли в систему!\n";
}

void registration_in_system() {
    while (true) {
        std::cout << "Придумайте логин: \n";
        safe_cin(my_login);

        send_to_server("srg " + my_login);
        char message[1];
        recv_from_server(message);
        if (message[0] != '0') {
            break;
        }
        std::cout << "Пользователь с таким логином уже зарегистрирован.\n";
    }
    std::cout << "Такой логин подходит.\n";
    std::cout << "Придумайте надёжный пароль: \n";
    std::string password;
    safe_cin(password);

    std::cout << "Вы успешно создали аккаунт!\n";
    std::cout << "Теперь заполните информацию о себе.\n";

    std::cout << "Введите ваше ФИО: \n";
    std::string surname;
    std::string first_name;
    std::string patronymic;
    safe_cin(surname);
    safe_cin(first_name);
    safe_cin(patronymic);

    std::cout << "Введите ваш курс (в формате 1, 2, 3, 4): \n";
    std::string course;
    safe_cin(course);

    std::cout << "Введите вашу группу (в формате Б00-000): \n";
    std::string group;
    safe_cin(group);

    send_to_server("sai " + my_login + " " + surname + " " + first_name + " " + patronymic + " " + course + " " + group);

    std::cout << "Вы успешно зарегистрировались!\n";
}

void login_or_registration() {
    std::cout << "Войдите в аккаунт или зарегистрируйтесь:\n";
    std::cout << "Для входа введите 1\n";
    std::cout << "Для регистрации введите 2\n";
    std::string login_or_registration;
    while (true) {
        safe_cin(login_or_registration);
        if (login_or_registration == "1") {
            login_in_system();
            break;
        } else if (login_or_registration == "2") {
            registration_in_system();
            break;
        }
        std::cout << "Вы ввели некоррекную команду.\n";
        std::cout << "Для входа введите 1\n";
        std::cout << "Для регистрации введите 2\n";
    }
}

void show_my_exams() {
    send_to_server("sme " + my_login);
    char message[1024];
    recv_from_server(message);
    std::cout << "Экзамены, на которые вы зарегистрировались: \n";
    std::cout << message << "\n";
}

void show_subjects() {
    send_to_server("sgs");
    char message[1024];
    recv_from_server(message);
    std::cout << "Все предметы: \n";
    std::cout << message << "\n";
}

void show_exams() {
    std::cout << "Введите предмет, информацию об экзаменах по которому вы хотите узнать: \n";
    std::string subject;
    safe_cin(subject);
    send_to_server("sge " + subject);
    char message[1024];
    recv_from_server(message);
    if (message != "0") {
        std::cout << "Доступные экзамены по предмету " + subject + "\n";
        std::cout << message << "\n";
        return;
    }
    std::cout << "Произошла ошибка, скорее всего предмета " + subject + " не существует\n";\
}

void pick_exam() {
    std::cout << "Введите предмет, на экзамен по которому вы хотите зарегистрироваться: \n";
    std::string subject;
    safe_cin(subject);

    std::cout << "Введите время этого экзамена: \n";
    std::string date;
    safe_cin(date);

    send_to_server("sre " + subject + " " + date);
    char message[1];
    recv_from_server(message);
    if (message == "1") {
        std::cout << "Вы успешно зарегистрировались на экзамен по предмету " + subject + ". Он пройдёт в " + date + ".\n";
        return;
    }
    std::cout << "Произошла ошибка, скорее всего предмет или время проведения экзамена укзаны неверно.\n";
}

int main() {
    if (!connect_to_server()) {
        exit(0);
    }
    send_to_server("st");

    start_message();
    login_or_registration();

    std::cout << "Чтобы вывести список команд напишите !help\n";
    std::string command;
    safe_cin(command);
    while (true) {
        if (command == "show_my_exams") {
            show_my_exams();
        } else if (command == "show_subjects") {
            show_subjects();
        } else if (command == "show_exams") {
            show_exams();
        } else if (command == "pick_exam") {
            pick_exam();
        }


        safe_cin(command);
    }
}