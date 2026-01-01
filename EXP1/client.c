#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main(){
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
sock=socket(AF_INET,SOCK_STREAM,0);
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(8080);
server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sock, (struct sockaddr *)&server_addr,sizeof(server_addr));
printf("Connected to server \n");
strcpy(buffer,"Hello from client");
send(sock,buffer,strlen(buffer),0);
int bytes=recv(sock,buffer,sizeof(buffer)-1,0);
buffer[bytes]='\0';
printf("Server says %s\n",buffer);
close(sock);
return 0;
}
