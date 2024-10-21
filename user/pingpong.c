#include "kernel/types.h"
#include "user/user.h"

#define MSGSIZE 16
int main(){
    int fd[2];
    pipe(fd);
    char buf [MSGSIZE];
    int pid = fork();
    //child process
    if (pid == 0){
      read(fd[0], buf, MSGSIZE);
      printf("%d: received %s\n", pid, buf);
      write(fd[1], "pong", MSGSIZE);
    }else{
      //parent process
      write(fd[1], "ping", MSGSIZE);
      wait(0);
      read(fd[0], buf, MSGSIZE);
      printf("%d: received %s\n", pid, buf);
    }
    exit(0);
}