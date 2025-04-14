// // 1-ft_tokenize.c 

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

// t_token_type ft_token_type(char *token)
// {
//     if (strcmp(token, "|") == 0)
//         return (TOKEN_PIPE);
//     else if (strcmp(token, "<") == 0)
//         return (TOKEN_REDIR_IN);
//     else if (strcmp(token, ">") == 0)
//         return (TOKEN_REDIR_OUT);
//     else if (strcmp(token, ">>") == 0)
//         return (TOKEN_REDIR_APPEND);
//     else if (strcmp(token, "<<") == 0)
//         return (TOKEN_REDIR_HEREDOC);
//     else
//         return (TOKEN_WORD);
// }
// void    ft_tokenize(char *line)
// {
//     size_t i;
//     size_t cnt_tokens;
//     char **tkn;
//     t_token **tokens;

//     tokens = NULL;
//     cnt_tokens = ft_count_tokens(line);
//     // printf("Number_tokens: %ld\n", cnt_tokens);
//     tkn = malloc(sizeof(char *) * cnt_tokens);
//     tkn = ft_split_whitespace(line);
//     // for(i = 0; i < cnt_tokens; i++){
//     //     printf("tkn[%zu] = [%s]\n", i, tkn[i]);
//     // }
//     i = 0;
//     while (i < cnt_tokens)
//     {
//        ft_token_add_back(tokens, ft_token_new(tkn[i], ft_token_type(tkn[i]))) ;
//        i++;
//     }
    
// }

// // ft_isspace.c 


// int ft_isspace(int c)
// {
//     return (c == ' ' || c == '\t' || c == '\n'|| c == '\f' || c == '\r' || c == '\v');
// }

// // parser 

// int main(void)
// {
// 	char	*line;

// 	while ((line = readline("minishell$ ")))
// 	{
// 		if (line && *line)
// 			add_history(line);
// 		ft_tokenize(line);
// 		free(line);
// 		line = NULL;
// 	}
// 	return (0);	
// }

// //.h

// #ifndef PARSER_H
// #define PARSER_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <string.h>

// typedef enum s_token_type
// {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,
// 	TOKEN_REDIR_IN,
// 	TOKEN_REDIR_OUT,
// 	TOKEN_REDIR_APPEND,
// 	TOKEN_REDIR_HEREDOC,
// }	t_token_type;

// typedef struct s_token
// {
// 	t_token_type	type;
// 	char			*value;
// 	struct s_token	*next;
// }	t_token;

// void	ft_tokenize(char *line);
// char	**ft_split_whitespace(char const *s);
// int		ft_isspace(int c);
// t_token	*ft_token_new(char *value, t_token_type type);
// void	ft_token_add_back(t_token **token_list, t_token *new_node);

// #endif