/*
** network.c for network in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 14:40:39 2015 sylvain garant
** Last update Thu Jun 18 16:51:20 2015 sylvain garant
*/

#include "../include/quorra.h"

t_lyr   *init_network(double *genome, double **output)
{
  t_lyr *network;
  int   lyrSize;
  int   lyrNb;
  int   i;

  i = -1;
  get_gene(genome);
  lyrNb = get_gene(NULL);
  if (!(network = malloc(sizeof(t_lyr) * lyrNb)))
    return (NULL);
  while (++i < lyrNb)
    {
      if (!(network[i].lyr =
            malloc(sizeof(t_pct) * (lyrSize = get_gene(NULL)))))
        return (NULL);
      network[i].lyrID = i + 1;
      network[i].lyrSize = lyrSize;
    }
  if (!(*output = malloc(sizeof(double) * (network[i - 1].lyrSize + 1))))
    return (NULL);
  memset(*output, 0, sizeof(double) * (network[i - 1].lyrSize + 1));
  network[i - 1].lyrID = 0;
  return (network);
}

void	fill_input(t_pct *lyr, int lyrSize, double *input)
{
  int	i;

  i = -1;
  while (++i < lyrSize)
    lyr[i].y = *input++;
}

int		step(t_lyr left, t_lyr right, double *genome)
{
  int		metadata;
  double	gene;
  int		il;
  int		ir;

  ir = -1;
  get_gene(genome);
  metadata = (int) get_gene(NULL);
  genome += metadata + 1;
  get_gene(genome);
  while (++ir < right.lyrSize)
    {
      il = -1;
      right.lyr[ir].y = 0;
      while (++il < left.lyrSize)
  	{
	  if (!(gene = get_gene(NULL)))
	    return (-1);
	  right.lyr[ir].y += gene * left.lyr[il].y;
  	}
      if (!(gene = get_gene(NULL)))
	return (-1);
      right.lyr[ir].y -= gene;
      right.lyr[ir].y = 1 / (1 + exp(-(right.lyr[ir].y)));
    }
  return (0);
}

void	fillout4(t_pct *olyr, int lyrSize, double *output)
{
  int	i;

  i = -1;
  while (++i < lyrSize)
    output[i] = olyr[i].y;
  output[i] = 0;
}

double		*neural_network(double *genome, double *input)
{
  t_lyr		*network;
  double	*output;
  int		i;

  network = NULL;
  output = NULL;
  i = -1;
  if (!(network = init_network(genome, &output)))
    return (NULL);
  fill_input(network->lyr, network->lyrSize, input);
  while (network[++i].lyrID)
    step(network[i], network[i + 1], genome);
  fillout4(network[i].lyr, network[i].lyrSize, output);
  free_network(network);
  return (output);
}
