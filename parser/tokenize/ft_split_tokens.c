/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:17:32 by eel-garo          #+#    #+#             */
/*   Updated: 2025/04/25 13:18:16 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../parser.h"

// static void	skip_token(const char *line, int *i)
// {
// 	char	quote;

// 	if (ft_isquot(line[*i]))
// 	{
// 		quote = line[*i];
// 		(*i)++;
// 		while (line[*i] && line[*i] != quote)
// 			(*i)++;
// 		if (line[*i] == quote)
// 			(*i)++;
// 	}
// 	else if (ft_isoperater(line[*i]))
// 	{
// 		if (ft_isdouble_op(line, *i))
// 			*i += 2;
// 		else
// 			(*i)++;
// 	}
// 	else
// 		ft_advance_word_token(line, i);
// }

// static size_t	ft_cnt_tokens(const char *line)
// {
// 	int		index;
// 	size_t	cnt_tokens;

// 	index = 0;
// 	cnt_tokens = 0;
// 	while (line[index])
// 	{
// 		while (line[index] && ft_isspace(line[index]))
// 			index++;
// 		if (line[index])
// 		{
// 			cnt_tokens++;
// 			skip_token(line, &index);
// 		}
// 	}
// 	return (cnt_tokens);
// }

// static char	*extract_token(const char *line, int *k)
// {
// 	int		j;
// 	int		token_len;
// 	char	quote_char;

// 	j = *k;
// 	if (ft_isquot(line[j]))
// 	{
// 		quote_char = line[(*k)++];
// 		while (line[*k] && line[*k] != quote_char)
// 			(*k)++;
// 		if (line[*k] == quote_char)
// 			(*k)++;
// 	}
// 	else if (ft_isoperater(line[j]))
// 		*k += 1 + ft_isdouble_op(line, j);
// 	else
// 		ft_advance_word_token(line, k);
// 	token_len = *k - j;
// 	if (token_len <= 0) // Handle cases like "" or potential errors
// 		token_len = 0; // Ensure non-negative length for malloc
// 	return (ft_alloc_token(token_len, j, line));
// }

// static char	**filltkn_array(char **token_array, const char *line)
// {
// 	int	i;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (line[k])
// 	{
// 		while (line[k] && ft_isspace(line[k]))
// 			k++;
// 		if (line[k])
// 		{
// 			token_array[i] = extract_token(line, &k);
// 			if (!token_array[i])
// 				free_all(token_array, i - 1);
// 			i++;
// 		}
// 	}
// 	token_array[i] = NULL;
// 	return (token_array);
// }

// char	**ft_split_tokens(const char *line)
// {
// 	size_t	cnt;
// 	char	**tkn_array;

// 	cnt = ft_cnt_tokens(line);
// 	printf("%zu\n", cnt);
// 	tkn_array = malloc(sizeof(char *) * (cnt + 1));
// 	if (!tkn_array)
// 		return (NULL);
// 	if (!filltkn_array(tkn_array, line))
// 		return (NULL);
// 	return (tkn_array);
// }

#include "../parser.h" // Assuming necessary headers are included
#include <stdlib.h>   // For malloc, free
#include <string.h>   // For strlcpy/strncpy if used

// --- Keep helper functions like: ---
// ft_isquot, ft_isoperater, ft_isdouble_op, ft_isspace
// free_all, ft_alloc_token (maybe needs ft_strlcpy)

// --- Remove or drastically simplify ft_advance_word_token ---
// It's not really needed if the main loop handles logic correctly.

// --- ft_cnt_tokens and filltkn_array need rethinking ---

static size_t ft_get_token_len(const char *line, int *k)
{
    int start = *k;
    char quote;

    // Handle Operator Tokens first (if they start the token)
    if (ft_isoperater(line[*k]))
    {
        *k += 1 + ft_isdouble_op(line, *k); // Advance past operator
        return (*k - start); // Return operator length (1 or 2)
    }

    // Handle Word/Quoted Tokens
    while (line[*k])
    {
        if (ft_isquot(line[*k]))
        {
            quote = line[*k];
            (*k)++; // Move past opening quote
            while (line[*k] && line[*k] != quote)
                (*k)++; // Move through quoted content
            if (line[*k] == quote)
                (*k)++; // Move past closing quote
            // Continue loop to check for adjacent parts like "word"'another'
        }
        else if (ft_isoperater(line[*k]) || ft_isspace(line[*k]))
        {
            break; // Stop token at unquoted operator or space
        }
        else
        {
            (*k)++; // Advance for normal character
        }
    }
    return (*k - start); // Return length of the complex token
}


static size_t	ft_count_tokens_revised(const char *line)
{
	int		k;
	size_t	cnt_tokens;
    size_t  len;

	k = 0;
	cnt_tokens = 0;
	while (line[k])
	{
		while (line[k] && ft_isspace(line[k])) // Skip whitespace BETWEEN tokens
			k++;
		if (line[k]) // Found start of a potential token
		{
            len = ft_get_token_len(line, &k); // Use revised logic to find end
            if (len > 0) // Check if a token was actually found
			    cnt_tokens++;
            // k is already advanced by ft_get_token_len
		}
	}
	return (cnt_tokens);
}

// Assumes ft_alloc_token correctly allocates based on length and copies
char	*ft_alloc_token(int token_len, int start_index, const char *line)
{
	char	*token_str;

	if (token_len <= 0) // Prevent zero or negative allocation
        return ft_strdup(""); // Return empty string for zero length

	token_str = malloc(sizeof(char) * (token_len + 1));
	if (!token_str)
		return (NULL);
    // Use strlcpy if available for safety, otherwise careful strncpy
	ft_strncpy(token_str, &line[start_index], token_len); // Assuming ft_strncpy exists
	token_str[token_len] = '\0';
	return (token_str);
}


static char	**filltkn_array_revised(char **token_array, const char *line)
{
	int	i; // Index for token_array
	int	k; // Index for line
    int token_start;
    size_t token_len;

	i = 0;
	k = 0;
	while (line[k])
	{
		while (line[k] && ft_isspace(line[k])) // Skip whitespace
			k++;

		if (line[k]) // If not end of line after skipping whitespace
		{
            token_start = k; // Mark start of token
            token_len = ft_get_token_len(line, &k); // Find length, advances k

            if (token_len > 0) // Should always be > 0 if line[k] was true
            {
			    token_array[i] = ft_alloc_token(token_len, token_start, line);
			    if (!token_array[i])
				    return (free_all(token_array, i)); // Use i, not i-1 on failure
			    i++;
            }
            // k is already advanced to the start of the next token or whitespace
		}
	}
	token_array[i] = NULL; // Null-terminate the array
	return (token_array);
}

// Main function uses the revised helpers
char	**ft_split_tokens(const char *line)
{
	size_t	cnt;
	char	**tkn_array;

    if (!line) return NULL; // Handle NULL input

	cnt = ft_count_tokens_revised(line);
	tkn_array = malloc(sizeof(char *) * (cnt + 1));
	if (!tkn_array)
		return (NULL);

	// Pass the allocated array to be filled
	if (!filltkn_array_revised(tkn_array, line))
    {
        // filltkn_array_revised already handles freeing on error
		return (NULL);
    }

	return (tkn_array);
}

// --- Make sure these helpers are correctly defined ---
// int ft_isquot(int c);
// int ft_isoperater(int c);
// int ft_isdouble_op(const char *line, int k);
// int ft_isspace(int c);
// char **free_all(char **tkn_array, int i); // Should free from i down to 0
// void ft_strncpy(char *dst, const char *src, size_t n); // Or use standard strncpy/strlcpy
// char *ft_strdup(const char *s1); // Standard or custom strdup
