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

static size_t ft_cnt_tokens(const char *line)
{
    int		index;
    size_t	cnt_tokens;
	char	quote_type;

	index = 0;
	cnt_tokens = 0;
    while (line[index])
    {
        while(line[index] && ft_isspace(line[index]))
            index++;
        if (line[index])
        {
			cnt_tokens++;
			if(ft_isquot(line[index]))
			{
				quote_type = line[index++];
				while (line[index] && line[index] != quote_type)
					index++;
			}
			if (line[index] == quote_type)
				index++; // end quote
			else
				while (line[index] && !ft_isspace(line[index]) 
				&& !ft_isquot(line[index]))
					index++;	
        }
    }
    return (cnt_tokens);
}

// This function iterates through the string, counting tokens separated by whitespace.
static char	**filltkn_array(char **token_array, const char *line)
{
	int i = 0;
	int	j = 0;
	int k = 0;
	int token_len;
	char quote_char;

	while (line[k])
	{
		while(line[k] && ft_isspace(line[k]))
			k++;
		if (!line[k])
			break;
		j = k;
		if (ft_isquot(line[j]))
		{
			quote_char = line[j];
			k++;
			while (line[k] && line[k] != quote_char)
				k++;
			if (line[k] == quote_char)
				k++;
			token_len = k - j;
			token_array[i] = malloc(sizeof(char) * (token_len + 1));
			if (!token_array[i])
				return (free_all(token_array, i));
			strncpy(token_array[i], &line[j], token_len);
			token_array[i][token_len] = '\0';
		}
		else
		{
			while(line[k] && !ft_isspace(line[k]) && !ft_isquot(line[k]))
				k++;
			token_len = k - j;
			token_array[i] = malloc(sizeof(char) * (token_len + 1));
			if (!token_array[i])
				return (free_all(token_array, i));
			strncpy(token_array[i], &line[j], token_len);
			token_array[i][token_len] = '\0';
		}
		i++;
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
