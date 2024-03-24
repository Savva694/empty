#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include "source/basic_functions.cpp"

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    int ip = ::ip_to_int(argv[1]);
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
