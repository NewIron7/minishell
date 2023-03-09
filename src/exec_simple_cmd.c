/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/09 23:36:01 by ddelhalt         ###   ########.fr       */
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

static int	check_redirection(t_parsing *tokens, int start, int end)
{
	int	i;
	int	redirs;

	i = -1;
	redirs = 0;
	while ((end != -1 && ++i < end - start) || (end == -1 && tokens))
	{
		if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_DINPUT || tokens->type == R_DOUTPUT)
			redirs++;
		tokens = tokens->next;
	}
	return (redirs);
}

static char	set_fd_redirection(int *fd_in, int *fd_out, t_parsing *tokens, int redirs)
{
	while (redirs--)
	{
		while (!put_new_fd_redirec(tokens, fd_out, fd_in))
			tokens = tokens->next;
		tokens = tokens->next;
		if (*fd_out == -1 || *fd_in == -1)
			return (perror(tokens->content), 1);
		tokens = tokens->next;
	}
	return (0);
}

static char	get_args(t_parsing *tokens, int end, int start, char ***args)
{
	int	i;
	int	j;

	*args = malloc(sizeof(**args) * (ft_lstsize_parsing(tokens) + 1));
	if (*args == NULL)
		return (1);
	i = 0;
	j = 0;
	while ((end != -1 && i++ < end - start) || (end == -1 && tokens))
	{
		if (!(is_redirection(tokens) || is_redirection(tokens->prev)))
			(*args)[j++] = tokens->content;
		tokens = tokens->next;
	}
	(*args)[j] = NULL;
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
	redir = check_redirection(tokens.tokens, tokens.start, tokens.end);
	if (redir)
	{
		if (set_fd_redirection(&fd_in, &fd_out, tokens.tokens, redir))
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
		{
			waitpid(pid, &redir, 0);
			redir = get_status(redir);
		}
		else
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			redir = exec_cmd(args, *envp, fd_in, fd_out);
			exit(redir);
		}
	}
	free(args);
	return (redir);
}
