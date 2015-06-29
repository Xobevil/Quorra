/*
** q.c for Quorra in /home/garant_s/quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:24:22 2015 sylvain garant
** Last update Mon Jun 29 13:57:26 2015 sylvain garant
*/

#include "../include/quorra.h"

int	preliminary(t_cnf *cnf, t_img **img, t_put *input, t_put *output)
{
  if (IS_PCT(cnf->conf) && !IS_GEN(cnf->conf))
    {
      if (create_io_pct(cnf->pct, &(input->put), &(output->put)))
	return (printerr(9));
      input->size = 2;
      output->size = 1;
    }
  else if (IS_GEN(cnf->conf) && (IS_IPT(cnf->conf) || IS_PCT(cnf->conf)))
    {
      if (IS_IPT(cnf->conf))
	if (create_ipt_i(cnf->ipt, input))
	  return (-1);
      if (IS_PCT(cnf->conf))
	{
	  if (create_i(cnf->pct, &(input->put)))
	    return (-1);
	  output->size = 1;
	  input->size = 2;
	}
    }
  else if (IS_IPT(cnf->conf) && IS_OPT(cnf->conf) && !IS_GEN(cnf->conf))
    {
      if (add_img(img, cnf->ipt) ||
	  (output->size = create_io_img(*img, cnf->opt,
					&(input->put), &(output->put))) == -1)
	return (-1);
      input->size = (*img)->x * (*img)->y;
    }
  else
    return (printerr(14));
  return (0);
}

int	processing(t_cnf *cnf, double **genome, t_put *input, t_put *output)
{
  int	i;

  if (input->put && output->put)
    {
      if (IS_ACC(cnf->conf))
	{
	  if (!(*genome = generator(input->put, input->size, output->put,
				    output->size, atof(cnf->acc))))
	    return (printerr(10));
	}
      else
	if (!(*genome = generator(input->put, input->size,
				  output->put, output->size, 0.00000001)))
	  return (printerr(10));
      if (genome && IS_SVE(cnf->conf))
	save_genome(cnf->sve, *genome);
    }
  else if (IS_GEN(cnf->conf) && input->put && !(output->put))
    {
      if (!(*genome = recover_genome(cnf->gen, &(output->size))))
	return (printerr(17));
      if (neural_network(*genome, input->put, &(output->put)))
	return (printerr(18));
      i = -1;
      printf("Output(s) :\n");
      while (++i < output->size)
	printf("\t- %f\n", output->put[i]);
    }
  return (0);
}

void	freedom(t_cnf *cnf, t_img *img, double *genome,
		t_put *input, t_put *output)
{
  if (IS_IPT(cnf->conf) && match(cnf->ipt, "*.pgm") && !IS_GEN(cnf->conf))
    free_img(img);
  free(genome);
  free(input->put);
  free(output->put);
}

int		main(int argc, char **argv)
{
  double	*genome = NULL;
  t_put	output;
  t_put	input;
  t_img	*img = NULL;
  t_cnf	cnf;

  srand(getpid() * time(0));
  user_input(argc, argv, &cnf);
  if (!cnf.conf)
    return (printerr(14));
  genome = NULL;
  memset(&input, 0, sizeof(t_put));
  memset(&output, 0, sizeof(t_put));
  if (preliminary(&cnf, &img, &input, &output))
    return (printerr(19));
  if (processing(&cnf, &genome, &input, &output))
    return (printerr(20));
  freedom(&cnf, img, genome, &input, &output);
  return (0);
}
