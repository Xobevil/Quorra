/*
** q.c for Quorra in /home/garant_s/quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:24:22 2015 sylvain garant
** Last update Thu Jun 18 21:05:27 2015 sylvain garant
*/

#include "../include/quorra.h"

int	*create_pct_tab(int iptSize, int optSize, int lyrNb)
{
  int	*pctNb;
  int	i;

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

double		*generator(double *ipt, int iptSize, double *opt, int optSize)
{
  double	*genome[10];
  double	*output[10];
  int		bestGenomeEUW;
  int		*pctNb;
  int		i;

  if (!(pctNb = create_pct_tab(iptSize, optSize, 3)))
    return (NULL);
  i = -1;
  while (++i < 10)
    if (!(genome[i] = generate_genome(3, pctNb)))
      return (NULL);
  while (i-- > 0)
    if (!(output[i] = neural_network(genome[i], ipt)))
      return (NULL);
  bestGenomeEUW = highest_doubtab(output);
  i = -1;
  while (++i < 10)
    {
      if (bestGenomeEUW != i)
	free(genome[i]);
      free(output[i]);
    }
  free(pctNb);
  return (genome[bestGenomeEUW]);
}

int		main(int argc, char **argv)
{
  t_cnf		cnf;
  double	*input;
  double	*output;
  double	*genome;

  srand(getpid() * time(0));
  user_input(argc, argv, &cnf);
  if (!(input = malloc(sizeof(double) * 2)))
    return (-1);
  input[0] = 1;
  input[1] = 0;
  if (!(output = malloc(sizeof(double) * 1)))
    return (-1);
  output[0] = 1;
  genome = generator(input, 2, output, 1);
  free(genome);
  free(input);
  free(output);
  return (0);
}

/* int		main(int argc, char **argv) */
/* { */
/*   t_cnf		cnf; */

/*   srand(getpid() * time(0)); */
/*   memset(&cnf, 0, sizeof(t_cnf)); */
/*   user_input(argc, argv, &cnf); */

/*   double	*genome; */
/*   double	*input; */
/*   double	*output; */
/*   int		*pctNb; */

/*   if (!(pctNb = malloc(sizeof(int) * 4))) */
/*     return (-1); */
/*   pctNb[0] = 2; */
/*   pctNb[1] = 3; */
/*   pctNb[2] = 1; */
/*   pctNb[3] = 0; */
/*   if (!(input = malloc(sizeof(double) * 2))) */
/*     return (-1); */
/*   input[0] = 1; */
/*   input[1] = 0; */
/*   genome = generate_genome(3, pctNb); */
/*   while ((output = neural_network(genome, input)) && *output < 0.82) */
/*     { */
/*       free(genome); */
/*       genome = generate_genome(3, pctNb); */
/*       free(output); */
/*     } */
/*   printf("%f\n", *output); */
/*   free(genome); */
/*   free(output); */
/*   free(input); */
/*   free(pctNb); */
/*   return (0); */
/* } */
