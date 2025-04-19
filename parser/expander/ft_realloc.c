#include "../parser.h"

#include <stdlib.h> // For malloc, free
#include <stddef.h> // For size_t

// You might need your own ft_memcpy if memcpy isn't allowed
// If memcpy is allowed, include <string.h>
// Assuming you have ft_memcpy or can use memcpy:
#include <string.h> // Or your libft header for ft_memcpy

// If memcpy is not allowed, here's a simple one:
void *ft_memcpy(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    if (dst == NULL && src == NULL) // Handle NULL case if needed
        return NULL;
    while (n--) {
        *d++ = *s++;
    }
    return dst;
}


/**
 * @brief Reallocates a memory block.
 *
 * @param ptr Pointer to the memory block to reallocate (can be NULL).
 * @param old_size The current size (in bytes) of the block pointed to by ptr.
 *                 Required for copying. Ignored if ptr is NULL.
 * @param new_size The desired new size (in bytes) for the memory block.
 *
 * @return void* Pointer to the newly allocated memory block, or NULL if:
 *         - new_size is 0 and ptr is not NULL (frees ptr).
 *         - Allocation fails.
 *         If ptr was NULL, behaves like malloc(new_size).
 *         If allocation succeeds, the original ptr is freed.
 */
void *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
    void *new_ptr;
    size_t copy_size;

    // Case 1: new_size is 0, behave like free(ptr) and return NULL
    if (new_size == 0) {
        if (ptr != NULL) {
            free(ptr);
        }
        return (NULL); // Standard realloc behavior
    }

    // Case 2: ptr is NULL, behave like malloc(new_size)
    if (ptr == NULL) {
        return (malloc(new_size));
    }

    // Case 3: Resizing an existing block (ptr != NULL, new_size > 0)
    new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        // Allocation failed, original ptr is untouched
        return (NULL);
    }

    // Determine how much data to copy
    if (new_size < old_size) {
        copy_size = new_size; // Shrinking, copy only up to new size
    } else {
        copy_size = old_size; // Growing, copy all old data
    }

    // Copy data from the old block to the new block
    ft_memcpy(new_ptr, ptr, copy_size); // Or use memcpy if allowed

    // Free the original memory block
    free(ptr);

    // Return the pointer to the new block
    return (new_ptr);
}