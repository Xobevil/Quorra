/*
** genome.c for genome in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 09:08:43 2015 sylvain garant
** Last update Mon Jun 29 14:06:29 2015 sylvain garant
*/

#include "../include/quorra.h"

int	genome_size(int lyrNb, int *pctNb)
{
  int	nb;
  int	i;

  nb = 0;
  i = -1;
  while (++i + 1 < lyrNb)
    nb += pctNb[i] * pctNb[i + 1] + pctNb[i + 1];
  return (nb);
}

double		generate_gene()
{
  double	gene;

  gene = (double) rand();
  while ((gene /= 10) > RAND_GENE_MAX_VALUE);
  return (gene);
}

int	check_param(int lyrNb, int *pctNb)
{
  if (lyrNb <= 0)
    return (printerr(6));
  if (intlen(pctNb) != lyrNb)
    return (printerr(6));
  return (0);
}

double          get_gene(double *genome)
{
  static double *gen;

  if (genome)
    {
      gen = genome;
      return (0);
    }
  if (!gen)
    return (-1);
  gen++;
  return (*(gen - 1));
}

double		*generate_genome(int lyrNb, int *pctNb, double **genome)
{
  int		genSize;
  int		i;

  if (check_param(lyrNb, pctNb))
    return (NULL);
  i = 0;
  genSize = genome_size(lyrNb, pctNb) + intlen(pctNb) + 1;
  if (!*genome && !(*genome = malloc(sizeof(double) * (genSize + 1))))
    return (NULL);
  (*genome)[i++] = (double) lyrNb;
  while (*pctNb)
    (*genome)[i++] = (double) *pctNb++;
  while (i < genSize)
    (*genome)[i++] = generate_gene();
  (*genome)[i] = -1;
  return (*genome);
}
