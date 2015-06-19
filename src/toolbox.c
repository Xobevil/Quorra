/*
** toolbox.c for toolbox in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 18 11:39:53 2015 sylvain garant
** Last update Fri Jun 19 14:07:23 2015 sylvain garant
*/

#include "../include/quorra.h"

void	write_genome(int fd, double *doubtab)
{
  while (*doubtab)
    {
      write(fd, doubtab, sizeof(double));
      doubtab++;
    }
}

double		doubtabavg(double *doubtab, int size)
{
  int		i;
  double	result;

  i = -1;
  result = 0;
  while (++i < size)
    result += doubtab[i];
  result /= size;
  return (result);
}

int		best_doubtab(double *doubtab[], double *out, int size)
{
  double	avgo;
  double	avg;
  int		buf;
  int		i;

  i = -1;
  buf = 0;
  avgo = doubtabavg(out, size);
  avg = doubtabavg(doubtab[0], size);
  while (++i < 10)
    if (ABS(avgo - doubtabavg(doubtab[i], size)) < ABS(avgo - avg))
      {
	avg = doubtabavg(doubtab[i], size);
	buf = i;
      }
  return (buf);
}

int     doubtabcmp(double *st, double *nd)
{
  while (*st && *nd)
    {
      if (*st > *nd)
        return (-1);
      if (*st < *nd)
        return (1);
      st++;
      nd++;
    }
  return (0);
}

int     doublen(double *dlen)
{
  int   i;

  i = -1;
  while (dlen[++i]);
  return (i);
}

void	aff_gene(double gene)
{
  printf("%f\n", gene);
}

void		aff_genome(double *genome)
{
  double	gene;

  get_gene(genome);
  while ((gene = get_gene(NULL)))
    aff_gene(gene);
}

void    free_network(t_lyr *network)
{
  t_lyr *buf;

  buf = network;
  while (buf && buf->lyrID)
    {
      free(buf->lyr);
      buf++;
    }
  free(buf->lyr);
  free(network);
}

int	acceptation(double *st, double *nd, int size, double acc)
{
  int	i;

  i = -1;
  while (++i < size)
    if ((st[i] - nd[i]) > acc || (st[i] - nd[i]) < -acc)
      return (0);
  return (1);
}
