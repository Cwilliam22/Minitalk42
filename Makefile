# Nom des exécutables
NAME_SERVER = server
NAME_CLIENT = client

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Fichiers sources
SRCS_SERVER = server.c
SRCS_CLIENT = client.c

# Fichiers objets
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

# Dossiers
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Dépendances
all: $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(NAME_SERVER)
	@echo "\033[32m Server compiled successfully!\033[0m"

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(NAME_CLIENT)
	@echo "\033[32m Client compiled successfully!\033[0m"

clean:
	@rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[33m Object files removed!\033[0m"

fclean: clean
	@rm -f $(NAME_SERVER) $(NAME_CLIENT) server_bonus client_bonus
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[31m  Executables removed!\033[0m"

re: fclean all
