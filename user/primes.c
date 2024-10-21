#include "kernel/types.h"
#include "user/user.h"

void sieve(int fd[]){
  close(fd[1]);
  int prime;
  int current_number;
  read(fd[0], &prime, sizeof(int));
  printf("prime %d\n", prime);

  int read_status = read(fd[0], &current_number, sizeof(int));
  if (read_status == 0){
    return;
  }
  int new_fd[2];
  pipe(new_fd);
  int pid = fork();
  if (pid > 0){
    close(new_fd[0]);
    do{
      if(current_number % prime != 0){
        write(new_fd[1], &current_number, sizeof(int));
      }
    }
    while(read(fd[0],&current_number, sizeof(int)));
    close(fd[0]);
    close(new_fd[1]);
    wait(0);
  }else{
    close(fd[0]);
    sieve(new_fd);
  }
}


int main(){
  int fd[2];
  pipe(fd);
  int i;
  int pid = fork();
  if (pid > 0){
    close(fd[0]);
    for (i = 2; i <=35; i++){
      write(fd[1], &i, sizeof(int));
    }
    close(fd[1]);
    wait(0);
  }else{
    sieve(fd);
  }
  exit(0);
}