#include "parser.h"

#include "parser.h" // Needs t_token definition and t_token_type enum
#include <stdio.h>  // For printf

/**
 * @brief Prints the contents (value and type) of a token linked list.
 *
 * Iterates through the linked list starting from the head and prints
 * the string value and the integer representation of the type for each token.
 *
 * @param head A pointer to the first node (head) of the token list.
 */
void ft_print_token_list(t_token *head)
{
    t_token *current = head; // Start traversal from the head
    int i = 0;               // Optional counter for indexing

    printf("--- Printing Token List ---\n");
    if (!current)
    {
        printf("  (List is empty)\n");
    }
    // Loop while the current node pointer is not NULL
    while (current != NULL)
    {
        // Print index, value (checking for NULL), and type
        printf("  [%d] Value: [%s], Type: %d\n",
               i,
               current->value ? current->value : "(null value)", // Safety check
               current->type);

        // Move to the next node in the list
        current = current->next;
        i++; // Increment index
    }
    printf("--- End of Token List ---\n");
}

int main(void)
{
	char	*line;
    t_token *token_list_head = NULL;

	while ((line = readline("minishell$ ")))
	{
        token_list_head = NULL;
		if (line && *line)
        {
			add_history(line);
            token_list_head = ft_tokenize(line);
            if (token_list_head)
            {
                ft_print_token_list(token_list_head);
            }
            else
                printf("Tokenization failed or line was empty.\n");
        }
		free(line);
		line = NULL;
	}
	return (0);	
}