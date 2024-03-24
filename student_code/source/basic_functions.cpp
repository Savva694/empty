#include "start_functions.cpp"

int session_stage = 0;
std::string exam = "";

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
