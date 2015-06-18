/*
** toolbox.c for toolbox in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 18 11:39:53 2015 sylvain garant
** Last update Thu Jun 18 21:04:13 2015 sylvain garant
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

int	highest_doubtab(double *doubtab[])
{
  int	buf;
  int	i;

  i = -1;
  buf = 0;
  while (++i < 10)
    if (*doubtab[buf] < *doubtab[i])
      buf = i;
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
