/*
** network.c for network in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 14:40:39 2015 sylvain garant
** Last update Mon Jun 29 14:14:21 2015 sylvain garant
*/

#include "../include/quorra.h"

t_lyr   *init_network(double *genome, double **output)
{
  t_lyr *network;
  int   lyrSize;
  int   lyrNb;
  int   i = -1;

  get_gene(genome);
  lyrNb = get_gene(NULL);
  if (!(network = malloc(sizeof(t_lyr) * lyrNb)))
    return (NULL);
  memset(network, 0, sizeof(t_lyr) * lyrNb);
  while (++i < lyrNb)
    {
      if ((lyrSize = get_gene(NULL)) == -1)
	return (NULL);
      if (!(network[i].lyr = malloc(sizeof(t_pct) * lyrSize)))
        return (NULL);
      memset(network[i].lyr, 0, sizeof(t_pct) * lyrSize);
      network[i].lyrID = i + 1;
      network[i].lyrSize = lyrSize;
    }
  if (!(*output = malloc(sizeof(double) * (network[i - 1].lyrSize + 1))))
    return (NULL);
  memset(*output, 0, sizeof(double) * (network[i - 1].lyrSize + 1));
  network[i - 1].lyrID = 0;
  return (network);
}

void	fillin(t_pct *lyr, int lyrSize, double *input)
{
  int	i;

  i = -1;
  while (++i < lyrSize)
    lyr[i].y = *input++;
}

int		step(t_lyr left, t_lyr right, double **genome)
{
  double	gene;
  int		il;
  int		ir;

  ir = -1;
  get_gene(*genome);
  memset(right.lyr, 0, sizeof(t_pct) * right.lyrSize);
  while (++ir < right.lyrSize)
    {
      il = -1;
      while (++il < left.lyrSize)
  	{
	  if ((gene = get_gene(NULL)) == -1)
	    return (-1);
	  (*genome)++;
	  right.lyr[ir].y += gene * left.lyr[il].y;
	  gene = 0;
  	}
      if ((gene = get_gene(NULL)) == -1)
	return (-1);
      (*genome)++;
      right.lyr[ir].y -= gene;
      right.lyr[ir].y = 1.0 / (1.0 + exp(-(right.lyr[ir].y)));
    }
  return (0);
}

void	fillout4(t_pct *olyr, int lyrSize, double *output)
{
  int	i;

  i = -1;
  while (++i < lyrSize)
    output[i] = olyr[i].y;
}

/*
** nn() and neural_network() do the same, but neural_network() allocs and frees
** what it needs to work, so it is slower for processing, nn() get these datas
** in parameter.
** neural_network() is used for single use, nn() is more adapted for loops of
** computation.
*/

double	*nn(t_lyr *network, double *genome, double *input,
	    double *output, int outputSize)
{
  int	i;

  i = -1;
  genome += ((int) *genome) + 1;
  if (!output)
    if (!(output = malloc(sizeof(double) * outputSize)))
      return (NULL);
  fillin(network->lyr, network->lyrSize, input);
  while (network[++i].lyrID)
    if (step(network[i], network[i + 1], &genome))
      {
	write(2, "step(): Too short genome\n", 25);
	return (NULL);
      }
  fillout4(network[i].lyr, network[i].lyrSize, output);
  return (output);
}

int	neural_network(double *genome, double *input, double **output)
{
  t_lyr	*network;
  int	i;

  if (!(network = init_network(genome, output)))
    return (-1);
  i = -1;
  genome += ((int) *genome) + 1;
  fillin(network->lyr, network->lyrSize, input);
  while (network[++i].lyrID)
    if (step(network[i], network[i + 1], &genome))
      {
        write(2, "step(): Too short genome\n", 25);
        return (-1);
      }
  fillout4(network[i].lyr, network[i].lyrSize, *output);
  free_network(network);
  return (0);
}
