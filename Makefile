# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 19:24:10 by ychagri           #+#    #+#              #
#    Updated: 2024/06/11 20:07:07 by ychagri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex


HEADER	:= mandatory/Inc/pipex.h

CFLAGS	:= -g -Wall -Wextra -Werror
#  -fsanitize=address

CC		:= cc

SRCS	:=	main.c \
			mandatory/tools/check_files.c \
			mandatory/tools/get_cmd.c \
			mandatory/tools/get_path.c \
			mandatory/tools/here_doc.c \
			mandatory/tools/multipipe.c \

OBGS	:= $(SRCS:.c=.o)

LIBRARY	:= lib/libft.a

all : $(NAME)

bonus : $(NAME_B)

lib :
	make -C lib

$(NAME) : $(OBGS)  lib
	$(CC) $(CFLAGS) $(OBGS)  $(LIBRARY) -o $(NAME)


%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C lib
	rm -rf $(OBGS)

fclean:	clean
	make fclean -C lib
	rm -rf $(NAME)

re: fclean all


push: fclean
	git add .
	git commit -m "pipekhs"
	git push

.PHONY: clean fclean re lib
