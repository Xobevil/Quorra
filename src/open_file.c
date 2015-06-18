/*
** open_file.c for open_file in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 23:27:48 2015 sylvain garant
** Last update Wed Jun 17 15:01:11 2015 sylvain garant
*/

#include "../include/quorra.h"

int             open_file(char *file, char *ext)
{
  struct stat   buf;
  int           fd;

  if (stat(file, &buf))
    return (printerr(1));
  if (!S_ISREG(buf.st_mode))
    return (printerr(2));
  if (!match(file, ext))
    return (printerr(3));
  if (!(fd = open(file, O_RDONLY)))
    return (printerr(4));
  return (fd);
}
