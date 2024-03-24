#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include "./source/basic_functions.cpp"

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
        }  else {
            std::cout << "Ведённая команда не существует. Чтобы посмотреть список команд напишите !help.\n";
        }

        safe_cin(command);
    }
}
