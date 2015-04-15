#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dearJohn.h"

int main()
{
  
  void (*replies[])(response) = {dump, second_chance, marraige, law_suit};
  
  response r[] = {
    {"Mike", DUMP}, {"Luis", SECOND_CHANCE},
    {"Matt", SECOND_CHANCE}, {"William", MARRAIGE}, {"Queermo", LAW_SUIT}
  };
  
  int i;
  
  for(i = 0; i < 5; i++)
  {
    (replies[r[i].type])(r[i]);
  }
  
  return 0;
  
}

void dump(response r)
{
  printf("Dear %s,\n", r.name);
  puts("Unfortunately your last date contacted us to");
  puts("say that they will not be seeing you again.");
}

void second_chance(response r)
{
  printf("Dear %s,\n", r.name);
  puts("Good news: your last date as asked us to");
  puts("arrange another meeting.  Please call ASAP.");
}

void marraige(response r)
{
  printf("Dear %s,\n", r.name);
  puts("Congratulations!  Your last date has contacted us");
  puts("with a proposal of marraige.");
}

void law_suit(response r)
{
  printf("Dear %s,\n", r.name);
  puts("Congratulations!  Your last date has contacted us");
  puts("to sue the pants off you.");
}