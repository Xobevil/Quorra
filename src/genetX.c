/*
** genetX.c for genetX in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Wed Jun 17 10:50:15 2015 sylvain garant
** Last update Fri Jun 19 16:10:37 2015 sylvain garant
*/

#include "../include/quorra.h"

int	my_rand(int max)
{
  int	nb;

  nb = rand();
  while ((nb /= 10) > max);
  return (nb);
}

double		genetX_double(double gen1, double gen2, char *bool)
{
  uDouble	res;
  uDouble	buf1;
  uDouble	buf2;
  int		size;
  int		i;

  size = sizeof(double);
  buf1.d = gen1;
  buf2.d = gen2;
  res.d = 0;
  i = -1;
  while (++i < size)
    {
      *bool = (my_rand(100) > 70) ? !(*bool) : (*bool);
      if (*bool)
	{
	  if (buf2.i >> (size - i - 1) % 2)
	    res.i += 1;
	}
      else
	if (buf1.i >> (size - i - 1) % 2)
	  res.i += 1;
      if (res.i % 2)
	res.i -= (my_rand(10000) == 42) ? 1 : 0;
      else
	res.i += (my_rand(10000) == 42) ? 1 : 0;
      if (i + 1 < size)
	res.i <<= 1;
    }
  return (res.d);
}

int	genetX(double *gen1, double *gen2)
{
  char	bool;

  bool = 0;
  if (doublen(gen1) != doublen(gen2))
    return (-1);
  while (*gen1)
    {
      *gen1 = genetX_double(*gen1, *gen2, &bool);
      gen1++;
      gen2++;
    }
  return (0);
}
