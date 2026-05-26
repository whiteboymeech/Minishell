NAME		= minishell

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./$(LIBFT_DIR)
SRCS		= build-in/cd.c \
			build-in/run.c \
			build-in/pwd.c \
			build-in/env.c \
			build-in/echo.c \
			build-in/exit.c \
			build-in/unset.c \
			build-in/export.c \
			build-in/cd_utils.c \
			build-in/env_utils.c \
			build-in/export_utils.c \
			build-in/env_more_utils.c \
			expand/expand_utils.c \
			expand/expand_tokens.c \
			expand/expand_more_utils.c \
			expand/expand_more_more_utils.c \
			loop/loop.c \
			loop/actions.c \
			loop/get_paths.c \
			loop/loop_utils.c \
			loop/loop_more_utils.c \
			loop/loop_more_more_utils.c \
			loop/loop_more_n_more_utils_again.c \
			loop/loop_more_n_more_n_more_utils_again.c \
			run/main.c \
			run/run_pipeline.c \
			run/search_and_launch.c \
			run/search_and_launch_utils.c \
			free/free.c \
			free/close.c \
			heredocuments/heredoc.c \
			heredocuments/heredoc_utils.c \
			lexer/lexer.c \
			lexer/lexer_more_utils.c \
			lexer/lexer_utils.c \
			pipes/pipes.c \
			pipes/valid_syntax.c \
			redirs/redir.c \
			redirs/redir_utils.c \
			signal/sig.c \

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
