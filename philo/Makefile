# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 15:16:41 by jdidier           #+#    #+#              #
#    Updated: 2022/01/14 18:30:42 by jdidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC=gcc

CFLAGS= -Wall -Wextra -Werror -pthread 
CFLAGS+= -g3 -fsanitize=thread



RM=rm -f

SRCS= main.c utils.c libft.c philo.c datas.c value_management.c

SRCS_BONUS=


OBJS=	${SRCS:.c=.o}

BONUS=	${SRCS_BONUS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS} 

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re
