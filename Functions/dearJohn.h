enum response_type {DUMP, SECOND_CHANCE, MARRAIGE, LAW_SUIT};

typedef struct 
{
  char *name;
  enum response_type type;
} response;

void dump(response r);

void second_chance(response r);

void marraige(response r);

void law_suit(response r);