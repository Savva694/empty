#include <iostream>
#include <netinet/in.h>
#include <string.h>

std::string my_login;
sockaddr_in servAddr;
int connection;
int session_stage = 0;
std::string exam = "";

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
        std::cout << "Для входа введите логин: \n";
        safe_cin(my_login);

        std::string password;
        std::cout << "Теперь введите пароль: \n";
        safe_cin(password);

        send_to_server("slg " + my_login + " " + password);
        char message;
        recv_from_server(&message, 1);
        if (message != '0') {
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

        std::cout << "Придумайте надёжный пароль: \n";
        std::string password;
        safe_cin(password);

        send_to_server("srg " + my_login + " " + password);
        char message;
        recv_from_server(&message, 1);
        if (message != '0') {
            break;
        }
        std::cout << "Пользователь с таким логином уже зарегистрирован.\n";
    }
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
    while (true) {
        safe_cin(course);
        if (course == "1" || course == "2" || course == "3" || course == "4") {
            break;
        }
        std::cout << "Неправильный формат ввода, попробуйте ещё раз. \n";
    }

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
    recv_from_server(message, 1024);
    std::cout << "Экзамены, на которые вы зарегистрировались: \n";
    std::cout << message << "\n";
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

void pick_exam() {
    std::cout << "Введите предмет, на экзамен по которому вы хотите зарегистрироваться: \n";
    std::string subject;
    safe_cin(subject);

    std::cout << "Введите время этого экзамена: \n";
    std::string date;
    safe_cin(date);

    send_to_server("sre " + my_login + " " + subject + " " + date);
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
        std::cout << "Вы успешно зарегистрировались на экзамен по предмету " + subject + ". Он пройдёт в " + date + ".\n";
        return;
    }
    std::cout << "Произошла ошибка, скорее всего предмет или время проведения экзамена укзаны неверно.\n";
}

void start_exam() {
    std::cout << "Введите предмет, экзамен по которому хотите начать: \n";
    std::string subject;
    safe_cin(subject);

    std::cout << "Введите время этого экзамена: \n";
    std::string date;
    safe_cin(date);

    send_to_server("sse " + my_login + " " + subject + " " + date);
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
        std::cout << "Вы успешно начали экзамен.\n";
        session_stage = 1;
        exam = subject + " " + date;
        return;
    }
    std::cout << "Произошла ошибка.\n";
}

void set_grade() {
    std::cout << "Введите желаемую оценку за экзамен: \n";
    std::string grade;
    while (true) {
        safe_cin(grade);
        if (grade == "3" || grade == "4" || grade == "5") {
            break;
        }
        std::cout << "Введенная оценка не соответствует формату 3, 4, 5. Попробуйте еще раз.\n";
    }

    send_to_server("ser " + my_login + " " + exam + " " + grade);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Ваша задача: \n";
        std::cout << message << "\n";
        session_stage = 2;
        return;
    }
    std::cout << "Произошла ошибка.\n";
}

void show_problem() {
    send_to_server("ssp " + my_login + " " + exam);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Ваша задача: \n";
        std::cout << message << "\n";
        return;
    }
    std::cout << "Произошла ошибка.\n";
}

void write_solution() {
    std::cout << "Напишите решение: \n";
    std::string solution;
    safe_cin(solution);

    send_to_server("sap " + my_login + " " + exam + " " + solution);
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
        std::cout << "Ваше решение принято на проверку, вы можете покидать экзамен. \n";
        session_stage = 3;
        return;
    }
    std::cout << "Произошла ошибка.\n";
}

void leave_exam() {
    send_to_server("see " + my_login + " " + exam);
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
        std::cout << "Вы покинули экзамен. \n";
        session_stage = 0;
        return;
    }
    std::cout << "Произошла ошибка.\n";
}

void my_grades() {
    send_to_server("ssr " + my_login);
    char message[1024];
    recv_from_server(message, 1024);
    if (message != "0") {
        std::cout << "Ваши оценки: \n";
        std::cout << message << "\n";
        return;
    }
    std::cout << "Произошла ошибка.\n";
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

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    int ip = ip_to_int(argv[1]);
    int port = atoi(argv[2]);

    if (!connect_to_server(ip, port)) {
        std::cout << "Не удалось подключиться\n";
        exit(0);
    }

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
        }  else if (command == "start_exam" && session_stage == 0) {
            start_exam();
        } else if (command == "set_grade" && session_stage == 2) {
            set_grade();
        } else if (command == "write_solution" && session_stage == 2) {
            write_solution();
        } else if (command == "leave_exam" && session_stage == 3) {
            leave_exam();
        } else if (command == "my_grades") {
            my_grades();
        } else {
            std::cout << "Ведённая команда не существует. Чтобы посмотреть список команд напишите !help.\n";
        }

        safe_cin(command);
    }
}

