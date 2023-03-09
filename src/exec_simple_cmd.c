/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/09 16:15:07 by ddelhalt         ###   ########.fr       */
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

static int	check_redirection(t_parsing *tokens, int end)
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
		if (put_new_fd_redirec(tokens, fd_out, fd_in))
			tokens = tokens->next;
		if (*fd_out == -1 || *fd_in == -1)
		{
			ft_printf_fd(2, "minishell: ");
			return (perror(tokens->content), 1);
		}
		tokens = tokens->next;
	}
	return (0);
}

static char	get_args(t_parsing *tokens, int end, int start, char ***args)
{
	int	i;

	*args = malloc(sizeof(**args) * (ft_lstsize_parsing(tokens) + 1));
	if (*args == NULL)
		return (1);
	i = 0;
	while ((end != -1 && i < end - start) || (end == -1 && tokens))
	{
		if (!(is_redirection(tokens) || is_redirection(tokens->prev)))
			(*args)[i++] = tokens->content;
		tokens = tokens->next;
	}
	(*args)[i] = NULL;
	return (0);
}

int	exec_simple_cmd(t_subtokens tokens, char **envp[])
{
	int		redir;
	int		fd_in;
	int		fd_out;
	char	**args;
	pid_t	pid;

	fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
	args = NULL;
	set_on_cmd(&tokens.tokens, tokens.start);
	redir = check_redirection(tokens.tokens, tokens.end - tokens.start);
	if (redir != -1)
	{
		if (set_fd_redirection(&fd_in, &fd_out, tokens.tokens, tokens.end - tokens.start))
			return (1);
	}
	if (get_args(tokens.tokens, tokens.end, tokens.start, &args))
		return (1);
	if (*args == NULL)
		return (EXIT_SUCCESS);
	if (is_builtin(args))
		redir = exec_builtin(args, envp, fd_in, fd_out);
	else
	{
		pid = fork();
		if (pid == -1)
			redir = EXIT_FAILURE;
		else if (pid)
			waitpid(pid, &redir, 0);
		else
		{
			redir = exec_cmd(args, *envp, fd_in, fd_out);
			exit(redir);
		}
	}
	free(args);
	return (redir);
}
