#include "include/server.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return 0;
    Server server(atoi(argv[1]));
    return 0;
}

