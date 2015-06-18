/*
** genetX.c for genetX in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 10:50:15 2015 sylvain garant
** Last update Thu Jun 18 11:40:28 2015 sylvain garant
*/

#include "../include/quorra.h"

int	my_rand(int max)
{
  int	nb;

  nb = rand();
  while ((nb /= 10) > max);
  return (nb);
}

int	genetX(double *gen1, double *gen2)
{
  char	bool;

  bool = 0;
  if (doublen(gen1) != doublen(gen2))
    return (-1);
  while (*gen1)
    {
      bool = (my_rand(100) > 70) ? !bool : bool;
      *gen1 = bool ? *gen2 : *gen1;
      *gen1 = (my_rand(10000) == 42) ? (double) my_rand(1) : *gen1;
      gen1++;
      gen2++;
    }
  return (0);
}
