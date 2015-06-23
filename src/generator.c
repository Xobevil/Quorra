/*
** generator.c for generator in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Mon Jun 22 13:55:35 2015 sylvain garant
** Last update Tue Jun 23 11:28:50 2015 sylvain garant
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

/* void    free_generator(double **genome, double **output, int bestGen) */
/* { */
/*   int   i; */

/*   i = -1; */
/*   while (++i < 10) */
/*     { */
/*       if (bestGen != i) */
/*         free(genome[i]); */
/*       free(output[i]); */
/*     } */
/* } */

/* double          *generator(double *ipt, int iptSize, */
/*                            double *opt, int optSize, double acc) */
/* { */
/*   double        *genome[10]; */
/*   double        *output[10]; */
/*   int           bestGen; */
/*   int           *pctNb; */
/*   int           i; */

/*   if (!(pctNb = create_pct_tab(iptSize, optSize, 3))) */
/*     return (NULL); */
/*   bestGen = -1; */
/*   while (bestGen == -1 || !acceptation(output[bestGen], opt, optSize, acc)) */
/*     { */
/*       if (bestGen != -1) */
/*         free_generator(genome, output, -1); */
/*       i = -1; */
/*       while (++i < 10) */
/*         if (!(genome[i] = generate_genome(3, pctNb))) */
/*           return (NULL); */
/*       while (--i >= 0) */
/*         if (!(output[i] = neural_network(genome[i], ipt))) */
/*           return (NULL); */
/*       bestGen = best_doubtab(output, opt, optSize); */
/*     } */
/*   free_generator(genome, output, bestGen); */
/*   free(pctNb); */
/*   return (genome[bestGen]); */
/* } */

int		init_netout(t_lyr **network, int *pctNb, double *opt[10])
{
  double	*output;
  double	*gnm;
  int		i;

  i = -1;
  if (!(gnm = generate_genome(3, pctNb)))
    return (-1);
  if (!(*network = init_network(gnm, &output)))
    return (-1);
  while (++i < 10)
    opt[i] = NULL;
  free(gnm);
  free(output);
  return (0);
}

void    free_generator(double **genome, int bestGen)
{
  int   i;

  i = -1;
  while (++i < 10)
    if (bestGen != i)
      free(genome[i]);
}

void	free_outputs(double **output)
{
  int	i;

  i = -1;
  while (++i < 10)
    free(output[i]);
}

double          *generator(double *ipt, int iptSize,
                           double *opt, int optSize, double acc)
{
  double        *genome[10];
  double        *output[10];
  t_lyr		*network = NULL;
  int           bestGen;
  int           *pctNb;
  int           i;

  if (!(pctNb = create_pct_tab(iptSize, optSize, 3)))
    return (NULL);
  if (init_netout(&network, pctNb, output))
    return (NULL);
  bestGen = -1;
  while (bestGen == -1 || !acceptation(output[bestGen], opt, optSize, acc))
    {
      if (bestGen != -1)
        free_generator(genome, -1);
      i = -1;
      while (++i < 10)
        if (!(genome[i] = generate_genome(3, pctNb)))
          return (NULL);
      while (--i >= 0)
        if (!(output[i] = nn(network, genome[i], ipt, output[i], optSize)))
          return (NULL);
      bestGen = best_doubtab(output, opt, optSize);
    }
  free_generator(genome, bestGen);
  free_outputs(output);
  free_network(network);
  free(pctNb);
  return (genome[bestGen]);
}
