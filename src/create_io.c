/*
** create_io.c for create_io in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 25 09:32:03 2015 sylvain garant
** Last update Fri Jun 26 17:37:19 2015 sylvain garant
*/

#include "../include/quorra.h"

int             create_ipt_i(char *ipt, t_put *input)
{
  t_img         *img;
  double        pix;
  double        max;
  int           it;
  double        *i;

  if (add_img(&img, ipt))
    return (printerr(25));
  max = img->max;
  if (!(i = malloc(sizeof(double) * (img->x * img->y))))
    return (printerr(11));
  it = -1;
  while (++it < (img->x * img->y))
    {
      pix = (double) img->pix[it];
      i[it] = 1 - (pix / max);
    }
  input->put = i;
  input->size = (img->x * img->y);
  free_img(img);
  return (0);
}

int             create_i(char *ipt, double **input)
{
  double        *i;
  char          **st;

  if (!match(ipt, "*,*") && !match(ipt, "* *"))
    return (printerr(21));
  if (!(i = malloc(sizeof(double) * 2)))
    return (printerr(11));
  if (!(st = strtowordtab(ipt, SEPARATOR_CHAR)) || !st[0] || !st[1] || st[2])
    return (printerr(13));
  i[0] = atof(st[0]);
  i[1] = atof(st[1]);
  *input = i;
  free(st);
  return (0);
}

int             create_io_img(t_img *top, char *opt,
                              double **input, double **output)
{
  int           outputSize;
  char          **st;
  double        max;
  double        pix;
  double        *i;
  double        *o;
  int           it;

  it = -1;
  if (*input || *output)
    return (-1);
  if (!(max = top->max))
    return (-1);
  if (!(st = strtowordtab(opt, SEPARATOR_CHAR)))
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

int             create_io_pct(char *pct, double **input, double **output)
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
