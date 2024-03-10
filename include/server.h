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
#include <vector>
#include "../include/session.h"

struct Server {
    Session session;
    int sListen;
    sockaddr_in server_address;
    std::vector<std::pair<int, int>> students;
    std::vector<std::pair<int, int>> teachers;

public:
    Server(int port);

    void find_clients();

    void comm_teacher(int index);

    void comm_student (int index);
};
