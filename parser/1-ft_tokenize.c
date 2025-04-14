#include "parser.h"

// size_t ft_count_tokens(char *line)
// {
//     int index = 0;
//     size_t cnt_tokens = 0;

//     while (line[index])
//     {
//         while(line[index] && ft_isspace(line[index]))
//             index++;
//         if (line[index])
//         {
//             cnt_tokens++;
//             while (line[index] && !ft_isspace(line[index]))
//                 index++;   
//         }
//     }
//     return (cnt_tokens);
    
// }

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

    if (!line)
        return (NULL);
    tkn_array = ft_split_whitespace(line);
    if (!tkn_array)
        return (NULL);
    while (tkn_array[i])
    {
        t_token_type type = ft_token_type(tkn_array[i]);
        new_node = ft_token_new(tkn_array[i], type);
        if (!new_node)
        {
            free(tkn_array);
            // ft_token_clear(&head); //! w need to add; it is like ft_lstclear
            return (NULL);
        }
        ft_token_add_back(&head, new_node);
        i++;
    }
    free(tkn_array);
    tkn_array = NULL;
    return (head); 
}