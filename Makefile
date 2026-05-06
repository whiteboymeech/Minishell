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
			  lexer/lexer.c \
			  lexer/lexer_utils.c \
			  lexer/lexer_more_utils.c \
			  build/pwd.c \
			  build/echo.c \
			  build/run.c \
			  build/env.c \
			  build/env_utils.c \
			  build/exit.c \
			  build/export.c \
			  build/unset.c \
			  build/cd.c \
			  build/cd_utils.c \
			  build/env_more_utils.c \
			  build/export_utils.c \
			  redir/redir.c \
			  redir/redir_utils.c \
			  pipes/pipes.c \
			  heredoc/heredoc.c \
			  heredoc/heredoc_utils.c \
			  expand/expand_tokens.c \
			  expand/expand_utils.c \
			  expand/expand_more_utils.c \
			  prompt/prompt_ascii_art.c \
			  signal/sig.c 



OBJS		= $(SRCS:.c=.o)

RESET		= \033[0m
BOLD		= \033[1m
GREEN		= \033[32m
CYAN		= \033[36m
YELLOW		= \033[33m
MAGENTA		= \033[35m
BLUE		= \033[34m

SPINNER		= ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏



.SILENT:

all: _header $(LIBFT) $(OBJS) _link _footer



$(LIBFT):
	printf "$(YELLOW)  ➤  Building libft...$(RESET)\n"
	$(MAKE) -C $(LIBFT_DIR) --silent
	printf "$(GREEN)  ✔  libft ready$(RESET)\n\n"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

_link: $(OBJS)
	printf "\n$(GREEN)  ✔  All files compiled!$(RESET)\n\n"
	printf "$(YELLOW)  ➤  Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

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

.PHONY: all clean fclean re _header _link _footer
