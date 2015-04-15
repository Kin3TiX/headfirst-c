#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scores.h"
#include "comparators.h"

int main()
{
  int scores[] = {543,323,32,554,11,3,112};
  int scores_len = sizeof(scores)/sizeof(scores[0]);
  
  rectangle areas[] = {{1,2},{3,4},{1,1},{4,6}};
  int rect_len = sizeof(areas)/sizeof(areas[0]);
  int area = 0;
  
  char* strings[] =  {"Happy","Birthday","To","You","Mr.","President"};
  int str_len = sizeof(strings)/sizeof(strings[0]);
  
  int i;
  
  qsort(scores, scores_len, sizeof(int), compare_scores);
  printf("Scores Ascending: ");
  for(i=0;i<scores_len;i++)
  {
    printf("%i", scores[i]);
    if(i < scores_len-1)
      printf(",");
  }
  printf("\n");
  
  qsort(scores, scores_len, sizeof(int), compare_scores_desc);
  printf("Scores Descending: ");
  for(i=0;i<scores_len;i++)
  {
    printf("%i", scores[i]);
    if(i < scores_len-1)
      printf(",");
  }
  printf("\n");
  
  qsort(areas, rect_len, sizeof(rectangle), compare_areas);
  printf("Areas Ascending: ");
  for(i=0;i<rect_len;i++)
  {
    area = areas[i].height * areas[i].width;
    printf("%i", area);
    if(i < rect_len-1)
      printf(",");
  }
  printf("\n");

  qsort(areas, rect_len, sizeof(rectangle), compare_areas_desc);
  printf("Areas Descending: ");
  for(i=0;i<rect_len;i++)
  {
    area = areas[i].height * areas[i].width;
    printf("%i", area);
    if(i < rect_len-1)
      printf(",");
  }
  printf("\n");
  
  qsort(strings, str_len, sizeof(char*), compare_names);
  printf("Strings Ascending: ");
  for(i=0;i<str_len;i++)
  {
    printf("%s", strings[i]);
    if(i < str_len-1)
      printf(",");
  }
  printf("\n");

  qsort(strings, str_len, sizeof(char*), compare_names_desc);
  printf("Strings Descending: ");
  for(i=0;i<str_len;i++)
  {
    printf("%s", strings[i]);
    if(i < str_len-1)
      printf(",");
  }
  printf("\n");
  
  return 0;
}