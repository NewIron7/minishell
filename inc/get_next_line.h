/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:45:29 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/16 15:27:50 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_tool
{
	char	*line;
	int		end;
}	t_tool;

char	*get_next_line(int fd);
char	*gnl_get_line(char *buf, int end);
char	*gnl_ft_strdup_(const char *s);
char	*gnl_ft_strcat(char *s1, char *s2);
char	*gnl_free_line(char *line);

int		gnl_ft_strlen(char *str);
int		gnl_is_end(char c);
int		gnl_get_end_line(char *str);

#endif
