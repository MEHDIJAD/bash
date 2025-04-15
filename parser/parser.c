#include "parser.h"


int main(void)
{
	char	*line;
    t_token *token_list_head = NULL;
    // one-time setup; ensures the pointer is not holding a garbage value

	while ((line = readline("minishell$ ")))
	{
        token_list_head = NULL;
        // per-command reset; after each tokenize list
		if (line && *line)
        {
			add_history(line);
            token_list_head = ft_tokenize(line);
            if (token_list_head)
                ft_print_token_list(token_list_head);
            else
                printf("Tokenization failed or line was empty.\n");
        }
		free(line);
        ft_token_clear(&token_list_head);
        token_list_head = NULL;
		line = NULL;
	}
    rl_clear_history();
	return (0);	
}