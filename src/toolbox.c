/*
** toolbox.c for toolbox in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 18 11:39:53 2015 sylvain garant
** Last update Tue Jun 30 16:52:41 2015 sylvain garant
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

int     genlen(double *dlen)
{
  int   i;

  i = -1;
  while (dlen[++i] != -1);
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

double          *recover_genome(char *file, int *oSize)
{
  int           genomeSize;
  double        lyrSize;
  double        *genome;
  double        *pctNb;
  int           fd;
  int           i;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (NULL);
  read(fd, &lyrSize, sizeof(double));
  if (!(pctNb = malloc(sizeof(double) * (lyrSize + 1))))
    return (NULL);
  i = -1;
  while (++i < lyrSize)
    read(fd, &(pctNb[i]), sizeof(double));
  pctNb[i] = 0;
  *oSize = (int) pctNb[i - 1];
  genomeSize = doublen(pctNb) + 1;
  i = -1;
  while (++i < lyrSize - 1)
    genomeSize += pctNb[i] * pctNb[i + 1] + pctNb[i + 1];
  if (!(genome = malloc(sizeof(double) * (genomeSize + 1))))
    return (NULL);
  genome[0] = lyrSize;
  i = 0;
  while (++i < lyrSize + 1)
    genome[i] = pctNb[i - 1];
  while (i < genomeSize)
    read(fd, &(genome[i++]), sizeof(double));
  genome[i] = 0;
  free(pctNb);
  close(fd);
  return (genome);
}

void    aff_percent(double *opt, double *output, int optSize, double gen,
		    int actual)
{
  system("clear");
  printf("\nCompleted %d%% from generation %d\n",
         (int) (100 - compute_delta(opt, output, optSize) * 100),
         (((int) gen > pow(2, (sizeof(int) * 8))) ?
          ((int) (pow(2, (sizeof(int) * 8)) - 1)) : ((int) gen)));
  aff_time((int) (time(0) - actual));
  printf("\n");
}

int             contOrStop(int sig)
{
  static int    x = 1;

  if (sig != -1)
    x = sig;
  return (x);
}

void    stop_signal(int sig)
{
  if (sig == SIGINT)
    contOrStop(0);
}

void	aff_time(int sec)
{
  printf("Time needed : ");
  if (sec >= 3600)
    {
      printf("%d h ", (sec / 3600));
      sec %= 3600;
    }
  if (sec >= 60)
    printf("%d m ", (sec / 60));
  printf("%d s\n", sec % 60);
}
