/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:33:03 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/23 22:57:16 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*ft_strtok(char *str, char *delim);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(char *src);
char				*ft_strcat(char c, char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);
char				*ft_strchr_int(char *s, int c, int i);
char				**ft_split(char *s, char c);
char				*ft_itoa(int nb);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
char				*ft_strnstr(char *big, char *little, size_t len);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strcat_allocated(char *dest, char *src);
char				*ft_strchar(char to_put, char *src);

int					ft_strcspn(char *s, char *reject);
int					ft_strspn(char *s, char *accept);
int					ft_atoi(const char *nptr);
int					ft_isalnum(int c);
long				ft_atol(const char *str);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
int					ft_lstsize(t_list *lst);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				ft_bzero(void *s, size_t n);
void				ft_free_tab(char **tab);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *destination, const void *source,
						size_t size);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				*ft_memchr(const void *s, int c, size_t n);

size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t size);

unsigned int		ft_strlen(char *s);

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
char				*get_next_line(int fd);

#endif
