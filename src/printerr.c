/*
** printerr.c for printerr in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 23:21:35 2015 sylvain garant
** Last update Fri Jun 19 10:26:53 2015 sylvain garant
*/

#include "../include/quorra.h"

int     printerr(int errnb)
{
  if (errnb == 1)
    write(2, "File doesn't exist\n", 19);
  if (errnb == 2)
    write(2, "File isn't a regular file\n", 26);
  if (errnb == 3)
    write(2, "Incorrect file\n", 15);
  if (errnb == 4 || errnb == 5)
    write(2, "Can't open file\n", 16);
  if (errnb == 6)
    write(2, "Incorrect i/o param\n", 20);
  if (errnb == 7)
    write(2, "Failed to open saving file\n", 27);
  if (errnb == 8)
    write(2, "Bad saving format, must be .gen\n", 32);
  return (-1);
}
