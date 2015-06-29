/*
** quorra.h for quorra in /home/garant_s/Quorra
**
** Made by sylvain garant
** Login   <garant_s@epitech.net>
**
** Started on  Tue Jun 16 22:25:00 2015 sylvain garant
** Last update Mon Jun 29 16:13:59 2015 sylvain garant
*/

#ifndef QUORRA_H_
# define QUORRA_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

#define GENSIZE 100
#define LYRNBR 3
#define MUTANT_RATE 10000
#define RAND_GENE_MAX_VALUE 0.01
#define SEPARATOR_CHAR ", ;"

#include "get_next_line.h"
#include "struct.h"
#include "protot.h"

#define CSV 0b00000001
#define IPT 0b00000010
#define OPT 0b00000100
#define SVE 0b00001000
#define GEN 0b00010000
#define PCT 0b00100000
#define ACC 0b01000000

#define IS_CSV(value) ((value & CSV) ? (1) : (0))
#define IS_IPT(value) ((value & IPT) ? (1) : (0))
#define IS_OPT(value) ((value & OPT) ? (1) : (0))
#define IS_SVE(value) ((value & SVE) ? (1) : (0))
#define IS_GEN(value) ((value & GEN) ? (1) : (0))
#define IS_PCT(value) ((value & PCT) ? (1) : (0))
#define IS_ACC(value) ((value & ACC) ? (1) : (0))

#define ABS(value) ((value < 0) ? -(value) : (value))

#endif
