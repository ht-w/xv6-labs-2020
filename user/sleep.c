#include "kernel/types.h"
#include "user/user.h"

int main (int argc , char * argv[]){
  if (argc < 2){
    fprintf(2, "no argument found\n"); 
    exit(1);
  }
  int result = sleep(atoi(argv[1]));
  exit (result == 0? 0 : 1);
}