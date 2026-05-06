NAME = libft.a
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES_BONUS = ft_lstnew_bonus.c\
				ft_lstadd_front_bonus.c\
				ft_lstsize_bonus.c\
				ft_lstlast_bonus.c\
				ft_lstadd_back_bonus.c\
				ft_lstdelone_bonus.c

SOURCES = ft_atoi.c\
		  ft_isalpha.c\
		  ft_strlen.c\
		  ft_isalnum.c\
		  ft_isascii.c\
		  ft_isdigit.c\
		  ft_isprint.c\
		  ft_memset.c\
		  ft_memcpy.c\
		  ft_memmove.c\
		  ft_strlcpy.c\
		  ft_strlcat.c\
		  ft_toupper.c\
		  ft_tolower.c\
		  ft_strchr.c\
		  ft_strchr_int.c\
		  ft_strrchr.c\
		  ft_strncmp.c\
		  ft_bzero.c\
		  ft_strdup.c\
		  ft_memchr.c\
		  ft_memcmp.c\
		  ft_calloc.c\
		  ft_strnstr.c\
		  ft_strcmp.c\
		  ft_strchar.c\
		  ft_substr.c\
		  ft_strjoin.c\
		  ft_strcat_allocated.c\
		  ft_strtrim.c\
		  ft_strcspn.c\
		  ft_strspn.c\
		  ft_strtok.c\
		  ft_split.c\
		  ft_itoa.c\
		  ft_strcat.c\
		  ft_free_tab.c\
		  ft_strmapi.c\
		  ft_striteri.c\
		  ft_putchar_fd.c\
		  ft_putstr_fd.c\
		  ft_putendl_fd.c\
		  ft_putnbr_fd.c \
		  gnl/get_next_line.c \
		  gnl/get_next_line_utils.c

OBJS = $(SOURCES:.c=.o)
OBJS_BONUS = $(SOURCES_BONUS:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	ar -rcs $@ $^

bonus: $(OBJS) $(OBJS_BONUS)
	ar -rcs $(NAME) $^

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@


run: bonus
	./libft_tester/libft_tester

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus run
