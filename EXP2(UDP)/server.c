#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main(){
int sock;
struct sockaddr_in server_addr,client_addr;
char buffer[1024];
socklen_t addr_len;
sock=socket(AF_INET,SOCK_DGRAM,0);
if(sock<0)
{
    perror("Socket creation failed");
    exit(1);
}
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(8080);
server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
{
    perror("Bind failed");
    exit(1);
}
printf("UDP Server listening at port 8080....\n");
addr_len=sizeof(client_addr);
while(1){
int bytes=recvfrom(sock,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&client_addr,&addr_len);
if(bytes<0)
{
perror("recvfrom failed");
continue;
}
buffer[bytes]='\0';
printf("Client [%s:%d] says %s\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buffer);
if(strcmp(buffer,"exit")==0){
    printf("Server shutting down.\n");
    break;
}
strcpy(buffer,"Hello from UDP server");
sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,addr_len);

}
close(sock);
return 0;
}
