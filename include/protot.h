/*
** protot.h for protot in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:45:12 2015 sylvain garant
** Last update Thu Jun 18 21:04:20 2015 sylvain garant
*/

#ifndef PROTOT_H_
# define PROTOT_H_

/* printerr.c */
int     printerr(int errnb);

/* open_file.c */
int	open_file(char *file, char *ext);

/* genome.c */
double	get_gene(double *genome);
double  *generate_genome(int lyrNb, int *pctNb);

/* match.c */
int     match(char *s1, char *s2);

/* intlen.c */
int     intlen(int *intstr);

/* genetX.c */
int     genetX(double *gen1, double *gen2);

/* network.c */
double  *neural_network(double *genome, double *input);

/* get_next_line.c */
char	*get_next_line(const int fd);

/* strtowordtab.c */
char	**strtowordtab(char *str, char *sep);

/* img.c */
int     add_img(t_img **top, char *file);

/* usr.c */
void    user_input(int argc, char **argv, t_cnf *cnf);

/* toolbox.c */
int     doublen(double *dlen);
void    aff_gene(double gene);
void    aff_genome(double *genome);
void    free_network(t_lyr *network);
int     doubtabcmp(double *st, double *nd);
int	highest_doubtab(double *doubtab[]);
void    write_genome(int fd, double *doubtab);

#endif
