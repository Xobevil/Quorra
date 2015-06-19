/*
** q.c for Quorra in /home/garant_s/quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:24:22 2015 sylvain garant
** Last update Fri Jun 19 10:46:49 2015 sylvain garant
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

double		*generator(double *ipt, int iptSize, double *opt, int optSize)
{
  int		bestGenomeEUW;
  double	*genome[10];
  double	*output[10];
  int		*pctNb;
  int		i;

  if (!(pctNb = create_pct_tab(iptSize, optSize, 3)))
    return (NULL);
  bestGenomeEUW = -1;
  while (bestGenomeEUW == -1 || !acceptation(output[bestGenomeEUW], opt, 0.2))
    {
      if (bestGenomeEUW != -1)
	free_generator(genome, output, -1);
      i = -1;
      while (++i < 10)
	if (!(genome[i] = generate_genome(3, pctNb)))
	  return (NULL);
      while (--i >= 0)
	if (!(output[i] = neural_network(genome[i], ipt)))
	  return (NULL);
      bestGenomeEUW = highest_doubtab(output);
    }
  free_generator(genome, output, bestGenomeEUW);
  free(pctNb);
  return (genome[bestGenomeEUW]);
}

int	save_genome(char *file, double *genome)
{
  int	fd;

  if (!match(file, "*.gen"))
    return (printerr(8));
  if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    return (printerr(7));
  while (*genome)
    {
      write(fd, genome, sizeof(double));
      genome++;
    }
  printf("Saved : %s\n", file);
  close(fd);
  return (0);
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
  if (!(genome = generator(input, 2, output, 1)))
    return (-1);
  if (IS_SVE(cnf.conf))
    save_genome(cnf.sve, genome);
  free(genome);
  free(input);
  free(output);
  return (0);
}

/* int		main(int argc, char **argv) */
/* { */
/*   t_cnf		cnf; */
/*   double	*input; */
/*   double	*output; */
/*   double	*genome; */

/*   srand(getpid() * time(0)); */
/*   user_input(argc, argv, &cnf); */
/*   if (!(input = malloc(sizeof(double) * 2))) */
/*     return (-1); */
/*   input[0] = 1; */
/*   input[1] = 0; */
/*   if (!(output = malloc(sizeof(double) * 1))) */
/*     return (-1); */
/*   output[0] = 1; */
/*   if (!(genome = generator(input, 2, output, 1))) */
/*     return (-1); */
/*   if (IS_SVE(cnf.conf)) */
/*     save_genome(cnf.sve, genome); */
/*   free(genome); */
/*   free(input); */
/*   free(output); */
/*   return (0); */
/* } */
