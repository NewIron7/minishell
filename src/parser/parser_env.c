/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:50:56 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/04 16:11:21 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	expand_redirect(t_parsing *elem, t_env envp)
{
	/*
	t_expand	*split;
	char		*content;

	if (!split_quotes(&split, elem->content))
		return (EXIT_FAILURE);
	if (!expand_var(&split, envp))
		return (EXIT_FAILURE);
	if (!expand_wildcards(&split))
		return (EXIT_FAILURE);
	if (!replace_content(&split, elem))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	*/
	(void) elem;
	(void) envp;
	//ft_printf_fd(2, "TODO : Expanding redirection : %s (in src/parser/parser_env.c)\n", elem->content);
	return (0);
}

static void	print_split(t_expand split[])
{
	int	i;
	char	*type[3] = {"DFL", "SPL", "DBL"};

	i = 0;
	ft_printf_fd(2, "***split***\n");
	while (split[i].str)
	{
		ft_printf_fd(2, "[%s] - %s\n", type[split[i].type], split[i].str);
		i++;
	}
}

static int	expand_argument(t_parsing *elem, t_env envp)
{
	t_expand	*split;
	t_list		*block;

	ft_printf_fd(2, "TODO : Expanding argument : %s (in src/parser/parser_env.c)\n", elem->content);
	if (!split_quotes(&split, elem->content))
		return (EXIT_FAILURE);
	ft_printf_fd(2, "---elem->content:%s\n", elem->content);
	print_split(split);
	if (expand_var(split, envp))
		return (EXIT_FAILURE);	
	ft_printf_fd(2, "After expand_var\n");
	print_split(split);
	if (!split_fields(split, &block))
		return (EXIT_FAILURE);
//	if (!expand_wildcards(block))
//		return (EXIT_FAILURE);
	if (replace_content(block, elem))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

char	put_var_env(t_portion chunck, t_env envp)
{
	t_parsing	*next;
	int			err;

	err = 0;
	while (chunck.start != chunck.end)
	{
		next = chunck.start->next;
		if (chunck.start->type == LEFT_PAR)
		{
			chunck.start = goto_par_end(chunck.start);
			next = chunck.start->next;
		}
		else if (chunck.start->prev && is_redirect(chunck.start->prev))
			err = expand_redirect(chunck.start, envp);
		else if (chunck.start->type == CMD || chunck.start->type == ARG)
			err = expand_argument(chunck.start, envp);
		if (err)
			return (err);
		chunck.start = next;
	}
	return (0);
}
