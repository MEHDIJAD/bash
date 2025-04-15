#include "parser.h"

static char **free_all(char **tkn_array, int i)
{
	while (i >= 0)
	{
		free(tkn_array[i]);
		i--;
	}
	free(tkn_array);
	return (NULL);
}

static void skip_token(const char *line, int *i)
{
	char quote;
	if (ft_isquot(line[*i]))
	{
		quote = line[*i];
		(*i)++;
		while(line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
	}
	else
		while (line[*i] && !ft_isspace(line[*i]) 
				&& !ft_isquot(line[*i]))
					(*i)++;
}
static size_t ft_cnt_tokens(const char *line)
{
    int		index;
    size_t	cnt_tokens;

	index = 0;
	cnt_tokens = 0;
    while (line[index])
    {
    	while(line[index] && ft_isspace(line[index]))
			index++;
		if (line[index])
		{
			cnt_tokens++;
			skip_token(line, &index);
		}
    }
    return (cnt_tokens);
}

static char *extract_token(const char *line, int *k)
{
	int		j;
	int		token_len;
	char	*token_str;
	char	quote_char;

	j = *k;
	if (ft_isquot(line[j]))
	{
		quote_char = line[j];
		(*k)++;
		while (line[*k] && line[*k] != quote_char)
			(*k)++;
		if (line[*k] == quote_char)
			(*k)++;
	}
	else
		while(line[*k] && !ft_isspace(line[*k]) && !ft_isquot(line[*k]))
					(*k)++;
	token_len = *k - j;
	token_str = malloc(sizeof(char) *(token_len + 1));
	if (!token_str)
		return (NULL);
	ft_strncpy(token_str, &line[j], token_len);
	token_str[token_len] = '\0';
	return (token_str);
}

static char	**filltkn_array(char **token_array, const char *line)
{
	int i = 0;
	int k = 0;

	i = 0;
	k = 0;
	while(line[k])
	{
		while(line[k] && ft_isspace(line[k]))
			k++;
		if (line[k])
		{
			token_array[i] = extract_token(line, &k);
			if (!token_array[i])
				free_all(token_array, i - 1);
			i++;
		}
	}
	token_array[i] = NULL;
	return (token_array);
}
char	**ft_split_tokens(const char *line)
{
	size_t	cnt = ft_cnt_tokens(line);
	char	**tkn_array;

	tkn_array = malloc(sizeof(char *) * (cnt + 1));
	if (!tkn_array)
		return (NULL);
	if (!filltkn_array(tkn_array, line))
		return (NULL);
	return (tkn_array);
}
