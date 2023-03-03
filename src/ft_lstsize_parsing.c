#include "minishell.h"

int	ft_lstsize_parsing(t_parsing *tokens)
{
	int	size;

	size = 0;
	while (tokens)
	{
		size++;
		tokens = tokens->next;
	}
	return (size);
}
