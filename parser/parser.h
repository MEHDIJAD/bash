#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h> //! RML

typedef enum s_token_type
{
	TOKEN_WORD, // 0
	TOKEN_PIPE, // 1
	TOKEN_REDIR_IN, // 2
	TOKEN_REDIR_OUT, // 3
	TOKEN_REDIR_APPEND, // 4
	TOKEN_REDIR_HEREDOC, // 5
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

//libft
int		ft_isspace(int c);
int		ft_isquot(int c);
char	*ft_strncpy(char *dest, const char *src, size_t dstsize);
size_t ft_strlen(const char *string);

t_token *ft_tokenize(char *line);
char	**ft_split_tokens(const char *line);
t_token	*ft_token_new(char *value, t_token_type type);
void	ft_token_add_back(t_token **token_list, t_token *new_node);
void    ft_token_delone(t_token *node);
void    ft_token_clear(t_token **token_list);
int		ft_token_size(t_token *head); // might need later
void	ft_print_token_list(t_token *head); // just for printing

#endif