/*
** get_next_line.c for get_next_line in /home/garant_s/Piscine2S/SBMLparser
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Mon Jun 15 10:36:58 2015 sylvain garant
** Last update Wed Jun 17 15:40:36 2015 sylvain garant
*/

#include "../include/quorra.h"

int     get_line(char *line, char *buffer, char *keep)
{
  int   i;
  int   j;

  i = 0;
  j = strlen(line);
  while (buffer[i])
    {
      if (buffer[i] == '\n' || j == READ)
        {
          line[j] = '\0';
          if (buffer[i] == '\n')
            ++i;
          return (1);
        }
      line[j++] = buffer[i++];
    }
  keep[0] = '\0';
  line[j] = '\0';
  return (0);
}

char            *get_next_line(const int fd)
{
  static char   keep[BUFFER_LEN];
  char          buffer[BUFFER_LEN + 1];
  char          *current_line;
  int           i;

  if (!(current_line = malloc(sizeof(char) * READ)))
    return (NULL);
  memset(current_line, 0, sizeof(char) * READ);
  if (get_line(current_line, keep, keep))
    return (current_line);
  while ((i = read(fd, buffer, BUFFER_LEN)) > 0 && READ > 0)
    {
      buffer[i] = '\0';
      if (get_line(current_line, buffer, keep))
        return (current_line);
    }
  if (current_line && current_line[0])
    return (current_line);
  return (NULL);
}
