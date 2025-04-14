#include "parser.h" // Needs t_token definition

/**
 * @brief Returns the last node of the token list.
 *
 * @param lst The beginning of the list.
 * @return t_token* A pointer to the last node, or NULL if the list is empty.
 */
static t_token *ft_token_last(t_token *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next) // Traverse until the node whose 'next' is NULL
    {
        lst = lst->next;
    }
    return (lst); // This is the last node
}

#include "parser.h" // Needs t_token definition

// Forward declaration or include the definition of ft_token_last
t_token *ft_token_last(t_token *lst);

/**
 * @brief Adds the node 'new_node' at the end of the token list.
 *
 * @param token_list A pointer to the pointer of the first node of the list.
 *                   This allows modification of the head pointer if the list
 *                   is initially empty.
 * @param new_node The node to add to the list.
 */
void ft_token_add_back(t_token **token_list, t_token *new_node)
{
    t_token *last;

    // Check for invalid inputs (NULL pointer to the list head or NULL new node)
    if (!token_list || !new_node)
        return;

    if (*token_list) // If the list is NOT empty
    {
        // Find the current last node
        last = ft_token_last(*token_list);
        // Set the 'next' of the current last node to point to the new node
        last->next = new_node;
    }
    else // If the list IS empty
    {
        // The new node becomes the first node
        *token_list = new_node;
    }
    // Note: new_node->next should already be NULL (as set by ft_token_new)
}