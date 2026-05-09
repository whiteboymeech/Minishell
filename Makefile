NAME		= minishell

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./$(LIBFT_DIR)

SRCS		= srcs/actions.c \
			  srcs/get_paths.c \
			  srcs/loop.c \
			  srcs/loop_more_utils.c \
			  srcs/loop_more_more_utils.c \
			  srcs/loop_utils.c \
			  srcs/main.c \
			  srcs/run_pipeline.c \
			  srcs/search_and_launch.c \
			  srcs/search_and_launch_utils.c \
			  srcs/valid_syntax.c \
			  srcs/lexer.c \
			  srcs/lexer_utils.c \
			  srcs/lexer_more_utils.c \
			  srcs/pwd.c \
			  srcs/echo.c \
			  srcs/run.c \
			  srcs/env.c \
			  srcs/env_utils.c \
			  srcs/exit.c \
			  srcs/export.c \
			  srcs/unset.c \
			  srcs/cd.c \
			  srcs/close.c \
			  srcs/cd_utils.c \
			  srcs/env_more_utils.c \
			  srcs/export_utils.c \
			  srcs/redir.c \
			  srcs/redir_utils.c \
			  srcs/pipes.c \
			  srcs/heredoc.c \
			  srcs/heredoc_utils.c \
			  srcs/expand_tokens.c \
			  srcs/expand_utils.c \
			  srcs/expand_more_utils.c \
			  srcs/expand_more_more_utils.c \
			  srcs/free.c \
			  srcs/sig.c

OBJS		= $(SRCS:.c=.o)

RESET		= \033[0m
BOLD		= \033[1m
GREEN		= \033[32m
YELLOW		= \033[33m

.SILENT:

all: _header $(LIBFT) $(NAME) _footer

$(LIBFT):
	printf "$(YELLOW)  ➤  Building libft...$(RESET)\n"
	$(MAKE) -C $(LIBFT_DIR) --silent
	printf "$(GREEN)  ✔  libft ready$(RESET)\n\n"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	printf "\n$(GREEN)  ✔  All files compiled!$(RESET)\n\n"
	printf "$(YELLOW)  ➤  Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

_header:
	printf "$(YELLOW)$(BOLD)  ➤  Building $(NAME)...$(RESET)\n\n"

_footer:
	printf "$(GREEN)$(BOLD)  ✔  $(NAME) built successfully!$(RESET)\n\n"

clean:
	printf "$(YELLOW)  ➤  Cleaning objects...$(RESET)\n"
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR) --silent
	printf "$(GREEN)  ✔  Objects removed$(RESET)\n"

fclean: clean
	printf "$(YELLOW)  ➤  Removing $(NAME)...$(RESET)\n"
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR) --silent
	printf "$(GREEN)  ✔  Full clean done$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re _header _footer
