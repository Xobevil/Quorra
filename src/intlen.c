/*
** intlen.c for intlen in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 10:45:38 2015 sylvain garant
** Last update Wed Jun 17 10:45:49 2015 sylvain garant
*/

#include "../include/quorra.h"

int     intlen(int *intstr)
{
  int   i;

  i = -1;
  while (intstr[++i]);
  return (i);
}
