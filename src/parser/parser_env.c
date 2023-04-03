/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:50:56 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/03 17:21:54 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	expand_elems(t_parsing *elem, t_parsing **next)
{
	if (!expand_elem(elem, &space_split))
		return (0);
	*next = elem->next;
	if (!expand_elem(elem, &expand_wildcard))
		return (0);
	return (1);
}

static char	expand_var(t_expand split[], t_env envp)
{
	int		i;
	char	**content_env[2];
	char	err;

	content_env[0] = envp.env;
	i = 0;
	while (split[i].str)
	{
		if (split[i].type == DFL || split[i].type == DBL)
		{
			content_env[1] = &split[i].str;
			err = put_var_env_elem(content_env, envp.code, 0, '\0');
			if (err)
				return (err);
		}
		i++;
	}
	return (0);
}

static char	init_replace_content(t_expand split[], t_parsing *elem)
{
	char	*ncontent;

	if (split && split->str)
	{
		ncontent = ft_strdup(split->str);
		if (ncontent == NULL)
			return (1);
		free(elem->content);
		elem->content = ncontent;
		return (0);
	}
	return (1);
}

static char	join_on_elem(char **content, char *str)
{
	char	*ncontent;

	ncontent = ft_strjoin(*content, str);
	if (ncontent == NULL)
		return (1);
	free(*content);
	*content = ncontent;
	return (0);
}

static char	replace_content_elem(t_expand split[], t_parsing *elem)
{
	int	i;

	if (init_replace_content(split, elem))
		return (1);
	i = 1;
	while (split[i].str)
	{
		if (join_on_elem(&elem->content, split[i].str))
			return (1);
		i++;
	}
	return (0);
}

static char	create_elem_replace_content(t_expand split[], t_parsing **elem)
{
	t_parsing	*nelem;
	char		*str;
	t_parsing	*tmp;

	str = ft_strdup("");
	if (str == NULL)
		return (1);
	nelem = ft_lstnew_parsing(str, ARG);
	if (nelem == NULL)
		return (1);
	if (replace_content_elem(split, nelem))
		return (free(nelem), 1);
	tmp = (*elem)->next;
	(*elem)->next = nelem;
	nelem->prev = (*elem);
	nelem->next = tmp;
	*elem = tmp;
	return (0);
}

static char	replace_content(t_expand *split[], t_parsing *elem)
{
	int			i;

	if (replace_content_elem(split[1], elem))
		return (1);
	i = 1;
	while (split[i])
	{
		if (create_elem_replace_content(split[i], &elem))
			return (1);
		i++;
	}
	return (0);
}

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
	ft_printf_fd(2, "TODO : Expanding redirection : %s (in src/parser/parser_env.c)\n", elem->content);
	return (0);
}

static int	expand_argument(t_parsing *elem, t_env envp)
{
	/*
	t_expand	*split;
	char		*content;

	if (!split_quotes(&split, elem->content))
		return (EXIT_FAILURE);
	if (!expand_var(&split, envp))
		return (EXIT_FAILURE);
	if (!split_fields(&split))
		return (EXIT_FAILURE);
	if (!expand_wildcards(&split))
		return (EXIT_FAILURE);
	if (!replace_content(&split, elem))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	*/
	(void) elem;
	(void) envp;
	ft_printf_fd(2, "TODO : Expanding argument : %s (in src/parser/parser_env.c)\n", elem->content);
	return (0);
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
