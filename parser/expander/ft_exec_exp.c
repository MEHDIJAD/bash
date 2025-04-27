#include "../parser.h"

char	*append_single_char(char *new_str,char c)
{
	char	*temp;
	char	signel_char_string[2];

	signel_char_string[0] = c;
	signel_char_string[1] = '\0';
	temp = ft_strjoined(new_str, signel_char_string);
	free(new_str);
	new_str = temp;
	return (new_str);
}

char	*ft_expenv( char *new_str, const char *orign, t_env *env, int *i)
{
	int peak = ft_peakahead(orign[*i + 1]);
	
	(void)new_str, (void)orign, (void)env;
	
	return (new_str);

}
char *ft_build_expanded_string(const char *orign, t_env *env)
{
	int		i;
	char	quote_char;
	char	*new_str;

	(void)env; //!_________LOOK
	new_str = ft_strdup("");
	i = 0;
	quote_char = '\0';
	while (orign && orign[i])
	{
		if (ft_isquot(orign[i]) && !quote_char)
		{
			quote_char = orign[i];
			new_str = append_single_char(new_str, orign[i++]);
		}
		else if (orign[i] == '$' && orign[i + 1] && (quote_char == '\"' || !quote_char))
		{
			new_str = ft_expenv( new_str, &orign[i], env, &i);
		}
		else
			new_str = append_single_char(new_str, orign[i++]);
	}
	return (new_str);
}

void	ft_expand(t_token **token, t_env *env)
{
	char	*orig_value;
	char	*exp_value;

	if (!token|| !*token|| !(*token)->value)
		return ;
	orig_value = (*token)->value;
	exp_value = ft_build_expanded_string(orig_value, env);
	if (!exp_value)
	{
		exp_value = ft_strdup("");
		if (!exp_value)
		{
			free(orig_value);
			(*token)->value = NULL;
			return ;
		}
	}
	free(orig_value);
	(*token)->value = exp_value;
	
}