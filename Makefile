# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2016/05/30 17:20:21 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC =	arguments.c coordinates.c display.c errors.c \
        exit.c fractol.c gradient.c hooks.c inputs.c \
        mandelbrot.c \
        julia.c \
        garczyn.c \
        julia3di.c \
        julia3dr.c \
        weird.c \
        sine.c \
        ship.c \
        triangles.c \
        squares.c

OBJ = $(SRC:.c=.o)

FLG = 

LIB =	-I minilibx_macos \
		-lmlx \
		-framework OpenGL -framework AppKit \
		-lpthread \

DEB = -g

OPT = -Ofast -ffast-math

all: $(NAME)

libft:

$(NAME):$(OBJ)
	gcc $(FLG) $(OPT) $(OBJ) $(LIB) $(DEB) -o $(NAME)

%.o: %.c
	gcc $(FLG) $(OPT) $(DEB) -c $< $  -pthread

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

optire: fclean opti
