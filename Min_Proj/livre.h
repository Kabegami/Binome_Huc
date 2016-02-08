
/*typedef struct livre;*/

struct i_livre{
  char *titre;
  char *auteur;
  int num;
};

typedef struct i_livre s_livre;

s_livre init_livre(char *titre, char *auteur, int num);
