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
  int fd[2];
  
  if(pipe(fd) == -1)
  {
    error("Can't create pipe");
  }
  
  pid_t pid = fork();
  
  if(pid == -1)
    error("Can't fork process");
  
  if(!pid)
  {
    close(fd[0]);
    dup2(fd[1], 1);
    if(execle("/usr/bin/python", "/usr/bin/python","./rssgossip.py", "-u", phrase, NULL, vars) == -1)
      error("Can't run script");
  }
  
  dup2(fd[0], 0);
  close(fd[1]);
  
  int pid_status;
  waitpid(pid,&pid_status,0);
  
  if(WEXITSTATUS(pid_status))
    error("Non-zero exit status");
  
  char url[255];
  while(fgets(url, 255, stdin))
  {
    if(url[0] == '\t')
    {
      printf("%s\n", url);
      pid_t url_pid = fork();
      if(!url_pid)
      {
	if(execlp("konqueror", "konqueror", url+1, NULL) == -1)
	  error("Can't launch browser");
      }
    }
  }
  
  return 0;
}

void error(char *msg)
{
  fprintf(stderr, "%s : %s\n", msg, strerror(errno));
  exit(1);
}