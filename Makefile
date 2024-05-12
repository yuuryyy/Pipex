# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youssra <youssra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 19:24:10 by ychagri           #+#    #+#              #
#    Updated: 2024/05/12 19:48:43 by youssra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex

HEADER	:= mandatory/Inc/pipex.h

CFLAGS	:= -Wall -Wextra -Werror 

CC		:= cc

SRCS	:=	main.c \
			mandatory/tools/check_files.c \
			mandatory/tools/get_cmd.c \
			mandatory/tools/get_path.c \

OBGS	:= $(SRCS:.c=.o)

LIBRARY	:= lib/libft.a

all : $(NAME)

lib :
	make -C lib

$(NAME) : $(OBGS) lib
	$(CC) $(CFLAGS) $(OBGS) $(LIBRARY) -o $(NAME)

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
