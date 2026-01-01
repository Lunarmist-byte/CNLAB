#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main(){
int server_sock,client_sock;
struct sockaddr_in server_addr,client_addr;
memset(&server_addr,0,sizeof(server_addr));
char buffer[1024];
socklen_t addr_size;
server_sock=socket(AF_INET,SOCK_STREAM,0);
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(8080);
server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

bind(server_sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
listen(server_sock,5);
printf("Server listening at port 8080....\n");
addr_size=sizeof(client_addr);
client_sock=accept(server_sock, (struct sockaddr *)&client_addr,&addr_size);
printf("Client connected\n");
int bytes=recv(client_sock,buffer,sizeof(buffer)-1,0);
buffer[bytes]='\0';
printf("Client says %s\n",buffer);
strcpy(buffer,"Hello from server");
send(client_sock,buffer,strlen(buffer),0);
close(client_sock);
close(server_sock);
return 0;
}
