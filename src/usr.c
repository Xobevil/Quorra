/*
** usr.c for usr in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Thu Jun 18 11:07:14 2015 sylvain garant
** Last update Thu Jun 18 11:07:25 2015 sylvain garant
*/

#include "../include/quorra.h"

void    user_input(int argc, char **argv, t_cnf *cnf)
{
  int   i;

  i = 0;
  while (++i < argc)
    {
      if (match(argv[i], "-csv") && i + 1 < argc)
        {
          cnf->conf |= CSV;
          cnf->csv = argv[i + 1];
        }
      else if (match(argv[i], "-s") && i + 1 < argc)
        {
          cnf->conf |= SVE;
          cnf->sve = argv[i + 1];
        }
      else if (match(argv[i], "-i") && i + 1 < argc)
        {
          cnf->conf |= IPT;
          cnf->ipt = argv[i + 1];
        }
      else if (match(argv[i], "-o") && i + 1 < argc)
        {
          cnf->conf |= OPT;
          cnf->opt = argv[i + 1];
        }
      else if (match(argv[i], "-g") && i + 1 < argc)
        {
          cnf->conf |= GEN;
          cnf->opt = argv[i + 1];
	}
    }
}
