/*
** generator.c for generator in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Mon Jun 22 13:55:35 2015 sylvain garant
** Last update Mon Jun 29 16:34:57 2015 sylvain garant
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
    //pctNb[i] = ABS(iptSize - optSize) / 2 + 2;
    //pctNb[i] = iptSize + 2;
    pctNb[i] = optSize * 4;
  pctNb[i++] = optSize;
  pctNb[i++] = 0;
  return (pctNb);
}

int		init_netout(t_lyr **network, int iptSize, int optSize,
			    double *opt[GENSIZE], double *genome[GENSIZE])
{
  double	*output;
  int		*pctNb;
  double	*gnm;
  int		i;

  i = -1;
  gnm = NULL;
  if (!(pctNb = create_pct_tab(iptSize, optSize, LYRNBR)))
    return (-1);
  if (!(generate_genome(LYRNBR, pctNb, &gnm)))
    return (printerr(23));
  if (!(*network = init_network(gnm, &output)))
    return (printerr(24));
  while (++i < GENSIZE)
    {
      opt[i] = NULL;
      genome[i] = NULL;
    }
  while (--i >= 0)
    if (!(generate_genome(LYRNBR, pctNb, &genome[i])))
      return (printerr(23));
  free(gnm);
  free(pctNb);
  free(output);
  return (0);
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
  printf("Genome generated size : %d genes\n", genlen(genome));
  printf("Time needed : %d second(s)\n", (int) (time(0) - start));
}

void    free_generator(double **genome, double **output, int bestGen, t_lyr *n)
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
}

double		*generator(double *ipt, int iptSize,
			   double *opt, int optSize, double acc)
{
  double	*genome[GENSIZE];
  double	*output[GENSIZE];
  time_t	actual = time(0);
  t_lyr		*network = NULL;
  int		bestGen = -1;
  double	gen = -1;
  int		i;

  if (init_netout(&network, iptSize, optSize, output, genome))
    return (NULL);
  while (bestGen == -1 || !acceptation(output[bestGen], opt, optSize, acc))
    {
      if (bestGen != -1)
      	genetXlab(genome, output, opt, optSize);
      i = -1;
      while (++i < GENSIZE)
        if (!(output[i] = nn(network, genome[i], ipt, output[i], optSize)))
          return (NULL);
      bestGen = best_doubtab(output, opt, optSize);
      gen++;
    }
  display_result(actual, output[bestGen], optSize, genome[bestGen], gen);
  free_generator(genome, output, bestGen, network);
  return (genome[bestGen]);
}
