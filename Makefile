##
## Makefile for make in /home/morgan/Documents/openGL
## 
## Made by Morgan SIMON
## Login   <morgan.simon@epitech.eu>
## 
## Started on  Wed Jun  7 04:27:19 2017 Morgan SIMON
## Last update Thu Jun  8 17:08:43 2017 Morgan SIMON
##

NAME	=	snake

SRC	=	main.c

CFLAGS	+=	-Wall -Wextra -O3

LDFLAGS	+=	-lGL -lglfw

OBJ	=	$(SRC:%.c=%.o)


all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
