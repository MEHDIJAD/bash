#include "parser.h" // Needs t_token definition, t_token_type enum

/**
 * @brief Allocates and returns a new token node.
 *
 * Initializes the node with the provided value and type.
 * The 'value' pointer is assigned directly; the string is NOT duplicated.
 * The 'next' pointer is initialized to NULL.
 *
 * @param value The string content of the token.
 * @param type The type of the token (e.g., TOKEN_WORD, TOKEN_PIPE).
 * @return t_token* A pointer to the newly created token node, or NULL
 *                 if memory allocation fails.
 */
t_token *ft_token_new(char *value, t_token_type type)
{
    t_token *new_node;

    // Allocate memory for the new token structure
    new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return (NULL); // Allocation failed

    // Assign the data
    new_node->value = value; // Assign the pointer from ft_split's result
    new_node->type = type;   // Set the token type

    // Initialize the next pointer
    new_node->next = NULL;

    return (new_node);
}