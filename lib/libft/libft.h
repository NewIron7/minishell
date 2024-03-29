/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:15:54 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 20:01:29 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

# define FT_BUFFER_SIZE 4096

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_params
{
	int	flag_alternate;
	int	flag_padding;
	int	flag_prefix;
	int	precision;
	int	width;
	int	conversion;
}	t_params;

typedef struct s_file
{
	int		fd;
	char	buff[FT_BUFFER_SIZE];
	int		pos;
}	t_file;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*get_next_line(int fd);
void	ft_putunbr_fd(unsigned int n, int fd);
void	ft_putunbr_base_fd(unsigned int n, char *base, int fd);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_printf_fd(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);
int		ft_printf_conv_c(t_params params, int arg, int fd);
int		ft_printf_conv_d(t_params params, int arg, int fd);
int		ft_printf_conv_o(t_params params, unsigned int arg, int fd);
int		ft_printf_conv_p(t_params params, void *arg, int fd);
int		ft_printf_conv_s(t_params params, const char *arg, int fd);
int		ft_printf_conv_other(t_params params, int fd);
int		ft_printf_padding(int size, t_params params, int sign, int fd);
int		ft_open(t_file *file, const char *path, int oflag);
void	ft_close(t_file *file);
int		ft_read_line(char **line, t_file *file);
int		ft_file_buffer_reload(t_file *file);
char	*ft_basename(char *cmd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_abs(int x);
char	*ft_strstr(const char *big, const char *little);
void	*ft_dynalloc(void *ptr, size_t nmemb, size_t add, size_t size);

#endif
