/*
** generator.c for generator in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Mon Jun 22 13:55:35 2015 sylvain garant
** Last update Thu Jun 25 10:52:50 2015 sylvain garant
*/

#include "../include/quorra.h"

int     *create_pct_tab(int iptSize, int optSize, int lyrNb)
{
  int   *pctNb;
  int   i;

  if (!(pctNb = malloc(sizeof(int) * (lyrNb + 1))))
    return (NULL);
  i = 0;
  pctNb[0] = iptSize;
  while (++i < lyrNb - 1)
    pctNb[i] = iptSize + 1;
  pctNb[i++] = optSize;
  pctNb[i++] = 0;
  return (pctNb);
}

int		init_netout(t_lyr **network, int *pctNb,
			    double *opt[GENSIZE], double *genome[GENSIZE])
{
  double	*output;
  double	*gnm = NULL;
  int		i;

  i = -1;
  if (!(generate_genome(3, pctNb, &gnm)))
    return (printerr(23));
  if (!(*network = init_network(gnm, &output)))
    return (printerr(24));
  while (++i < GENSIZE)
    {
      opt[i] = NULL;
      genome[i] = NULL;
    }
  while (--i >= 0)
    if (!(generate_genome(3, pctNb, &genome[i])))
      return (printerr(23));
  free(gnm);
  free(output);
  return (0);
}

void    free_generator(double **genome, double **output, int bestGen, t_lyr *n,
		       int *pctNb)
{
  int   i;

  i = -1;
  while (++i < GENSIZE)
    {
      if (bestGen != i)
	free(genome[i]);
      free(output[i]);
    }
  free_network(n);
  free(pctNb);
}

void	display_result(time_t start, double *output, int size, double *genome,
		       int gen)
{
  int	i;

  i = -1;
  printf("Process terminated\n");
  printf("Obtained output(s) from generation %d of size %d :\n", gen, GENSIZE);
  while (++i < size)
    printf("\t- %f\n", output[i]);
  printf("Genome generated size : %d genes\n", doublen(genome));
  printf("Time needed : %d second(s)\n", (int) (time(0) - start));
}

double		*generator(double *ipt, int iptSize,
			   double *opt, int optSize, double acc)
{
  double	*genome[GENSIZE];
  double	*output[GENSIZE];
  t_lyr		*network = NULL;
  int		bestGen;
  int		*pctNb;
  time_t	actual;
  double	gen;
  int		i;

  if (!(pctNb = create_pct_tab(iptSize, optSize, 3)))
    return (NULL);
  if (init_netout(&network, pctNb, output, genome))
    return (NULL);
  bestGen = -1;
  gen = -1;
  actual = time(0);
  while (bestGen == -1 || !acceptation(output[bestGen], opt, optSize, acc))
    {
      //i = -1;
      //while (++i < GENSIZE)
      //if (!(generate_genome(3, pctNb, &genome[i])))
      //return (NULL);
      if (bestGen != -1)
	genetXlab(genome, output, opt, optSize);
      i = -1;
      //while (--i >= 0)
      while (++i < GENSIZE)
        if (!(output[i] = nn(network, genome[i], ipt, output[i], optSize)))
          return (NULL);
      bestGen = best_doubtab(output, opt, optSize);
      gen++;
    }
  display_result(actual, output[bestGen], optSize, genome[bestGen], gen);
  free_generator(genome, output, bestGen, network, pctNb);
  return (genome[bestGen]);
}
