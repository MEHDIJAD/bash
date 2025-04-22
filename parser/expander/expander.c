#include "../parser.h"

int ft_alpha_quote(char *word)
{
	int		i;
	char	quote;
	int		at_quote;

	i = 0;
	at_quote = 0;
	while(word[i])
	{
		if (ft_isquot(word[i]))
		{
			quote = word[i];
			at_quote = 1;
		}
		else if (ft_isquot(word[i]) && at_quote == 1)
			break;
		i++;
	}
	if (quote == '\"' || at_quote == 0)
		return (1);
	return (0);
}
int ft_isexpandable(t_token *current)
{
	if (current->type == TOKEN_WORD && (ft_strchr(current->value, '$') 
		&& ft_alpha_quote(current->value)))
		return (1);
	return(0);     
}

int	ft_isbign_variable(char c)
{
	return((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c  == '_'));
}

int ft_ispt_variable(char c)
{
	return((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

int	ft_peakahead(char c)
{
	if (ft_isspace(c))
		return (0);
	else if (ft_isbign_variable(c))
	return (1);
	else if (c == '?')
		return (2);
	else if (c >= '0' && c <= '9')
		return (3);
	return (-1);
}

size_t	ft_vtsize(char *string, int j)
{
	size_t	size = 0;

	while (string[j] && ft_ispt_variable(string[j]))
	{
		size++;
		j++;
	}
	return (size);
}
char	*ft_build_variable_name(char *string, int *i, int peak)
{
	char		*vt_name;
	size_t		vt_size;
	size_t		j;
	int			k;

	if (peak == 3)
	{
		vt_name = malloc(2);
		if (!vt_name)
			return (NULL);
		vt_name[0] = string[0];
		vt_name[1] = '\0';
		*i += 2;
	}
	else if (peak == 1)
	{	
		j = 0;
		k = 0; 
		vt_size = ft_vtsize(string, j);
		if (vt_size == 0)
			return (ft_strdup(""));
		vt_name = malloc(sizeof(char) * (vt_size + 1));
		if (!vt_name)
			return (NULL);
		while (j < vt_size)
				vt_name[k++] = string[j++];
		vt_name[k] = '\0';
		*i += vt_size + 1;
	}
	return (vt_name);
}

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


char	ft_get_alpha_quote(char *word)
{
	int		i;
	char	quote;
	int		at_quote;

	i = 0;
	at_quote = 0;
	quote = '\0';
	while(word[i])
	{
		if (ft_isquot(word[i]))
		{
			quote = word[i];
			at_quote = 1;
		}
		else if (ft_isquot(word[i]) && at_quote == 1)
			break;
		i++;
	}
	return (quote);
}
void	ft_clean_up(t_token **token)
{
	char	alpha_quote;
	char	*new_string;
	int		i = 0;
	int		j = 0;
	size_t	len;

	if (!token || !*token || !(*token)->value)
		return;
	alpha_quote = ft_get_alpha_quote((*token)->value);
	if (!alpha_quote)
		return ;
	len = ft_strlen((*token)->value);
	new_string = malloc(sizeof(char) * (len + 1));
	if (!new_string)
		return ;
	while ((*token)->value[i])
	{
		if ((*token)->value[i] != alpha_quote)
			new_string[j++] = (*token)->value[i];
		i++;
	}
	new_string[j] = '\0';
	free((*token)->value);
	(*token)->value = new_string;
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