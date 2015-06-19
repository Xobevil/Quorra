##
## Makefile for Makefile in /home/garant_s/Quorra
##
## Made by sylvain garant
## Login   <garant_s@epitech.net>
##
## Started on  Tue Jun 16 22:21:12 2015 sylvain garant
## Last update Fri Jun 19 09:56:53 2015 sylvain garant
##

NAME	= q

SRC	= src/$(NAME).c \
	src/printerr.c \
	src/genome.c \
	src/match.c \
	src/network.c \
	src/intlen.c \
	src/genetX.c \
	src/get_next_line.c \
	src/strtowordtab.c \
	src/img.c \
	src/usr.c \
	src/toolbox.c \
	src/open_file.c

OBJ	= $(SRC:.c=.o)

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ) -lm

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OBJ)

re: fclean all
