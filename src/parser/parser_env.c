/* ************************************************************************** */
#include "parser.h"

static char	get_value_var(const char *var, char **env, char **value, int code)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && var[j] && env[i][j] != '=' && env[i][j] == var[j])
			j++;
		if (var[j] == '\0' && env[i][j] == '=')
		{
			*value = ft_strdup(&env[i][j + 1]);
			if (*value == NULL)
				return (1);
			return (0);
		}
		i++;
	}
	if (ft_strcmp(var, "?") == 0)
		*value = ft_itoa(code);
	else
		*value = ft_strdup("");
	if (*value == NULL)
		return (1);
	return (0);
}

static char	insert_value_var(char **content, char *value, int len_var, int i)
{
	char	*content_tail;
	char	*content_top;
	char	*tmp;

	content_tail = ft_strdup(&(*content)[i + len_var + 1]);
	if (content_tail == NULL)
		return (free(value), 1);
	(*content)[i] = '\0';
	content_top = ft_strdup(*content);
	if (content_top == NULL)
		return (free(content_tail), free(value), 1);
	free(*content);
	tmp = ft_strjoin(content_top, value);
	free(content_top);
	free(value);
	if (tmp == NULL)
		return (free(content_tail), 1);
	*content = ft_strjoin(tmp, content_tail);
	free(content_tail);
	free(tmp);
	if (*content == NULL)
		return (1);
	return (0);
}

static char	verif_var(char **var, char *content, int pos, int *len_var)
{
	int		i;
	char	*tmp;

	i = 1;
	if (var && *var)
	{
		while ((*var)[i] && (*var)[i] != '{')
			i++;
		if (**var == '{' && ((*var)[i] == '{' || content[pos + 1 + i] != '}'))
			return (syntax_error_near(*var), 2);
		if (**var == '{')
		{
			tmp = ft_strdup(&(*var)[1]);
			(*len_var)++;
		}
		else
		{
			(*var)[i] = '\0';
			tmp = ft_strdup(*var);
			(*len_var) = i;
		}
		free(*var);
		if (tmp == NULL)
			return (1);
		*var = tmp;
	}
	return (0);
}

static char	put_var_env_elem(char **content, char **env, int code, int start, int end)
{
	int		i;
	int		len_value;
	char	*var;
	char	*value;
	int		len_var;

	i = start;
	len_var = 0;
	while ((*content)[i] && i < end)
	{
		if ((*content)[i] == '$')
		{
			if (get_var_env_txt(&(*content)[i], &var))
				return (1);
			//printf("var:%s\n", var);
			if (var)
				len_var = ft_strlen(var);
			len_value = verif_var(&var, *content, i, &len_var);
			if (len_value)
				return (len_value);
			if (var)
			{
				if (get_value_var(var, env, &value, code))
					return (free(var), 1);
				len_value = ft_strlen(value);
				if (insert_value_var(content, value, len_var, i))
					return (free(var), 1);
				free(var);
				i += len_value - 1;
			}
		}
		i++;
	}
	return (0);
}
/*
static char	*get_str(char *str, int start, int end)
{
	char	*nstr;
	char	*tmp;

	nstr = ft_strdup(str + start);
	if (nstr == NULL)
		return (NULL);
	nstr[end] = '\0';
	tmp = nstr;
	nstr = ft_strdup(nstr);
	free(tmp);
	if (nstr == NULL)
		return (NULL);
	return (nstr);
}*/

char	put_var_env(t_parsing **list_parsing, char **env, int code)
{
	t_parsing	*elem;
	char		err;
	int			pos[3];
	char		*content;
	char		sep;

	elem = *list_parsing;
	while (elem)
	{
		pos[0] = 0;
		pos[1] = 0;
		//printf("type:%d, CMD:%d\n", elem->type, CMD);
		if (elem->type == CMD || elem->type == ARG)
		{
			sep = '\0';
			content = elem->content;
			while (content[pos[0]])
			{
				if (sep == '\0')
				{
					if (content[pos[0]] == '\"')
					{
						err = put_var_env_elem(&elem->content, env, code, pos[1], pos[0]);
						if (err)
							return (err);
						pos[1] = pos[0] + 1;
						sep = '\"';
					}
					else if (content[pos[0]] == '\'')
						sep = '\'';
				}
				else if (content[pos[0]] == '\'' || content[pos[0]] == '\"')
				{
					if (sep == '\"' && sep == content[pos[0]])
					{
						pos[2] = pos[0];
						err = put_var_env_elem(&elem->content, env, code, pos[1], pos[2]);
						if (err)
							return (err);
						sep = '\0';
					}	
				}
				pos[0]++;
			}
			err = put_var_env_elem(&elem->content, env, code, pos[1], pos[0]);
			if (err)
				return (err);
		}
		elem = elem->next;
	}
	return (0);
}

/*
   char	put_var_env(t_parsing **list_parsing, char **env, int code)
   {
   t_parsing	*elem;
   char		err;

   elem = *list_parsing;
   while (elem)
   {
   if (elem->type == CMD || elem->type == ARG)
   {
   err = put_var_env_elem(&elem->content, env, code);
   if (err)
   return (err);
   }
   elem = elem->next;
   }
   return (0);
   }*/
