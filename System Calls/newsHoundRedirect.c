#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void error(char *msg);

int main(int argc, char *argv[])
{
  char *phrase = argv[1];
  char *vars[] = {"RSS_FEED=http://rss.nytimes.com/services/xml/rss/nyt/MiddleEast.xml", NULL};
  FILE *f = fopen("stories.txt", "w");
  
  if(!f)
  {
    error("Can't open stories.txt");
  }
  
  pid_t pid = fork();
  
  if(pid == -1)
    error("Can't fork process");
  
  if(!pid)
  {
    if(dup2(fileno(f), 1) == -1)
      error("Can't redirect stdout");
    if(execle("/usr/bin/python", "/usr/bin/python","./rssgossip.py", phrase, NULL, vars) == -1)
      error("Can't run script");
  }
  
  int pid_status;
  waitpid(pid,&pid_status,0);
  
  if(WEXITSTATUS(pid_status))
    error("Non-zero exit status");
  
  return 0;
}

void error(char *msg)
{
  fprintf(stderr, "%s : %s\n", msg, strerror(errno));
  exit(1);
}