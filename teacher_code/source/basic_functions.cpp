#include "start_functions.cpp"

int session_stage = 0;
std::string exam = "";

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
    char message;
    recv_from_server(&message, 1);
    if (message != '0') {
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
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
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
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
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
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
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
    char message;
    recv_from_server(&message, 1);
    if (message == '1') {
        std::cout << "Экзамен завершён. \n";
        session_stage = 0;
        return;
    }
    std::cout << "Произошла ошибка. \n";\
}
