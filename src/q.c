/*
** q.c for Quorra in /home/garant_s/quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:24:22 2015 sylvain garant
** Last update Thu Jun 18 19:01:48 2015 sylvain garant
*/

#include "../include/quorra.h"

int	*create_pct_tab(double *input, double *output, int lyrNb)
{
  int	*pctNb;
  int	i;

  if (!(pctNb = malloc(sizeof(int) * lyrNb)))
    return (NULL);
  i = -1;
  pctNb[0] = doublen(input);
  while (++i < lyrNb - 2)
    pctNb[i] = doublen(input) + 1;
  pctNb[i++] = doublen(output);
  pctNb[i++] = 0;
  return (pctNb);
}

int		generator(double *ipt, double *opt)
{
  double	*genome[10];
  double	*output[10];
  int		*pctNb;
  int		i;

  i = -1;
  pctNb = create_pct_tab(ipt, opt, 3);
  while (++i < 10)
    if (!(genome[i] = generate_genome(3, pctNb)))
      return (-1);
  i = -1;
  while (++i < 10)
    if (!(output[i] = neural_network(genome[i], ipt)))
      return (-1);
  while (i-- > 0)
    {
      free(genome[i]);
      free(output[i]);
    }
  free(pctNb);
  return (0);
}

int		main(int argc, char **argv)
{
  t_cnf		cnf;

  srand(getpid() * time(0));
  memset(&cnf, 0, sizeof(t_cnf));
  user_input(argc, argv, &cnf);

  double	*genome;
  double	*input;
  double	*output;
  int		*pctNb;

  if (!(pctNb = malloc(sizeof(int) * 4)))
    return (-1);
  pctNb[0] = 2;
  pctNb[1] = 3;
  pctNb[2] = 1;
  pctNb[3] = 0;
  if (!(input = malloc(sizeof(double) * 2)))
    return (-1);
  input[0] = 1;
  input[1] = 0;
  genome = generate_genome(3, pctNb);
  while ((output = neural_network(genome, input)) && *output < 0.82)
    {
      free(genome);
      genome = generate_genome(3, pctNb);
      free(output);
    }
  printf("%f\n", *output);
  free(genome);
  free(output);
  free(input);
  free(pctNb);
  return (0);
}
