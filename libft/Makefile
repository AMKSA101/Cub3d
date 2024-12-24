# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abamksa <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 19:43:00 by abamksa           #+#    #+#              #
#    Updated: 2023/12/07 09:26:08 by abamksa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

AR = ar crs

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS_P =	ft_memset.c	 			\
			ft_bzero.c	 			\
	        ft_memcpy.c 			\
			ft_memmove.c 			\
			ft_memchr.c	 			\
			ft_memcmp.c	 			\
			ft_calloc.c	 			\
			ft_strlen.c	 			\
			ft_strlcpy.c 			\
			ft_strlcat.c 			\
			ft_strchr.c  			\
			ft_strrchr.c 			\
			ft_striteri.c			\
			ft_strncmp.c 			\
			ft_strnstr.c 			\
			ft_strdup.c	 			\
			ft_isdigit.c 			\
			ft_atoi.c				\
			ft_isalpha.c 			\
			ft_isalnum.c 			\
			ft_isascii.c 			\
			ft_isprint.c 			\
			ft_toupper.c			\
			ft_tolower.c			\
			ft_substr.c     		\
			ft_strjoin.c	  		\
			ft_strtrim.c	  		\
			ft_split.c	    		\
			ft_itoa.c	      		\
			ft_strmapi.c			\
			ft_putchar_fd.c 		\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putnbr_fd.c

SRCS_B = 	ft_lstnew_bonus.c		\
			ft_lstadd_front_bonus.c	\
			ft_lstsize_bonus.c		\
			ft_lstlast_bonus.c		\
			ft_lstadd_back_bonus.c	\
			ft_lstdelone_bonus.c	\
			ft_lstclear_bonus.c		\
			ft_lstiter_bonus.c		\
			ft_lstmap_bonus.c

OBJS_P := $(SRCS_P:%.c=%.o)

OBJS_B := $(SRCS_B:%.c=%.o)

OBJS = $(OBJS_P) $(OBJS_B)

all: $(NAME)

$(NAME): $(OBJS_P)
	@$(AR) $@ $?

%.o: %.c
	@$(CC) $(CFLAGS) -I. -c $< -o $@

bonus: $(OBJS)
	@$(AR) $(NAME) $?

clean :
	@$(RM) $(OBJS_P) $(OBJS_B)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
