#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *myenv[] = {"FOOD=donuts", NULL};
  
  if(execle("./coffee", "./coffee", "cream", NULL, myenv) == -1)
  {
    fprintf(stderr, "\nCan't run process 0: %s\n\n", strerror(errno));
    return 1;
  }
  
  return 0;
}