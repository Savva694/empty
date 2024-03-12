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
int session_stage = 0;
std::string exam = "";

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

bool connect_to_server(const size_t ip_server = 3232235627, const size_t port = 32245) {
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
        std::cout << "show_subjects - выводит список всех предметов\n";
        std::cout << "show_exams subject - выводит список экзаменов по предмету subject\n";
        std::cout << "add_subject - добавляет ваш предмет в общий список предметов\n";
        std::cout << "add_exam date - добавляет экзамен по вашему предмету на время date\n";
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

        send_to_server("tlg " + my_login + " " + password);
        char message[1];
        recv_from_server(message, 1);
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

        send_to_server("trg " + my_login);
        char message[1];
        recv_from_server(message, 1);
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

    std::cout << "Введите вау кафедру: \n";
    std::string department;
    safe_cin(department);

    std::cout << "Введите ваш предмет: \n";
    std::string subject;
    safe_cin(subject);

    send_to_server("tai " + my_login + " " + surname + " " + first_name + " " + patronymic + " " + department + " " + subject);
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

void show_subjects() {
    send_to_server("sgs");
    char message[1024];
    recv_from_server(message, 1024);
    std::cout << "Все предметы: \n";
    std::cout << message << "\n";
}

void show_exams() {
    std::cout << "Введите предмет, информацию об экзаменах по которому вы хотите узнать: \n";
    std::string subject;
    safe_cin(subject);
    send_to_server("sge " + subject);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Доступные экзамены по предмету " + subject + "\n";
        std::cout << message << "\n";
        return;
    }
    std::cout << "Произошла ошибка, скорее всего предмета " + subject + " не существует\n";\
}

void add_subject() {
    send_to_server("tas " + my_login);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Ваш предмет ";
        std::cout << message;
        std::cout << " успешно добавлен\n";
        return;
    }
    std::cout << "Произошла ошибка, скорее всего ваш предмет уже кто-то добавил\n";\
}

void add_exam() {
    std::cout << "Введите время новго экзамена: \n";
    std::string date;
    safe_cin(date);
    send_to_server("tae " + my_login + " " + date);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Новый экзамен по вашему предмету на время " + date + " успешно добавлен.\n";
        return;
    }
    std::cout << "Произошла ошибка, скорее всего экзамен на это время уже кто-то добавил\n";\
}

void add_problem() {
    std::cout << "Введите условие новой задачи: \n";
    std::string problem;
    safe_cin(problem);

    std::cout << "На какую оценку эта задача? (3, 4, 5) \n";
    std::string rate;
    while (true) {
        safe_cin(rate);
        if (rate == "3" || rate == "4" || rate == "5") {
            break;
        }
        std::cout << "Неправильный формат. Введите оценку за задачу в формате: 3, 4, 5 \n";
    }

    send_to_server("tap " + my_login + " " + rate + " " + problem);
    char message[1];
    recv_from_server(message, 1);
    if (message == "1") {
        std::cout << "Новая задача на оценку " + rate + " успешно добавлена.\n";
        return;
    }
    std::cout << "Произошла ошибка.\n";\
}

void start_exam() {
    std::cout << "Введите предмет, экзамен по которому хотите начать: \n";
    std::string subject;
    safe_cin(subject);

    std::cout << "Введите время этого экзамена: \n";
    std::string date;
    safe_cin(date);

    send_to_server("tse " + my_login + " " + subject + " " + date);
    char message[1];
    recv_from_server(message, 1);
    if (message == "1") {
        session_stage = 1;
        exam = subject + " " + date;
        std::cout << "Экзамен начался! \n";
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}

void show_students() {
    send_to_server("twe " + my_login + " " + exam);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Вы принимаете экзамен у следующих людей: \n";
        std::cout << message << "\n";
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}

void show_solution() {
    std::cout << "Введите логин ученика: \n";
    std::string student_login;
    safe_cin(student_login);

    send_to_server("tws " + my_login + " " + exam + " " + student_login);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Решение: \n";
        std::cout << message << "\n";
        session_stage = 2;
        return;
    }
    std::cout << "Решения пока нет. \n";\
}

void rate_solution() {
    std::cout << "Введите логин ученика: \n";
    std::string student_login;
    safe_cin(student_login);

    std::cout << "Введите оценку: \n";
    std::string rate;
    while (true) {
        safe_cin(rate);
        if (rate == "1" || rate == "2" || rate == "3" || rate == "4" || rate == "5" || rate == "6" || rate == "7"
         || rate == "8" || rate == "9" || rate == "10") {
            break;
        }
        std::cout << "Неправильный формат. Введите оценку за задачу в формате: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 \n";
    }

    send_to_server("trs " + my_login + " " + exam + " " + student_login + " " + rate);
    char message[1];
    recv_from_server(message, 1024);
    if (message == "1") {
        std::cout << "Оценка выставлена. \n";
        session_stage = 1;
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}

void reg_for_exam() {
    std::cout << "Введите предмет, на экзамен по которму хотите зарегистрироваться: \n";
    std::string subject;
    safe_cin(subject);

    std::cout << "Введите время этого экзамена: \n";
    std::string date;
    safe_cin(date);

    send_to_server("tre " + my_login + " " + subject + " " + date);
    char message[1];
    recv_from_server(message, 1);
    if (message == "1") {
        std::cout << "Вы успешно зарегистрировались на экзамен. \n";
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}

void show_my_exams() {
    send_to_server("tme " + my_login);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Экзамены, на которые вы зарегистрировались: \n";
        std::cout << message << "\n";
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}

void end_exam() {
    send_to_server("tee " + my_login + " " + exam);
    char message[1];
    recv_from_server(message, 1);
    if (message == "1") {
        std::cout << "Экзамен завершён. \n";
        session_stage = 0;
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}

int main() {
    if (!connect_to_server()) {
        exit(0);
    }

    start_message();
    login_or_registration();

    std::cout << "Чтобы вывести список команд напишите !help\n";
    std::string command;
    safe_cin(command);
    while (true) {
        if (command == "show_subjects") {
            show_subjects();
        } else if (command == "show_exams") {
            show_exams();
        } else if (command == "add_subject") {
            add_subject();
        } else if (command == "add_exam") {
            add_exam();
        } else if (command == "add_problem") {
            add_problem();
        } else if (command == "start_exam") {
            start_exam();
        } else if (command == "show_students" && session_stage == 1) {
            show_students();
        } else if (command == "show_solution" && session_stage == 1) {
            show_solution();
        } else if (command == "rate_solution" && session_stage == 2) {
            rate_solution();
        } else if (command == "reg_for_exam") {
            reg_for_exam();
        } else if (command == "show_my_exams") {
            show_my_exams();
        } else if (command == "end_exam" && session_stage == 1) {
            end_exam();
        }

        safe_cin(command);
    }
}