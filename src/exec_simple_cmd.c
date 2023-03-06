/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/06 18:18:29 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	set_on_cmd(t_parsing **tokens, int start)
{
	int	i;

	i = -1;
	while (++i < start)
		*tokens = (*tokens)->next;
}

static char	check_redirection(t_parsing *tokens, int end)
{
	int	i;

	i = -1;
	while ((++i < end && end != -1) || (end == -1 && tokens))
	{
		if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_DINPUT || tokens->type == R_DOUTPUT)
			return (tokens->type);
		tokens = tokens->next;
	}
	return (-1);
}

static char	set_fd_redirection(int *fd_in, int *fd_out, t_parsing *tokens, int end)
{
	int		i;

	i = -1;
	while ((++i < end && end != -1) || (end == -1 && tokens))
	{
		put_new_fd_redirec(tokens, fd_out, fd_in);
		tokens = tokens->next;
	}
	if (*fd_out == -1 || *fd_in == -1)
		return (perror("minishell"), 1);
	return (0);
}

static char	get_args(t_parsing *tokens, int end, char ***args)
{
	int	i;

	*args = malloc(sizeof(**args) * (ft_lstsize_parsing(tokens) + 1));
	if (*args == NULL)
		return (1);
	i = 0;
	while ((i < end && end != -1) || (end == -1 && tokens))
	{
		if (!(is_redirection(tokens) || is_redirection(tokens->prev)))
			(*args)[i++] = tokens->content;
		tokens = tokens->next;
	}
	(*args)[i] = NULL;
	return (0);
}

int	exec_simple_cmd(t_parsing *tokens, int start, int end, char *envp[])
{
	char	redir;
	int		fd_in;
	int		fd_out;
	char	**args;

	fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
	args = NULL;
	set_on_cmd(&tokens, start);
	redir = check_redirection(tokens, end - start);
	if (redir != -1)
	{
		if (set_fd_redirection(&fd_in, &fd_out, tokens, end - start))
			return (1);
	}
	if (get_args(tokens, end, &args))
		return (1);
	if (*args == NULL)
		return (EXIT_SUCCESS);
	if (is_builtin(args))
		redir = exec_builtin(args, &envp, fd_in, fd_out);
	else
		redir = exec_cmd(args, envp, fd_in, fd_out);
	free(args);
	return (redir);
}
