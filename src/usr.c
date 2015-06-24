/*
** usr.c for usr in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 18 11:07:14 2015 sylvain garant
** Last update Wed Jun 24 14:29:56 2015 sylvain garant
*/

#include "../include/quorra.h"

void    user_input(int argc, char **argv, t_cnf *cnf)
{
  int   i;

  i = 0;
  memset(cnf, 0, sizeof(*cnf));
  while (++i < argc)
    {
      if (match(argv[i], "-csv") && i + 1 < argc)
        {
          cnf->conf |= CSV;
          cnf->csv = argv[i + 1];
        }
      else if (match(argv[i], "-s") && i + 1 < argc)
        {
          cnf->conf |= SVE;
          cnf->sve = argv[i + 1];
        }
      else if (match(argv[i], "-i") && i + 1 < argc)
        {
          cnf->conf |= IPT;
          cnf->ipt = argv[i + 1];
        }
      else if (match(argv[i], "-o") && i + 1 < argc)
        {
          cnf->conf |= OPT;
          cnf->opt = argv[i + 1];
        }
      else if (match(argv[i], "-g") && i + 1 < argc)
        {
          cnf->conf |= GEN;
          cnf->gen = argv[i + 1];
	}
      else if (match(argv[i], "-pct") && i + 1 < argc)
        {
          cnf->conf |= PCT;
          cnf->pct = argv[i + 1];
	}
      else if (match(argv[i], "-a") && i + 1 < argc)
        {
          cnf->conf |= ACC;
          cnf->acc = argv[i + 1];
	}
    }
}

int     save_genome(char *file, double *genome)
{
  int   fd;

  if (!match(file, "*.gen"))
    return (printerr(8));
  if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    return (printerr(7));
  while (*genome)
    {
      write(fd, genome, sizeof(double));
      genome++;
    }
  printf("Genome saved in file : %s\n", file);
  close(fd);
  return (0);
}

int		create_io_pct(char *pct, double **input, double **output)
{
  char          **st;
  double        *i;
  double        *o;

  if (*input || *output)
    return (-1);
  if (!(st = strtowordtab(pct, ", ")))
    return (printerr(12));
  if (!st[0] || !st[1] || !st[2] || st[3])
    return (printerr(13));
  if (!(i = malloc(sizeof(double) * 2)))
    return (printerr(11));
  i[0] = atof(st[0]);
  i[1] = atof(st[1]);
  if (!(o = malloc(sizeof(double) * 1)))
    return (printerr(11));
  o[0] = atof(st[2]);
  free(st);
  *input = i;
  *output = o;
  return (0);
}

int		create_io_img(t_img *top, char *opt,
			      double **input, double **output)
{
  int		outputSize;
  char          **st;
  double	max;
  double	pix;
  double        *i;
  double        *o;
  int           it;

  it = -1;
  if (*input || *output)
    return (-1);
  if (!(max = top->max))
    return (-1);
  if (!(st = strtowordtab(opt, ", ")))
    return (printerr(12));
  if (!st[0])
    return (printerr(13));
  if (!(i = malloc(sizeof(double) * (top->x * top->y))))
    return (printerr(11));
  it = -1;
  while (++it < top->x * top->y)
    {
      pix = top->pix[it];
      i[it] = 1 - (pix / max);
    }
  if (!(o = malloc(sizeof(double) * strlen(opt))))
    return (printerr(11));
  it = -1;
  while (st[++it])
    o[it] = atof(st[it]);
  outputSize = strtablen(st);
  free(st);
  *input = i;
  *output = o;
  return (outputSize);
}

int		create_i(char *ipt, double **input)
{
  double	*i;
  char		**st;

  if (!match(ipt, "*.pgm") && !match(ipt, "*,*") && !match(ipt, "* *"))
    return (printerr(21));
  if (match(ipt, "*.pgm"))
    return (-1);
  if (!(i = malloc(sizeof(double) * 2)))
    return (printerr(11));
  if (!(st = strtowordtab(ipt, ", ")) || !st[0] || !st[1] || st[2])
    return (-1);
  i[0] = atof(st[0]);
  i[1] = atof(st[1]);
  *input = i;
  free(st);
  return (0);
}
