#include <iostream>
#include <signal.h>
#include <unistd.h>

void sighandler (int sig) {
  std::cout << "recive signal:" 
            << sig
            << std::endl;
}

int main (int argc, char* argv[]){
  signal(SIGINT, sighandler);
  signal(SIGQUIT, sighandler);
  signal(SIGHUP, sighandler);
  pause();
  return 0;
};