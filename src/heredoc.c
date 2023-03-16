#include "minishell.h"

static char	do_heredoc(t_parsing **tokens)
{
	char	*line;
	int		tube[2];
	char	*txt;
	char	*tmp;

	txt = ft_strdup("");
	if (pipe(tube) || txt == NULL)
		return (free(txt), 1);
	(*tokens)->fd = tube[0];
	*tokens = (*tokens)->next;
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			return (close(tube[0]), close(tube[1]), 1);
		if (ft_strcmp(line, (*tokens)->content) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(txt, line);
		free(txt);
		free(line);
		txt = tmp;
		if (txt == NULL)
			return (close(tube[1]), 1);
		tmp = ft_strjoin(txt, "\n");
		free(txt);
		txt = tmp;
		if (txt == NULL)
			return (close(tube[1]), 1);
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
			if (do_heredoc(&tokens))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}	
