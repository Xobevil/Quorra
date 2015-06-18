/*
** prerequis.c for prerequis in /home/garant_s/Piscine2Merde/SBMLparser
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Mon Jun 15 09:31:38 2015 sylvain garant
** Last update Thu Jun 18 10:57:52 2015 sylvain garant
*/

#include <stdlib.h>

int	is_sep(char c, char *sep)
{
  while (*sep)
    if (c == *sep++)
      return (1);
  return (0);
}

int	word_number(char *str, char *sep)
{
  int	nb;

  nb = 0;
  while (*str)
    {
      if (!is_sep(*str, sep) && is_sep(*(str + 1), sep))
	nb++;
      str++;
    }
  return (nb);
}

char	**strtowordtab(char *str, char *sep)
{
  char	**result;
  int	i;

  i = 0;
  if (!(result = malloc(sizeof(char*) * (word_number(str, sep) + 1))))
    return (NULL);
  while (*str && is_sep(*str, sep))
    str++;
  while (*str)
    {
      result[i++] = str;
      while (*str && !is_sep(*str, sep))
	str++;
      while (*str && is_sep(*str, sep))
	*str++ = 0;
    }
  result[i] = 0;
  return (result);
}
