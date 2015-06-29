/*
** genetX.c for genetX in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 10:50:15 2015 sylvain garant
** Last update Mon Jun 29 14:24:19 2015 sylvain garant
*/

#include "../include/quorra.h"

void	momndad(int *st, int *nd,
		double *output[GENSIZE], double *dOutput, int oSize)
{
  double	delta[GENSIZE];
  double	bufst;
  double	bufnd;
  int		i;

  i = -1;
  while (++i < GENSIZE)
    delta[i] = compute_delta(output[i], dOutput, oSize);
  *st = 0;
  bufst = delta[*st];
  while (--i >= 0)
    if (bufst > delta[i])
      {
	*st = i;
	bufst = delta[i];
      }
  *nd = (!*st) ? 1 : 0;
  bufnd = delta[*nd];
  while (++i < GENSIZE)
    if (i != *st && bufnd > delta[i])
      {
	*nd = i;
	bufnd = delta[i];
      }
}

double		my_rand(int max)
{
  double	nb;

  nb = (double) rand();
  while ((nb /= 10) > max);
  return (nb);
}

int	genetX(double *gen1, double *gen2, double *gen3)
{
  int	lyrSize;
  char	bool;
  int	size;
  int	i;

  bool = 0;
  if (genlen(gen1) != genlen(gen2) && genlen(gen1) != genlen(gen3))
    return (-1);
  i = -1;
  lyrSize = (int) *gen1;
  size = genlen(gen1) - (lyrSize + 1);
  gen1 += lyrSize + 1;
  gen2 += lyrSize + 1;
  gen3 += lyrSize + 1;
  while (++i < size)
    {
      bool = ((rand() % 100) > 70) ? !bool : bool;
      gen3[i] = (bool ? (gen1[i]) : (gen2[i]));
      if (!(rand() % MUTANT_RATE))
	gen3[i] = my_rand(1);
    }
  return (0);
}

void	genetXlab(double *genome[GENSIZE],
		  double *output[GENSIZE], double *dOutput, int oSize)
{
  int	st;
  int	nd;
  int	i;

  if (!output[0])
    return ;
  momndad(&st, &nd, output, dOutput, oSize);
  i = -1;
  while (++i < GENSIZE)
    if (i != st && i != nd)
      genetX(genome[st], genome[nd], genome[i]);
}
