/*
** printerr.c for printerr in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 23:21:35 2015 sylvain garant
** Last update Tue Jun 23 11:24:45 2015 sylvain garant
*/

#include "../include/quorra.h"

void	display_help()
{
  printf("./q [-OPTION FILE|DATA] ...\n");
  printf("-pct \"[0;1],[0;1],[0;1]\"\n");
  printf("-a ACCEPTANCE\n");
  printf("-i PGM FILE\n");
  printf("-o DESIRED OUTPUT\n");
  printf("-s SAVE GENOME IN GEN FILE\n");
  printf("Example :\n\t./q -pct \"1,0,1\" -s perceptron.gen -a 0.18\n");
  printf("\t./q -i picture.pgm -o 1 -s img.gen -a 0.3\n");
}

int     printerr(int errnb)
{
  if (errnb == 1)
    write(2, "File doesn't exist\n", 19);
  else if (errnb == 2)
    write(2, "File isn't a regular file\n", 26);
  else if (errnb == 3)
    write(2, "Incorrect file\n", 15);
  else if (errnb == 4 || errnb == 5)
    write(2, "Can't open file\n", 16);
  else if (errnb == 6)
    write(2, "Incorrect i/o param\n", 20);
  else if (errnb == 7)
    write(2, "Failed to open saving file\n", 27);
  else if (errnb == 8)
    write(2, "Bad saving format, must be .gen\n", 32);
  else if (errnb == 9)
    write(2, "Failed to create i/o for PCT\n", 29);
  else if (errnb == 10)
    write(2, "generator() failed\n", 19);
  else if (errnb == 11)
    write(2, "malloc() failed\n", 19);
  else if (errnb == 12)
    write(2, "strtowordtab() failed\n", 19);
  else if (errnb == 13)
    write(2, "Perceptrons must only have 2 inputs and 1 output\n", 49);
  else if (errnb == 14)
    display_help();
  else if (errnb == 15)
    write(2, "Failed to recover image\n", 24);
  else if (errnb == 16)
    write(2, "Failed to get img data\n", 23);
  return (-1);
}
