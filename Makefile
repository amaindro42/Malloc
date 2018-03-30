# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaindro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/19 21:04:32 by amaindro          #+#    #+#              #
#    Updated: 2017/07/27 18:25:07 by amaindro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

SRC = malloc.c allocator.c free.c realloc.c show_alloc_mem.c hex_dump.c \
	  reallocf.c calloc.c

OBJ = $(SRC:.c=.o)

LIB = -L libft/ -lft

MAKELIB = make -C ./libft

CLEANLIB = make clean -C ./libft

FCLEANLIB = make fclean -C ./libft

all : $(NAME)

$(NAME) : $(OBJ)
	@$(MAKELIB)
	@gcc -Wall -Wextra -Werror -c $(SRC)
	@gcc -Wall -Wextra -Werror -shared -o $(NAME) $(OBJ) $(LIB)
	@ln -sf $(NAME) $(LINK)

clean :
	@rm -rf $(OBJ)
	@$(CLEANLIB)

fclean : clean
	@rm -rf $(NAME) $(LINK)
	@$(FCLEANLIB)

re : fclean all

.PHONY: all clean fclean re
