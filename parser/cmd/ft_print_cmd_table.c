#include "../parser.h"

void ft_print(char **argv)
{
    int i = 0;

    // *** ADD THIS CHECK ***
    if (argv == NULL)
    {
        printf("[ (no arguments) ]\n"); // Or just print nothing
        return;
    }
    // *** END CHECK ***

    // Original loop is fine if argv is not NULL
    while (argv[i] != NULL)
    {
        printf("[%s] ", argv[i]); // Maybe remove trailing comma/newline here
        i++;
    }
     printf("\n"); // Add newline after printing all args for one command
}

// Optional: Adjust ft_print_cmd_table slightly for formatting
void    ft_print_cmd_table(t_cmd *head)
{
    t_cmd *curr_cmd = head;
    t_redir *curr_redir;
    int cmd_num = 0;

    while (curr_cmd)
    {
        printf("--- Command %d ---\n", cmd_num);
        printf("  Args: "); // Label for arguments
        ft_print(curr_cmd->argv); // ft_print now handles NULL and adds newline

        if (curr_cmd->redir)
        {
             printf("  Redirs:\n"); // Label for redirections
            curr_redir = curr_cmd->redir;
            while (curr_redir)
            {
                // Use the helper function from before for readable types
                // const char *type_str = ft_redir_type_to_str(curr_redir->type);
                // printf("    type: %s ", type_str);
                printf("    type: %d ", curr_redir->type); // Original version
                printf("bool: %d ", curr_redir->expand_heredoc);
                printf("filename: %s " , curr_redir->filename ? curr_redir->filename : "(null)");
                printf("fd: %d\n", curr_redir->heredoc_fd);
                curr_redir = curr_redir->next;
            }
        } else {
             printf("  Redirs: (None)\n");
        }
        printf("------------------\n");
        curr_cmd = curr_cmd->next;
        cmd_num++;
    }
}