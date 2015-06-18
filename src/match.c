/*
** match.c for match in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 09:36:53 2015 sylvain garant
** Last update Wed Jun 17 09:37:41 2015 sylvain garant
*/

#include "../include/quorra.h"

int     match(char *s1, char *s2)
{
  if (*s1 != '\0' && *s2 == '*')
    return (match(s1 + 1, s2) || match(s1, s2 + 1));
  if (*s1 == '\0' && *s2 == '*')
    return (match(s1, s2 + 1));
  if (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
    return (match(s1 + 1, s2 + 1));
  if (*s1 == *s2 && *s1 == '\0' && *s2 == '\0')
    return (1);
  return (0);
}
