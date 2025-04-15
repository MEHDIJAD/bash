#include "parser.h"

#include "parser.h"

t_token_type ft_token_type(char *token)
{
    if (strcmp(token, "|") == 0)
        return (TOKEN_PIPE);
    else if (strcmp(token, "<") == 0)
        return (TOKEN_REDIR_IN);
    else if (strcmp(token, ">") == 0)
        return (TOKEN_REDIR_OUT);
    else if (strcmp(token, ">>") == 0)
        return (TOKEN_REDIR_APPEND);
    else if (strcmp(token, "<<") == 0)
        return (TOKEN_REDIR_HEREDOC);
    else
        return (TOKEN_WORD);
}
t_token *ft_tokenize(char *line)
{
    size_t i = 0;
    char **tkn_array = NULL;
    t_token *head = NULL;
    t_token *new_node = NULL;
    t_token_type type;

    if (!line)
        return (NULL);
    tkn_array = ft_split_tokens(line);
    if (!tkn_array)
        return (NULL);
    while (tkn_array[i])
    {
        type = ft_token_type(tkn_array[i]);
        new_node = ft_token_new(tkn_array[i], type);
        if (!new_node)
            return (free(tkn_array), ft_token_clear(&head), NULL);
        ft_token_add_back(&head, new_node);
        i++;
    }
    free(tkn_array);
    tkn_array = NULL;
    return (head); 
}
