#include <stdio.h>
#include <math.h>

int fonctionHachage(int clef, int m)
{
  double  a = (sqrt(5)-1)/2;
  return (int)(m*(clef*a-(int)(clef*a)));
}

int main()
{
  int i;
  for (i = 0; i < 10 ; i++)
    {
      printf("pour la clef  : %d ", i);
      printf("%d \n",fonctionHachage(i,10));
    }
  for (i = 0; i < 10 ; i++)
    {
      printf("pour la clef  : %d ", i);
      printf("%d \n",fonctionHachage(i,20));
    }
  return 0;
}
