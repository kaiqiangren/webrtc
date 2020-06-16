#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8000
#define MESSAGE_LEN 1024
int main (int argc, char* argv[]){
  int socket_fd;
  int ret;
  char sendbuffer[MESSAGE_LEN] = {0,};
  char recvbuffer[MESSAGE_LEN] = {0,};
  struct sockaddr_in serveraddr;
  // 创建socket
  socket_fd = socket(AF_INET,SOCK_STREAM, 0);

  if (socket_fd < 0) {
    std::cout << "fail to socket create!"<<std::endl;
    exit(-1);
  }
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = PORT; 
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  ret = connect(
    socket_fd, 
    (struct sockaddr *)&serveraddr,
    sizeof(struct sockaddr)
  );

  if (ret < 0) {
    std::cout << "fail to socket connect!"<<std::endl;
    exit(-1);
  }

  while (1){
    memset(sendbuffer,0,MESSAGE_LEN);
    gets(sendbuffer);
    ret = send(socket_fd, sendbuffer, strlen(sendbuffer), 0);
    if (ret <= 0) {
      std::cout << "fail to socket send!"<<std::endl;
      break;
    }

    if (strcmp(sendbuffer, "quit") == 0) {
      break;
    }

    ret = recv(socket_fd, recvbuffer, MESSAGE_LEN, 0);
    recvbuffer[ret] = '\0';
    std::cout << "recv:"
              << recvbuffer
              <<std::endl;
  }
  close(socket_fd);
};