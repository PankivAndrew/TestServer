#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <zconf.h>

int main(int argc, char*argv[]) {
    struct sockaddr_in server ;
    char buf[2048] = "ls\n";
    char ls[2048] = "ls\n";
    int sd = socket (AF_INET,SOCK_STREAM,0);
    if( sd == -1 ) {
        sd = errno;
        printf("Error: %s\n",strerror(sd));
    }
    memset(&server, 0, sizeof( server ));
    server . sin_family = AF_INET;
    server .sin_port = htons(9099);
    if ( inet_aton(argv [1], &server.sin_addr) <= 0 ) {}
    int res = connect(sd, (const sockaddr *) &server, sizeof( server ));
    if( res == -1){
        res = errno;
        printf("Error: %a\n",strerror(res));
    }
    int rcv;
    for (;;) {
        rcv = read(sd,buf,sizeof(buf));
        printf ("%s",buf);

        if (rcv == -1) {
            rcv = errno;
            printf("Error: %s\n",strerror(rcv));
            exit(EXIT_FAILURE);
        }
        fflush(stdout);
        sleep(1);
        int snd = write(sd, ls, sizeof (ls ));
        if(snd == -1){
            snd = errno;
            printf("Error: %s\n",strerror(snd));
            exit(EXIT_FAILURE);
        }

    }
    return 0;
}