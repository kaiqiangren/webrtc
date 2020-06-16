#include <iostream>
#include <unistd.h>
#include <stdlib.h>

// 使用daemon api实现后台运行
int main (int argc, char* argv[]) {
  if (daemon(0, 0) == -1) {
    std::cout << "error" <<std::endl;
    exit(-1);
  };
  while (1)
  {
    sleep(1);
  }
  
};