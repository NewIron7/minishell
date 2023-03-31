/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:42:48 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/31 17:01:27 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	is_redirection(t_parsing *tokens)
{
	if (tokens == NULL)
		return (0);
	if (tokens->type >= R_INPUT && tokens->type <= R_DOUTPUT)
		return (1);
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

int	verif_simple_cmd(t_process *process, t_parsing *tokens, t_env *envp,
	char ***args)
{
	int			redir;

	*args = NULL;
	if (check_env_heredoc(tokens, process->tokens.end,
			process->tokens.start, *envp))
		return (0);
	if (put_var_env(&tokens, envp->env, envp->code))
		return (0);
	redir = check_redirection(tokens, process->tokens.start,
			process->tokens.end);
	if (redir && set_fd_redirect(&process->infile, &process->outfile,
			tokens, redir))
		return (0);
	if (get_args(tokens, process->tokens.end, process->tokens.start, args))
		return (0);
	if (**args == NULL)
	{
		free(*args);
		return (0);
	}
	return (1);
}
