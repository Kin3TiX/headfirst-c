#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#undef DEBUG
//#define DEBUG

#ifdef DEBUG
#	define DEBUG_TEST 1
#else
#	define DEBUG_TEST 0
#endif

#define DEBUG_PRINT(fmt, ...) do { if (DEBUG_TEST) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

int main(int argc, char *argv[])
{
  DEBUG_PRINT("%i\n", argc);
  int i;
  for(i = 0; i < argc; i++)
  {
    DEBUG_PRINT("%s\n", argv[i]);
  }
  
  char *feeds[] = {"http://rss.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
    "http://www.npr.org/rss/rss.php?id=1004"
  };
  int times = 2;
  char *phrase = argv[argc - 1];
  i=0;
  
  
  DEBUG_PRINT("FEEDS=%i\n", times);
  
  for(i=0;i<times;i++)
  {
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL};
    
    DEBUG_PRINT("i=%i, RSS_FEED=%s\n", i, feeds[i]);
    
    pid_t pid = fork();
    if(pid == -1)
    {
      fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
      return 1;
    }
    
    if(!pid)
    {
      DEBUG_PRINT("CHILD PROCESS: %i\n", pid);
      if(execle("/usr/bin/python", "/usr/bin/python","./rssgossip.py", "-u", phrase, NULL, vars) == -1)
      {
	fprintf(stderr, "Can't run script: %s\n", strerror(errno));
	return 1;
      }
    }
    else
    {
      DEBUG_PRINT("PARENT PROCESS: %i\n", pid);
      sleep(3);
    }
      
  }
  
  return 0;
}