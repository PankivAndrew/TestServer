#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <fcntl.h>

int main(int argc, char*argv[]) {
    printf("dssdsdsdsdsdsdsdsdsdsdsdsd\n");
    struct sockaddr_in server ;
    char buf[2048];
    char *commands[2048] = {"ls\n","pwd\n","ls | grep a\n","echo lol\n","ls -l\n","move -h\n","ls -h\n"};
    int index = 0;
    int sd = socket (AF_INET,SOCK_STREAM,0);
    if( sd == -1 ) {
        sd = errno;
        printf("Error: %s\n",strerror(sd));
        exit(EXIT_FAILURE);
    }
    memset(&server, 0, sizeof( server ));
    server.sin_family = AF_INET;
    server.sin_port = htons(9099);
    if ( inet_aton(argv [1], &server.sin_addr) <= 0 ) {}
    int res = connect(sd, (const sockaddr *) &server, sizeof( server ));
    if( res == -1){
        res = errno;
        printf("Error: %s\n",strerror(res));
        exit(EXIT_FAILURE);
    }
    int rcv;
    int file = open("stdout.txt",O_WRONLY);
    if(file == -1){
        file = errno;
        printf("Error: %s\n",strerror(file));
        exit(EXIT_FAILURE);
    }
    for (;;) {
        rcv = read(sd,buf,sizeof(buf));
        int wr = write(file,buf,sizeof(buf));
        if(wr == -1){
            wr = errno;
            printf("Error: %s\n",strerror(wr));
            exit(EXIT_FAILURE);
        }
        if (rcv == -1) {
            rcv = errno;
            printf("Error: %s\n",strerror(rcv));
            exit(EXIT_FAILURE);
        }
        fflush(stdout);
        sleep(1);
        int snd = write(sd, commands[index], sizeof (commands[index]));
        index++;
        if(index == 6)
        {
            index = 0;
        }
        if(snd == -1){
            snd = errno;
            printf("Error: %s\n",strerror(snd));
            exit(EXIT_FAILURE);
        }

    }
    return 0;
}
