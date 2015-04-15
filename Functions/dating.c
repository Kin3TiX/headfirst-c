#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NUM_ADS = 7;
char *ADS[]  = {
  "William: SBM GSOH likes sports, TV, dining",
  "Matt: SWM NS likes art, movies, theater",
  "Luis: SLM ND likes books, theater, art",
  "Mike: DWM DS likes trucks, sports, bieber",
  "Peter: SAMM likes chess, working out, art",
  "Josh: SJM likes sports, movies, theater",
  "Jed: DBM likes theater, books, dining"
};

int sports_no_bieber(char *s)
{
  return strstr(s, "sports") && !strstr(s, "bieber");
}

int chess(char *s)
{
  return strstr(s, "chess");
}

void find(int (*string_check) (char*))
{
  int i;
  
  puts("Search results: ");
  puts("----------------------------");
  
  for(i = 0; i < NUM_ADS; i++)
  {
    if(string_check(ADS[i]))
	printf("%s\n", ADS[i]);
  }
  
  puts("----------------------------");
  
}

int main()
{
  int (*string_check) (char*);
  string_check = chess;
  
  find(string_check);
  
  return 0;
  
}