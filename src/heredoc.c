#include "minishell.h"

static int	get_nb_heredoc(t_parsing *tokens)
{
	int	nb;

	nb = 0;
	while (tokens)
	{
		if (tokens->type == R_DINPUT)
			nb++;
		tokens = tokens->next;
	}
	return (nb);
}

static char	do_heredoc(t_parsing **tokens, int *heredocs)
{
	char	*line;
	int		tube[2];
	char	*txt;
	char	*tmp;

	txt = ft_strdup("");
	if (pipe(tube) || txt == NULL)
		return (1);
	*heredocs = tube[0];
	*tokens = (*tokens)->next;
	while (1)
	{
		line = readline(">");
		if (!line)
			return (close(tube[0]), close(tube[1]), 1);
		if (ft_strcmp(line, (*tokens)->content) == 0)
			break ;
		tmp = ft_strjoin(txt, line);
		free(txt);
		free(line);
		txt = tmp;
	}
	write(tube[1], txt, ft_strlen(txt));
	free(txt);
	close(tube[1]);
	return (0);
}

int	*ft_heredoc(t_parsing *tokens)
{
	int	nb;
	int	*heredocs;
	int	i;

	nb = get_nb_heredoc(tokens);
	heredocs = malloc(sizeof(int) * (nb + 1));
	if (heredocs == NULL)
		return (NULL);
	heredocs[nb] = -1;
	i = 0;
	while (tokens)
	{
		if (tokens->type == R_DINPUT)
		{
			if (do_heredoc(&tokens, &heredocs[i]))
				return (free(heredocs), NULL);
		}
		tokens = tokens->next;
	}
	return (heredocs);
}	
