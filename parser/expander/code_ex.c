#include "../parser.h"

// int	ft_isspecial_char() // add char c  //!
// {
// 	return (0);
// }

typedef struct s_proc
{
	char	*to_proc;
	char	quote_char;
	int		last_pos;
}	t_proc;

char	*ft_append_segment(char *curr_new, const char *orig, int last_pos, int index)
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


char	*ft_process(char *new_str, t_proc *prc, t_env *env)
{
	/*
		1- parse prcess 

	*/
	int j;
	char	*temp;

	(void)env;
	(void)new_str;
	j = 0;
	while (prc->to_proc[j])
	{
		if (prc->to_proc[j] == '$' && prc->quote_char == '\"')
		{
			// expand

			return (NULL);
			j++;
			
		}
		else if (prc->to_proc[j] == '$' && prc->quote_char == '\'')
		{
			temp = ft_strjoined(new_str, prc->to_proc);
			free(new_str);
			new_str = temp;
			break ;
		}
		j++;
	}
	return (new_str);
}
size_t	ft_len(const char *str, int start_index)
{
	int		i;
	char	quote_char;

	if (!str || !str[start_index] || !ft_isquot(str[start_index]))
		return (0);
	quote_char = str[start_index];
	i = start_index + 1;
	while (str[i])
	{
		if (str[i] == quote_char)
			return ((i - start_index) + 1);
		i++;
	}
	return (0);	
}
char	*ft_build_expanded_string(const char *orig, t_env *env)
{
	int		i;
	char	*new_str;
	t_proc	prc;
	size_t	len;

	i = 0;
	(void)env;
	new_str = ft_strdup("");
	prc.quote_char = '\0'; // to indecat no quots in ft_process
	prc.last_pos = 0;
	if (!new_str)
		return (NULL);
	while (orig[i])
	{
		if (ft_isquot(orig[i]))
		{
			new_str = ft_append_segment(new_str, orig, prc.last_pos, i);
			prc.quote_char = orig[i];
			// printf("%c\n", prc.quote_char);
			len = ft_len(orig, i);
			// printf("%zu\n", len);
			if (len > 0)
			{
				prc.to_proc = ft_substr(orig, i, len);
				// printf("prc: %s\n", prc.to_proc);
				if (!prc.to_proc )
				return (free(new_str), NULL);
				new_str = ft_process(new_str, &prc , env);
				if (!new_str)
					return (NULL);
				i += len;
				prc.last_pos = i;
			}	
		}
		// else if (orig[i] == '$')
		// {
		// 	// apend segement
		// 	/* 
		// 		1- look at (i + 1)char:
		// 		if quote advance i++ and last_p
		// 		else if big pf vt or digit process
		// 	*/
			
		// }
		else
		{
			i++;
		}
	}
	return (ft_append_segment(new_str, orig, prc.last_pos, i)); // append after
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
