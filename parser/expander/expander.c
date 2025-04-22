#include "../parser.h"

char	*ft_ckeckvt_exist(t_env *env, char *variable_name)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->name, variable_name) == 0)
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
}

void	ft_expand(t_token **current, t_env *env)
{
	int		i;
	int		peak;
	char	*variable_name;
	char	*new_string;
	char	*value;
	char	*temp;
	char	*segment;
	int		last_pos = 0;

	i = 0;
	new_string = ft_strdup("");

	while ((*current)->value[i])
	{
		if ((*current)->value[i] == '$' && (*current)->value[i + 1])
		{
			if (i > last_pos)
			{
				// ft_segment();
				segment =  ft_substr((*current)->value, last_pos, i - last_pos);
				temp = ft_strjoined(new_string, segment);
				free(new_string);
				free(segment);
				new_string = temp;
			}
			peak = ft_peakahead((*current)->value[i + 1]);
			if (peak == -1)
				return ;
			else if (peak == 1)
			{
				//ft_env_variable();
				variable_name =  ft_build_variable_name(&(*current)->value[i + 1], &i, peak);
				if ((value = ft_ckeckvt_exist(env, variable_name)))
				{
					temp = ft_strjoined(new_string, value);
					free(new_string);
					new_string = temp;
				}
				free(variable_name);
				free(value);
				last_pos = i;
				continue;
			}
			else if (peak == 2)
			{
				i += 2;
				continue;
				
			}
			else if (peak == 3)
			{
				// ft_env_digit();
				variable_name =  ft_build_variable_name(&(*current)->value[i + 1], &i, peak);
				if ((value = ft_ckeckvt_exist(env, variable_name)))
				{
					temp = ft_strjoined(new_string, value);
					free(new_string);
					free(value);
					new_string = temp;
				}
				free(variable_name);
				last_pos = i;
				continue;
			}

		}
		i++;
	}
	if (last_pos < (int)ft_strlen((*current)->value))
	{
		segment =  ft_substr((*current)->value, last_pos, i - last_pos);
		temp = ft_strjoined(new_string, segment);
		free(new_string);
		free(segment);
		new_string = temp;
	}
	free((*current)->value);
	(*current)->value = new_string;
}

void	ft_expander(t_token **token, t_env *env)
{
	t_token *current;

	current = *token;
	(void)env;
	while (current)
	{
		if (ft_isexpandable(current))
		{
			ft_expand(&current, env);
		}
		ft_clean_up(&current);
		current = current->next;
	}
}