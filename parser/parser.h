/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:16:43 by eel-garo          #+#    #+#             */
/*   Updated: 2025/05/01 16:57:43 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h> //! MBLater
# include <string.h> //^ for strcmp make your's

typedef enum s_token_type
{
	TOKEN_WORD, // 0
	TOKEN_PIPE, // 1
	TOKEN_REDIR_IN, // 2 -> < 
	TOKEN_REDIR_OUT, // 3 -> >
	TOKEN_REDIR_APPEND, // 4 -> >>
	TOKEN_REDIR_HEREDOC, // 5 -> >>
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		flag_env;
	struct s_env *next;
}	t_env;

typedef struct s_redir
{
    t_token_type    type;
    char            *filename;
    int                heredoc_fd;
    bool            expand_heredoc;
    struct s_redir    *next;
}    t_redir;

typedef struct s_cmd
{
    char            **argv;
    struct s_redir    *redir;
    struct s_cmd    *next;
}    t_cmd;


typedef struct s_data
{
    t_env    *env_list;
    int        last_exit_status;
}    t_data;



//libft
int		ft_isspace(int c);
int		ft_isquot(int c);
char	*ft_strncpy(char *dest, const char *src, size_t dstsize);
size_t	ft_strlen(const char *string);

//ft_utils_split.c
int		ft_isoperater(int c);
int		ft_isdouble_op(const char *line, int k);
char	**free_all(char **tkn_array, int i);
char	*ft_alloc_token(int token_len, int j, const char *line);
void	ft_advance_word_token(const char *line, int *i);
// ft_utils_error.c
int		quote_error(const char *line);
int		pipe_error(const char *line);
int		redir_error(const char *line);

// Tokenize Part
t_token	*ft_tokenize(char *line);
char	**ft_split_tokens(const char *line);
t_token	*ft_token_new(char *value, t_token_type type);
void	ft_token_add_back(t_token **token_list, t_token *new_node);
void	ft_token_delone(t_token *node);
void	ft_token_clear(t_token **token_list);
void	ft_print_token_list(t_token *head); // just for printing
int		ft_synax_error_free(const char *line);

// expander Part
void	ft_expander(t_token **token, t_env *env);
char	*ft_strjoined(char const *string, char const *str);
int		ft_strcmp(const char *alpha, const char *bita);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_clean_up(t_token **token);
int		ft_isdouble_quote(char *word);
int 	ft_isexpandable(t_token *current);
int		ft_isbign_variable(char c);
int 	ft_ispt_variable(char c);
int		ft_peakahead(char c);
char	*ft_build_variable_name(const char *orign, int peak, int *index);
char	*ft_isvariablet_exist(t_env *env_list, char *variable_name);
void	ft_expand(t_token **token_ptr, t_env *env);
int		ft_isdigit(int c);

//expander/env
t_env	*ft_getenv(char **env);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);
t_env	*ft_tenv_new(char *name, char *value, int flag);
void	ft_tenv_add_back(t_env **env_list, t_env *new_node);
t_env	*ft_tenv_last(t_env *env);
void	ft_tenv_delone(t_env *node);
void	ft_tenv_clear(t_env **token_list);

// cmd_table
t_cmd	*ft_creat_cmd_table(t_token *token);
t_cmd	*ft_cmd_new(void);
void	ft_cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
t_redir	*ft_redir_new(int type, char *filename);
void	ft_redir_add_back(t_redir **redir_list, t_redir *new_redir);
void	ft_print_cmd_table(t_cmd *head);
void	ft_cmd_clear(t_cmd **cmd_list);
void	ft_redir_clear(t_redir **redir_list);

#endif
