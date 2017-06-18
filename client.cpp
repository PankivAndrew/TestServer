#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
int main(int argc, char*argv[]) {
    struct sockaddr_in server ;
    char buf[2048] = "ls";
    struct addrinfo addr; char host_buf[NI_MAXHOST];
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
    for (;;) {
        int snd = send(sd, buf, strlen (buf ), 0 );
        if(snd == -1){
            snd = errno;
            printf("Error: %s\n",strerror(snd));
        }
        int rcv = recv(sd,buf,strlen(buf),0);
        if(rcv == -1){
            rcv = errno;
            printf("Error: %s\n",strerror(rcv));
        }
        printf ("%s\n",buf);
    }
    return 0;
}