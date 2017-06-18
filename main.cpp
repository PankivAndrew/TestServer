#include <iostream>
#include <zconf.h>
#include <cstring>
#include <sys/wait.h>
int main(int argc,char *argv[]) {
    for(int i = 0; i < atoi(argv[1]);i++){
        pid_t PID;
        switch(PID = fork()) {
            case -1: {
                int err = errno;
                printf("Error: %s\n", strerror(err));
            }
            case 0: {
                execv("client", &argv[2]);
            }
            default: {
                printf("New client is created:%i\n", i);
            }
        }
    }
    wait(NULL);


    return 0;
}