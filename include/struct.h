/*
** struct.h for struct in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:34:04 2015 sylvain garant
** Last update Fri Jun 19 10:45:40 2015 sylvain garant
*/

#ifndef STRUCT_H_
# define STRUCT_H_

typedef struct	s_cnf
{
  char		conf;
  char		*csv;
  char		*sve;
  char		*ipt;
  char		*opt;
  char		*pct;
}		t_cnf;

typedef struct	s_img
{
  int		x;
  int		y;
  int		max;
  unsigned char	**pix;
  struct s_img	*next;
}		t_img;

typedef struct	s_pct
{
  double	teta;
  double	y;
}		t_pct;

typedef struct	s_lyr
{
  int		lyrSize;
  int		lyrID;
  t_pct		*lyr;
}		t_lyr;

#endif
