#include "../parser.h"

// int	ft_isspecial_char() // add char c  //!
// {
// 	return (0);
// }

char	*ft_append_segemnt(char *curr_new, const char *orig, int last_pos, int index)
{
	char	*segment;
	char	*temp;
	int		len;

	len = index - last_pos;
	if (len <= 0)
		return (curr_new);
	segment = ft_substr(orig, last_pos, len);
	if (!segment)
		return (free(curr_new), NULL);
	temp = ft_strjoined(curr_new, segment);
	return (free(curr_new), free(segment), temp);
}

char	*ft_append_vn(char *new_str, char *orig, int peak)
{
	if (peak == 1)
		new_str = ft_append_env_value();
}
char	*ft_build_expanded_string(const char *orig, t_env *env)
{
	int		i;
	int		last_pos;
	char	*new_str;
	char	next_char;
	int		peak;

	i = 0;
	last_pos = 0;
	(void)env;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (orig[i])
	{
		if (orig[i] == '$' && orig[i + 1])
		{
			new_str = ft_append_segemnt(new_str, orig, last_pos, i);
			if (!new_str)
				return (NULL);
			next_char = orig[i + 1];
			if (ft_isquot(next_char))
			{
				i += 1;
				last_pos = i;
			}
			else if (ft_isbign_variable(next_char) || ft_isdigit(next_char))
			{
				peak = ft_peakahead(next_char);
				new_str = ft_append_vn(new_str, orig, peak);

				// take part of $ inside of a quote --> if double quotes expand 
			}
		}
		i++;
	}
	new_str = ft_append_segemnt(new_str, orig, last_pos, i);
	if (!new_str)
		return (NULL);
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
