#include "../parser.h"

// int ft_alpha_quote(char *word)
// {
// 	int		i;
// 	char	quote;
// 	int		at_quote;
// 	int		dollar_flag;

// 	i = 0;
// 	at_quote = 0;
// 	dollar_flag = 0;
// 	while(word[i])
// 	{
// 		if (word[i] == '$')
// 			dollar_flag = 1;
// 		if (ft_isquot(word[i]))
// 		{
// 			quote = word[i];
// 			at_quote = 1;
// 		}
// 		else if (ft_isquot(word[i]) && at_quote == 1)
// 			break;
// 		i++;
// 	}
// 	if (quote == '\"' && dollar_flag)
// 		return (1);
// 	return (0);
// }
// int ft_isexpandable(t_token *current)
// {
// 	if (current->type == TOKEN_WORD && ft_strchr(current->value, '$'))
// 		return (1);
// 	return(0);     
// }


// int	ft_peakahead(char c)
// {
// 	if (ft_isspace(c))
// 		return (0);
// 	else if (c == '$')
// 		return (1);
// 	return (0);
// }


// void	ft_expand(t_token **current, t_env *env)
// {
	
	
// }

// void	ft_expander(t_token **token, t_env *env)
// {
// 	t_token *current;

// 	current = *token;
// 	(void)env;
// 	while (current)
// 	{
// 		if (ft_isexpandable(current))
// 		{
// 			ft_expand(&current, env);
// 		}
// 		current = current->next;
// 	}
// }