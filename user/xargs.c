#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int argv_len = 0;
  char buf[128] = {0};
  char *max_argv[MAXARG];
  for(int i = 1; i < argc; i++){
      max_argv[i-1] = argv[i];
  }
  while(gets(buf, sizeof(buf))){
    int buf_len = strlen(buf);
    if(buf_len < 1) break;
    buf[buf_len - 1] = 0;

    argv_len = argc - 1;
    char *x = buf;
    while(*x){
      while(*x && (*x == ' ')) *x++ = 0;
      if(*x) max_argv[argv_len++] = x;
      while(*x && (*x != ' ')) x++;
    }

    if (argv_len >= MAXARG){
      printf("xargs too many args\n");
      exit();
    }
    if (argv_len < 1){
      printf("xargs too few args\n");
      exit();
    }

    max_argv[argv_len] = 0;
    if (fork() > 0) {
        wait();
    }else{
        exec(max_argv[0], max_argv);
        exit();
    }
  }
  exit();

}