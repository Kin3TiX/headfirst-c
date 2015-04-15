#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef enum {MUDSLIDE, MONKEY_GLAND, FUZZY_NAVEL, ZOMBIE} drink;

double total(int args, ...);
double price(drink d);

int main()
{
  
  printf("The total is %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));
  
  return 0;

}

double total(int args, ...)
{
  va_list ap;
  va_start(ap, args);
  double total = 0;
  
  int i;
  for(i =0; i < args; i++)
  {
    total += price(va_arg(ap, drink));
  }
  va_end(ap);
  
  return total;
  
}

double price(drink d)
{
  switch(d)
  {
    case MONKEY_GLAND:
      return 4.82;
    case MUDSLIDE:
      return 6.79;
    case FUZZY_NAVEL:
      return 5.31;
    case ZOMBIE:
      return 5.89;
    default:
      return 0;
  }
}