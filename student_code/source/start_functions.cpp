#include "service_functions.cpp"

std::string my_login;

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
