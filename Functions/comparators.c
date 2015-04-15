#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators.h"

int compare_scores(const void* score_a, const void* score_b)
{
  int a = *(int*)score_a;
  int b = *(int*)score_b;

  return a - b;
}

int compare_scores_desc(const void* score_a, const void* score_b)
{
  return -1 * compare_scores(score_a, score_b);
}

int compare_areas(const void* area_a, const void* area_b)
{
  rectangle* rect_a = (rectangle*)area_a;
  rectangle* rect_b = (rectangle*)area_b;
  
  int a = rect_a->width * rect_a->height;
  int b = rect_b->width * rect_b->height;

  return a - b;
}

int compare_areas_desc(const void* area_a, const void* area_b)
{
  return -1 * compare_areas(area_a, area_b);
}

int compare_names(const void* name_a, const void* name_b)
{
  char* a = *(char**)name_a;
  char* b = *(char**)name_b;
  
  return a[0] - b[0];
}

int compare_names_desc(const void* name_a, const void* name_b)
{
  return -1 * compare_names(name_a, name_b);
}