# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 15:16:41 by jdidier           #+#    #+#              #
#    Updated: 2022/01/03 13:22:36 by jdidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC=gcc

CFLAGS= -Wall -Wextra -Werror -lpthread -g3 -fsanitize=address



RM=rm -f

SRCS= main.c utils.c libft.c

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