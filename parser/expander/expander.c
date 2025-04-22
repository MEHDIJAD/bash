#include "../parser.h"

void	ft_expander(t_token **token, t_env *env)
{
	t_token *current;

	current = *token;
	while (current)
	{
		if (ft_isexpandable(current))
		{
			if (current->value[0] == '$' && current->next)
			{
				if (current->next->value[0] == '\''
					|| current->next->value[0] == '\"')
				{
					free(current->value);
					current->value = ft_strdup("");
				}
			}
			ft_expand(&current, env);
		}
		ft_clean_up(&current);
		current = current->next;
	}
}
