/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:52:00 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/09 16:26:28 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static void print_id_tab(char *id_tab)
{
	printf("id_tab:[");
	while (*id_tab != -1)
	{
		printf(" %d,", *id_tab);
		id_tab++;
	}
	printf("]\n");
}

static char	identify_type_char(char c)
{
	if (c == ' ')
		return (SPACE);
	if (c == 39)
		return (S_QUOTE);
	if (c == '"')
		return (D_QUOTE);
	if (c == '$')
		return (DOLLAR);
	if (c == '|')
		return (PIPE_C);
	if (c == '<' || c == '>')
		return (REDIRECT);
	return (ALPHA_NUM);
}

static char	get_id_cmd(char *cmd, char **id_tab)
{
	int	size;
	int	i;

	size = ft_strlen(cmd);
	*id_tab = malloc(size + 1);
	if (!*id_tab)
		return (1);
	(*id_tab)[size] = -1;
	i = 0;
	while (i < size)
	{
		(*id_tab)[i] = identify_type_char(cmd[i]);
		i++;
	}
	return (0);
}

static char	get_elem_txt(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
	int		size;
	char	*elem;
	int		j;
	t_parsing	*node;

	size = 0;
	while (id_tab[*i] != -1  && (id_tab[*i] == ALPHA_NUM || id_tab[*i] == DOLLAR))
	{
		size++;
		(*i)++;
	}
	if (!size)
		return (0);
	*i -= size;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (j < size)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	node = ft_lstnew_parsing(elem, TXT);
	if (!node)
		return (1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

static char	second_quote(char *id_tab, int *i)
{
	char	quote;
	int		j;

	j = *i;
	if (id_tab[j] == S_QUOTE)
		quote = S_QUOTE;
	else if (id_tab[j] == D_QUOTE)
		quote = D_QUOTE;
	else
		return (-1);
	j++;
	while (id_tab[j] != -1 && id_tab[j] != quote)
		j++;
	if (id_tab[j] != quote)
		return (0);
	return (quote);
}

static char get_elem_quoted(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
	int     size;
	char    *elem;
	int     j;
	t_parsing   *node;
	char	quote;

	quote = second_quote(id_tab, i);
	if (!quote)
	{
		id_tab[*i] = ALPHA_NUM;
		return (0);
	}
	if (quote == -1)
		return (0);
	size = 0;
	(*i)++;
	while (id_tab[*i] != -1 && id_tab[*i] != quote)
	{
		size++;
		(*i)++;
	}
	(*i)++;
	if (!size)
		return (0);
	*i -= size + 1;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (id_tab[*i] != -1 && id_tab[*i] != quote)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	if (quote == S_QUOTE)
		node = ft_lstnew_parsing(elem, TXT_S);
	else
		node = ft_lstnew_parsing(elem, TXT_D);
	if (!node)
		return (1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

static char	get_space(char *id_tab, int *i, t_parsing **list_parsing)
{
	int	size;
	t_parsing	*node;

	size = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == SPACE)
	{
		size++;
		(*i)++;
	}
	if (size)
	{
		node = ft_lstnew_parsing(" ", SPACE_TMP);
		if (!node)
			return (1);
		ft_lstadd_back_parsing(list_parsing, node);
	}
	return (0);
}

static char get_pipe(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
	int     size;
	char    *elem;
	int     j;
	t_parsing   *node;

	size = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == PIPE_C)
	{
		size++;
		(*i)++;
	}
	if (!size)
		return (0);
	*i -= size;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == PIPE_C)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	node = ft_lstnew_parsing(elem, PIPE);
	if (!node)
		return (1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

static char get_redirect(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
    int     size;
    char    *elem;
    int     j;
    t_parsing   *node;

    size = 0;
    while (id_tab[*i] != -1 && id_tab[*i] == REDIRECT)
    {
        size++;
        (*i)++;
    }
    if (!size)
        return (0);
    *i -= size;
    elem = malloc(size + 1);
    if (!elem)
        return (1);
    elem[size] = 0;
    j = 0;
    while (id_tab[*i] != -1 && id_tab[*i] == REDIRECT)
    {
        elem[j] = cmd[*i];
        (*i)++;
        j++;
    }
    node = ft_lstnew_parsing(elem, REDIRECT_TMP);
    if (!node)
        return (1);
    ft_lstadd_back_parsing(list_parsing, node);
    return (0);
}

static char	get_list_parsing(char *cmd, char *id_tab, t_parsing **list_parsing)
{
	int			size;
	int			i;

	size = ft_strlen(cmd);
	i = 0;
	*list_parsing = NULL;
	while (i < size)
	{
		if (get_elem_txt(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_space(id_tab, &i, list_parsing))
			return (1);
		if (get_elem_quoted(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_pipe(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_redirect(cmd, id_tab, &i, list_parsing))
			return (1);
	}
	return (0);
}

static char	*get_name_id_elem(char id)
{
	char	*txt;

	if (id == CMD)
		txt = "CMD";
	else if (id == ARG)
		txt = "ARG";
	else if (id == PIPE)
		txt = "PIPE";
	else if (id == R_INPUT)
		txt = "R_INPUT";
	else if (id == R_OUTPUT)
        txt = "R_outPUT";
	else if (id == R_DINPUT)
        txt = "R_DINPUT";
	else if (id == R_DOUTPUT)
        txt = "R_DOUTPUT";
	else if (id == REDIRECT_TMP)
        txt = "REDIRECT_TMP";
	else if (id == SPACE_TMP)
        txt = "SPACE_TMP";
	else if (id == TXT)
        txt = "TXT";
	else if (id == TXT_S)
        txt = "TXT_S";
	else if (id == TXT_D)
        txt = "TXT_D";
	else
        txt = "UNKWOWN";
	return (ft_strdup(txt));
}

void	print_list_parsing(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		printf("[%s]-> %s\n",
			get_name_id_elem(list_parsing->type), list_parsing->content);
		list_parsing = list_parsing->next;
	}
}

char	parser(char *cmd, t_parsing **list_parsing, char **env)
{
	char		*id_tab;

	if (!cmd)
		return (1);
	//cmd[ft_strlen(cmd) - 1] = 0;
	cmd = ft_strtrim(cmd, " \n");
	if (!cmd)
		return (2);
	printf("cmd apres trim:%s$\n", cmd);
	if (get_id_cmd(cmd, &id_tab))
		return (2);
	print_id_tab(id_tab);
	if (get_list_parsing(cmd, id_tab, list_parsing))
		return (2);
	print_list_parsing(*list_parsing);
	if (put_var_env(list_parsing, env))
		return (2);
	printf("****VAR ENV ADDED****\n");
	print_list_parsing(*list_parsing);
	return (0);
}
