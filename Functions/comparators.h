// Header definition for comparator functions

int compare_scores(const void* score_a, const void* score_b);
int compare_scores_desc(const void* score_a, const void* score_b);

typedef struct
{
  int width;
  int height;
} rectangle;

int compare_areas(const void* area_a, const void* area_b);
int compare_areas_desc(const void* area_a, const void* area_b);

int compare_names(const void* name_a, const void* name_b);
int compare_names_desc(const void* name_a, const void* name_b);