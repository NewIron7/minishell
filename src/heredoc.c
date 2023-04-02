/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:05:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/02 11:14:26 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_fd = -1;

static void	sig_handler_heredoc(int sig)
{
	(void)sig;
	ft_printf_fd(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	g_fd = dup(0);
	close(0);
}

char	init_heredoc(t_parsing **tokens, char **txt, int tube[2])
{
	unsigned long	size;

	*txt = ft_strdup("");
	if (pipe(tube) || *txt == NULL)
		return (free(*txt), 1);
	(*tokens)->fd = tube[0];
	*tokens = (*tokens)->next;
	size = ft_strlen((*tokens)->content);
	rm_quotes((*tokens)->content);
	if (size != ft_strlen((*tokens)->content))
		(*tokens)->prev->quoted = 1;
	return (0);
}

static char	get_the_line(t_parsing **tokens, char **txt, int tube[2])
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (g_fd != -1)
	{
		dup2(g_fd, 0);
		close(g_fd);
		g_fd = -2;
		return (free(*txt), close(tube[0]), close(tube[1]), -2);
	}
	if (check_ctrl_d(line, (*tokens)->content))
		return (free(line), 1);
	tmp = ft_strjoin(*txt, line);
	free(*txt);
	free(line);
	*txt = tmp;
	if (*txt == NULL)
		return (close(tube[0]), close(tube[1]), -1);
	tmp = ft_strjoin(*txt, "\n");
	free(*txt);
	*txt = tmp;
	if (*txt == NULL)
		return (close(tube[0]), close(tube[1]), -1);
	return (0);
}

static char	do_heredoc(t_parsing **tokens)
{
	int				tube[2];
	char			*txt;
	char			err;

	if (init_heredoc(tokens, &txt, tube))
		return (1);
	while (1)
	{
		err = get_the_line(tokens, &txt, tube);
		if (err < 0)
			return (1);
		else if (err == 1)
			break ;
	}
	write(tube[1], txt, ft_strlen(txt));
	free(txt);
	close(tube[1]);
	return (0);
}

char	ft_heredoc(t_parsing *tokens)
{
	while (tokens)
	{
		if (tokens->type == R_DINPUT)
		{
			signal(SIGINT, &sig_handler_heredoc);
			if (do_heredoc(&tokens))
			{
				signal(SIGINT, SIG_IGN);
				return (1);
			}
			signal(SIGINT, SIG_IGN);
		}
		tokens = tokens->next;
	}
	return (0);
}
