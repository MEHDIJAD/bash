#include "parser.h"

void *ft_malloc(size_t size)
{
    void *ptr;
    if (size == 0)
        return (NULL);
    ptr = malloc(size);
    if (!ptr){
        perror("malloc FAILED");
        exit(EXIT_FAILURE);
    }
}