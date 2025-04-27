#include "../parser.h"

// char	*ft_append_segment(char *curr_new, const char *orig, int last_pos, int index)
// {
// 	char	*segment;
// 	char	*temp;
// 	int		len;

// 	len = index - last_pos;
// 	if (len <= 0)
// 		return (curr_new);
// 	segment = ft_substr(orig, last_pos, len);
// 	if (!segment)
// 		return (free(curr_new), NULL);
// 	temp = ft_strjoined(curr_new, segment);
// 	return (free(curr_new), free(segment), temp);
// }

// t_exp_res	*ft_append_env_value(t_exp_res *exp, char *process, t_env *env)
// {
// 	char	*var_name;
// 	char	*var_value;
// 	char	*temp;

// 	var_name = ft_build_variable_name(exp, process, exp->peak);
// 	// printf("here;2 --> %s\n", var_name);
// 	if (!var_name)
// 		return (exp);
// 	exp->chars_consumed = ft_strlen(process) + 1;
// 	var_value = ft_isvariablet_exist(env, var_name);
// 	// printf("vt_vaue;3 --> %s\n", var_value);
// 	if (var_value)
// 	{
// 		temp = ft_strjoined(exp->res_str, var_value);
// 		// printf("temp;4 --> %s\n", temp);
// 		free(exp->res_str);
// 		exp->res_str = temp;
// 	}
// 	return (exp);
// }
// t_exp_res	*ft_expenv(t_exp_res *exp, char *process, t_env *env, int index)
// {

// 	exp->peak = ft_peakahead(process[index + 1]);
// 	if (exp->peak == 1 || exp->peak == 3)
// 	{
// 		// printf("here;1\n");
// 		exp = ft_append_env_value(exp, &process[index + 1], env);
// 		// printf("%s\n", exp->res_str);
// 		// printf("out;\n");
// 	}
// 	return(exp);
// }

// t_exp_res *ft_process(t_exp_res *exp, t_proc *prc, t_env *env)
// {
// 	int j;
// 	char	*temp;
// 	char	signle_char_string[2];
	
// 	j = 0;
// 	while (prc->to_proc &&  prc->to_proc[j])
// 	{
// 		if (prc->to_proc[j] == '$' && prc->quote_char == '\"')
// 		{
// 			exp = ft_expenv(exp, prc->to_proc, env, j);
// 			printf("%c\n", prc->to_proc[j + exp->chars_consumed]);
// 			break ;
// 		}
// 		else if (prc->to_proc[j] == '$' && prc->quote_char == '\'')
// 		{
// 			temp = ft_strjoined(exp->res_str, prc->to_proc);
// 			free(exp->res_str);
// 			exp->res_str = temp;
// 			exp->chars_consumed = ft_strlen(prc->to_proc);
// 			break;
// 		}
// 		else
// 		{
// 			signle_char_string[0] = prc->to_proc[j];
// 			signle_char_string[1] = '\0';
// 			temp = ft_strjoined(exp->res_str, signle_char_string);
// 			free(exp->res_str);
// 			exp->res_str = temp;
// 			exp->chars_consumed++;
// 			j++;
// 		}
// 	}
// 	return (exp);
// }
// size_t	ft_len(const char *str, int start_index)
// {
// 	int		i;
// 	char	quote_char;

// 	if (!str || !str[start_index] || !ft_isquot(str[start_index]))
// 		return (0);
// 	quote_char = str[start_index];
// 	i = start_index + 1;
// 	while (str[i])
// 	{
// 		if (str[i] == quote_char)
// 			return ((i - start_index) + 1);
// 		i++;
// 	}
// 	return (0);	
// }

// char	*ft_build_expanded_string(const char *orig, t_env *env)
// {
// 	int		i;
// 	t_proc	prc;
// 	t_exp_res exp;
// 	int	len;

// 	i = 0;
// 	exp.res_str = ft_strdup("");
// 	if (!exp.res_str)
// 		return (NULL);
// 	prc.quote_char = '\0'; // to indecat no quots in ft_process
// 	prc.last_pos = 0;
// 	while (orig[i])
// 	{
// 		exp.chars_consumed = 0;
// 		if (ft_isquot(orig[i]))
// 		{
// 			exp.res_str = ft_append_segment(exp.res_str, orig, prc.last_pos, i);
// 			prc.quote_char = orig[i];
// 			len = ft_len(orig, i);
// 			if (len > 0)
// 			{
// 				prc.to_proc = ft_substr(orig, i, len);
// 				if (!prc.to_proc )
// 				return (free(exp.res_str), NULL);
// 				ft_process(&exp, &prc, env);
// 				if (!exp.res_str)
// 				return (NULL);
// 				// printf("%s\n", prc.to_proc);
// 				// printf("%s\n", exp.res_str);
// 				// printf("%d\n", exp.chars_consumed);
// 				i += exp.chars_consumed;
// 				prc.last_pos = i;
// 				free(prc.to_proc);
// 			}	
// 		}
// 		else if (orig[i] == '$')
// 		{
// 			exit(1);
// 		}
// 		else
// 			i++; //_________keep it here________-
// 	}
// 	return (ft_append_segment(exp.res_str, orig, prc.last_pos, i)); // append after
// }

// void	ft_expand(t_token **token, t_env *env)
// {
// 	char	*orig_value;
// 	char	*exp_value;

// 	if (!token|| !*token|| !(*token)->value)
// 		return ;
// 	orig_value = (*token)->value;
// 	exp_value = ft_build_expanded_string(orig_value, env);
// 	if (!exp_value)
// 	{
// 		exp_value = ft_strdup("");
// 		if (!exp_value)
// 		{
// 			free(orig_value);
// 			(*token)->value = NULL;
// 			return ;
// 		}
// 	}
// 	free(orig_value);
// 	(*token)->value = exp_value;
	
// }
