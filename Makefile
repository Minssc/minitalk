# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/29 18:58:25 by minsunki          #+#    #+#              #
#    Updated: 2021/05/31 15:08:06 by minsunki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		=	server
CLIENT		=	client

FIL_S		=	server.c
FIL_C		=	client.c

OBJ_S		=	$(FIL_S:.c=.o)
OBJ_C		=	$(FIL_C:.c=.o)

FIL_SB		=	server_bonus.c
FIL_CB		=	client_bonus.c

OBJ_SB		=	$(FIL_SB:.c=.o)
OBJ_CB		=	$(FIL_CB:.c=.o)

CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

%.o			:	%.c
			$(CC) $(CFLAG) -c $< -o $@

all			:	$(SERVER) $(CLIENT)

$(SERVER)	:	$(OBJ_S)
			$(CC) $(OBJ_S) $(CFLAG) -o $(SERVER)

$(CLIENT)	:	$(OBJ_C)
			$(CC) $(OBJ_C) $(CFLAG) -o $(CLIENT)

bonus		:	$(OBJ_SB) $(OBJ_CB)
			$(CC) $(OBJ_SB) $(CFLAG) -o $(SERVER)
			$(CC) $(OBJ_CB) $(CFLAG) -o $(CLIENT)

clean		:
			$(RM) $(OBJ_S) $(OBJ_C) $(OBJ_SB) $(OBJ_CB)

fclean		:	clean
			$(RM) $(SERVER) $(CLIENT)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
