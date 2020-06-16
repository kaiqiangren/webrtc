#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 8000
#define MESSAGE_LEN 1024
int main (int argc, char* argv[]){
  int ret = -1;
  int socket_fd;
  int accept_fd;
  int on = 1;
  int backlog = 10;
  char in_buff[MESSAGE_LEN] = {0,};
  struct sockaddr_in localaddr,remoteaddr;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1) {
    std:: cout << "创建失败!" << std::endl;
    exit(-1);
  }

  ret = setsockopt(
    socket_fd,
    SOL_SOCKET,
    SO_REUSEADDR,
    &on,
    sizeof(on)
  );

  if (ret == -1) {
    std::cout << "fail to set socket options!" <<std::endl;
  }

  localaddr.sin_family = AF_INET;
  localaddr.sin_port = PORT;
  localaddr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(localaddr.sin_zero), 8);
  ret = bind(socket_fd, (struct sockaddr *)&localaddr, sizeof(struct sockaddr));

  if (ret == -1) {
    std::cout << "fail to bind addr" <<std::endl;
    exit(-1);
  }

  // 毫秒级并发10
  ret = listen(socket_fd, backlog);
  if(ret == -1) {
    std::cout << "fail to bind listen" <<std::endl;
    exit(-1);
  }
  // 持续监听socket
  for(;;) {
    socklen_t addrlen = sizeof(struct sockaddr);
    // socket_fd
    accept_fd = accept(
      socket_fd,
      (struct sockaddr *)&remoteaddr,
      &addrlen
    );
    for(;;) {
      ret = recv(accept_fd, (void *)in_buff, MESSAGE_LEN, 0);
      if (ret == 0) {
        break;
      }

      std::cout << "recv:"
                << in_buff
                <<std::endl;
      // 服务端回复
      send(accept_fd, (void *)in_buff, MESSAGE_LEN, 0);
    }
    close(accept_fd);
  }
  close(socket_fd);
  return 0;
};
