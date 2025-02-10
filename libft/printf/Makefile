# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcapt <wcapt@student.42lausanne.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 18:06:45 by wcapt             #+#    #+#              #
#    Updated: 2024/10/17 06:15:31 by wcapt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables
NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

#Fichiers
SRC =	ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_adresse.c \
		ft_hexa_conv.c

#Objets correspondants
OBJ = $(SRC:.c=.o)

#Commande pour créer la bibliothèque (ar = bi statique)
AR = ar rcs

#Règle par défaut
all: $(NAME)

#Compilation de la bibliothèque (pour construire libft.a)
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

#Compilation des fichiers .o à partir des .c
#($<) => fichier source
#($@) => fichier cible
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Nettoyage des fichiers objets
clean:
	rm -f $(OBJ)

#Nettoyage complet : fichiers objets + bibliothèque
fclean: clean
	rm -f $(NAME)

#Reconstruction complète
re: fclean all

#Evite les conflits si des fichiers ont le même nom que les règles
#.PHONY: all bonus clean fclean re
