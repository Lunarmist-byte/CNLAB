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
sock=socket(AF_INET,SOCK_DGRAM,0);
if(sock<0)
    {
        perror("Socket creation failed");
        exit(1);
    }
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(8080);
server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
strcpy(buffer,"Hello from client(UDP)");
sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
socklen_t addr_len=sizeof(server_addr);
while(1){
    printf("Enter message to server(type 'exit' to quit):");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]='\0';
    sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(strcmp(buffer,"exit")==0) 
        break;
    int bytes=recvfrom(sock,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&server_addr,&addr_len);
    if(bytes<0){perror("recvfrom failed");
        continue;
    }
    buffer[bytes]='\0';
    printf("Server says %s\n",buffer);
}
close(sock);
return 0;
}
