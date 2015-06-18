/*
** img.c for img in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 16:23:22 2015 sylvain garant
** Last update Thu Jun 18 10:58:42 2015 sylvain garant
*/

#include "../include/quorra.h"

int	get_data(int fd, t_img *elem)
{
  char	*s;
  char	**st;

  if (!(s = get_next_line(fd)))
    return (-1);
  free(s);
  while ((s = get_next_line(fd)) && s[0] == '#')
    free(s);
  if (!(st = strtowordtab(s, " ")) && !st[0] && !st[1])
    return (-1);
  elem->x = atoi(st[0]);
  elem->y = atoi(st[1]);
  free(s);
  if (!(s = get_next_line(fd)))
    return (-1);
  elem->max = atoi(st[0]);
  free(s);
  return (0);
}

int     recov_img(int fd, t_img *elem)
{
  char  *s;
  int   ln;
  int   i;

  ln = -1;
  if (get_data(fd, elem))
    return (-1);
  if (!(elem->pix = malloc(sizeof(char*) * elem->y)))
    return (-1);
  while ((s = get_next_line(fd)))
    {
      i = -1;
      if (!(elem->pix[++ln] = malloc(sizeof(char) * elem->x)))
        return (-1);
      while (s[++i])
        elem->pix[ln][i] = s[i];
      free(s);
    }
  return (0);
}

int     put_list(t_img **top, int fd)
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
  int   fd;

  if ((fd = open_file(file, "*.pgm")) == -1)
    return (-1);
  put_list(top, fd);
  close(fd);
  return (0);
}
