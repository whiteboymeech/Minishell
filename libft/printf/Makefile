NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_printf.c\
		  ft_putchar.c\
		  ft_puthexa.c\
		  ft_putnbr.c\
		  ft_putptr.c\
		  ft_putstr.c\
		  ft_putunsigned.c
		  
OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
