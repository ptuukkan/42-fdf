# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 12:36:17 by ptuukkan          #+#    #+#              #
#    Updated: 2021/07/29 17:49:09 by ptuukkan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIB = libft.a
SRCDIR = srcs
SRCS = read_file.c draw_map.c draw_line.c controls.c clip3d.c \
		main.c rotate_controls.c color.c mv_matrices.c \
		projection_matrices.c matrix_operations.c clip2d.c

OBJDIR = objects
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
INC = includes/

GCC = gcc -Werror -Wextra -Wall -O3

all: $(NAME)


# Uncomment below for MAC
# $(NAME): $(OBJS) libft/$(LIB)
# 	$(GCC) $(OBJS) -o $(NAME) libft/$(LIB) -lmlx -I $(INC) -I libft/$(INC) \
# 	-framework OpenGL -framework AppKit

# Uncomment below for Linux
$(NAME): $(OBJS) libft/$(LIB)
	$(GCC) $(OBJS) -o $(NAME) libft/$(LIB) -lmlx -I $(INC) -I libft/$(INC) \
	-lXext -lX11 -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)/fdf.h
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(GCC) -c $< -o $@ -I $(INC) -I libft/$(INC)

lib:
	make -C libft/

libft/$(LIB):
	make -C libft/

clean:
		/bin/rm -f $(OBJS)
		/bin/rm -rf $(OBJDIR)
		make -C libft/ clean

fclean : clean
		/bin/rm -f $(NAME)
		make -C libft/ fclean

re: fclean all

.PHONY: clean fclean all lib
