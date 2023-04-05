/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:42:48 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/05 08:43:58 by ddelhalt         ###   ########.fr       */
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

static int	args_len(t_portion chunck)
{
	int	len;

	len = 0;
	while (chunck.start != chunck.end)
	{
		if (!(is_redirection(chunck.start)
				|| is_redirection(chunck.start->prev)))
			len++;
		chunck.start = chunck.start->next;
	}
	return (len);
}

static char	get_args(t_portion chunck, char ***args)
{
	int	i;
	int	len;

	len = args_len(chunck);
	*args = malloc(sizeof(char **) * (len + 1));
	if (*args == NULL)
		return (1);
	i = 0;
	while (chunck.start != chunck.end)
	{
		if (!(is_redirection(chunck.start)
				|| is_redirection(chunck.start->prev)))
			(*args)[i++] = chunck.start->content;
		chunck.start = chunck.start->next;
	}
	(*args)[i] = NULL;
	return (0);
}

int	verif_simple_cmd(t_process *process, t_env *envp, char ***args)
{
	int			redir;

	*args = NULL;
	if (check_env_heredoc(process->chunck, *envp))
		return (0);
	if (put_var_env(process->chunck, *envp))
		return (0);
	redir = check_redirection(process->chunck);
	if (redir && set_fd_redirect(&process->infile, &process->outfile,
			process->chunck.start, redir))
		return (0);
	if (get_args(process->chunck, args))
		return (0);
	if (**args == NULL)
	{
		free(*args);
		return (0);
	}
	return (1);
}
