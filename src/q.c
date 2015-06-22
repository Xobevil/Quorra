/*
** q.c for Quorra in /home/garant_s/quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:24:22 2015 sylvain garant
** Last update Mon Jun 22 11:22:15 2015 sylvain garant
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

void	free_generator(double **genome, double **output, int bestGen)
{
  int	i;

  i = -1;
  while (++i < 10)
    {
      if (bestGen != i)
	free(genome[i]);
      free(output[i]);
    }
}

double		*generator(double *ipt, int iptSize,
			   double *opt, int optSize, double acc)
{
  int		bestGen;
  double	*genome[10];
  double	*output[10];
  int		*pctNb;
  int		i;

  if (!(pctNb = create_pct_tab(iptSize, optSize, 3)))
    return (NULL);
  bestGen = -1;
  while (bestGen == -1 || !acceptation(output[bestGen], opt, optSize, acc))
    {
      if (bestGen != -1)
	free_generator(genome, output, -1);
      i = -1;
      while (++i < 10)
	if (!(genome[i] = generate_genome(3, pctNb)))
	  return (NULL);
      while (--i >= 0)
	if (!(output[i] = neural_network(genome[i], ipt)))
	  return (NULL);
      bestGen = best_doubtab(output, opt, optSize);
    }
  free_generator(genome, output, bestGen);
  free(pctNb);
  return (genome[bestGen]);
}

/* int	create_io_img(t_img *top, double *input, double *output) */
/* { */
  
/* } */

int		main(int argc, char **argv)
{
  double	*output;
  double	*genome;
  double	*input;
  t_cnf		cnf;
  t_img		*img;

  srand(getpid() * time(0));
  user_input(argc, argv, &cnf);
  if (!cnf.conf)
    return (printerr(14));
  input = NULL;
  output = NULL;
  genome = NULL;
  if (IS_PCT(cnf.conf))
    if (create_io_pct(cnf.pct, &input, &output))
      return (printerr(9));
  if (IS_IPT(cnf.conf))
    if (add_img(&img, cnf.ipt))
      return (-1);
  if (input && output)
    {
      if (IS_ACC(cnf.conf))
	{
	  if (!(genome = generator(input, 2, output, 1, atof(cnf.acc))))
	    return (printerr(10));
	}
      else
	if (!(genome = generator(input, 2, output, 1, 0.0)))
	  return (printerr(10));
      if (genome && IS_SVE(cnf.conf))
	save_genome(cnf.sve, genome);
    }
  if (IS_IPT(cnf.conf))
    free_img(img);
  free(genome);
  free(input);
  free(output);
  return (0);
}
