#include <iostream>
#include <zconf.h>
#include <cstring>
#include <sys/wait.h>
#include <chrono>
#include <thread>

int main(int argc,char *argv[]) {
    for(int i = 0; i < atoi(argv[1]);i++){
        pid_t PID;
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        switch(PID = fork()) {
            case -1: {
                int err = errno;
                printf("Error: %s\n", strerror(err));
            }
            case 0: {
                execv("client", &argv[1]);
            }
            default: {
                printf("New client is created:%i\n", i + 1);
            }
        }
    }
    wait(NULL);


    return 0;
}