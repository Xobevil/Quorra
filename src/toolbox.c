/*
** toolbox.c for toolbox in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 18 11:39:53 2015 sylvain garant
** Last update Tue Jun 23 17:22:45 2015 sylvain garant
*/

#include "../include/quorra.h"

int	strtablen(char **st)
{
  int	i;

  i = -1;
  while (st[++i]);
  return (i);
}

void	write_genome(int fd, double *doubtab)
{
  while (*doubtab)
    {
      write(fd, doubtab, sizeof(double));
      doubtab++;
    }
}

double		compute_delta(double *st, double *nd, int size)
{
  int		i;
  double	delta;

  delta = 0;
  i = -1;
  while (++i < size)
    delta += ABS(st[i] - nd[i]);
  return (delta);
}

int		best_doubtab(double *doubtab[], double *out, int size)
{
  double	delta[GENSIZE];
  double	buf;
  int		i;
  int		bufi;

  i = -1;
  while (++i < GENSIZE)
    delta[i] = compute_delta(doubtab[i], out, size);
  bufi = 0;
  buf = delta[bufi];
  while (--i >= 0)
    if (delta[i] < buf)
      {
	buf = delta[i];
	bufi = i;
      }
  return (bufi);
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
    if (ABS((st[i] - nd[i])) > acc)
      return (0);
  return (1);
}
