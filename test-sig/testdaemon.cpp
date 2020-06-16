#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
// 使用fork方式实现后台进程
void daemonlize () {
  int fd;
  pid_t pid;
  if((pid = fork()) < 0) {
    std::cout << "can't create child process!" <<std::endl;
  } else if (pid != 0) {
    exit(0);
  };

  setsid();

  if (chdir("/") < 0) {
    std::cout << "can't change dir" <<std::endl;
    exit(-1);
  };

  fd = open("/dev/null", O_RDWR);
  dup2(fd, STDIN_FILENO);
  dup2(fd, STDOUT_FILENO);
  dup2(fd, STDERR_FILENO);
};


int main (int argc, char* argv[]){
  daemonlize();
  while (1){
    /* code */
    sleep(1);
  }
  
};
