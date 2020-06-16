#include <iostream>
#include <unistd.h>
#include "server.h"

namespace avdance {
Server::Server() {
  std::cout << "construct"<< std::endl;
}

Server::~Server() {
  std::cout << "destruct"<< std::endl;
}

void Server::run () {
  while (1){
    std::cout << "running"<< std::endl;
    ::usleep(1000000); // sleep 1s
  }
}

}