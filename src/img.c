/*
** img.c for img in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 16:23:22 2015 sylvain garant
** Last update Mon Jun 22 11:20:14 2015 sylvain garant
*/

#include "../include/quorra.h"

void	free_img(t_img *destroy)
{
  free(destroy->pix);
  free(destroy);
}

int	my_function_that_works(char *nb)
{
  int	result;
  int	i;

  result = 0;
  i = -1;
  while (nb[++i])
    result = (result * 10) + (nb[i] - '0');
  return (result);
}

int		get_data(FILE *fd, t_img *elem)
{
  char		*s = NULL;
  char		**st;
  size_t	len = 0;

  if (getline(&s, &len, fd) == -1)
    return (-1);
  while ((getline(&s, &len, fd)) != -1 && s[0] == '#');
  if (!(st = strtowordtab(s, " ")) || !st[0] || !st[1])
    return (-1);
  elem->x = atoi(st[0]);
  elem->y = atoi(st[1]);
  free(st);
  if (getline(&s, &len, fd) == -1)
    return (-1);
  elem->max = atoi(s);
  free(s);
  return (0);
}

int		recov_img(FILE *fd, t_img *elem)
{
  char		*s = NULL;
  int		ln;
  size_t	len = 0;;

  ln = -1;
  if (get_data(fd, elem))
    return (printerr(16));
  if (!(elem->pix = malloc(sizeof(char) * (elem->y * elem->x))))
    return (-1);
  while (getline(&s, &len, fd) != -1)
    elem->pix[++ln] = (unsigned char) atoi(s);
  free(s);
  return (0);
}

int     put_list(t_img **top, FILE *fd)
{
  t_img *elem;

  if (!(elem = malloc(sizeof(*elem))))
    return (-1);
  memset(elem, 0, sizeof(*elem));
  recov_img(fd, elem);
  elem->next = *top;
  *top = elem;
  return (0);
}

int     add_img(t_img **top, char *file)
{
  FILE	*fd;

  if (!(fd = fopen_file(file, "*.pgm")))
    return (printerr(4));
  if (put_list(top, fd))
    return (printerr(15));
  fclose(fd);
  return (0);
}
