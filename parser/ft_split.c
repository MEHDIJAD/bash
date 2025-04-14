#include "parser.h" // Assuming ft_isspace is defined or included here

// Forward declarations for static helpers (signatures updated)
static size_t   ft_count_whitespace_tokens(char const *s);
static char     **ft_freeall(char **tofill, size_t i);
static size_t   ft_count_word_len(const char *s, size_t i);
static char     **ft_fill_whitespace_split(char **tofill, const char *s);

// Counts the length of a word starting at index i until whitespace or end.
static size_t ft_count_word_len(const char *s, size_t i)
{
    size_t len = 0;

    // Count characters until whitespace or end of string is found
    while (s[i] && !ft_isspace(s[i]))
    {
        len++;
        i++;
    }
    return (len);
}

// Fills the allocated array with strings split by whitespace.
static char **ft_fill_whitespace_split(char **tofill, const char *s)
{
    size_t i = 0; // Index for the 'tofill' array
    size_t j = 0; // Index for the input string 's'
    size_t k;     // Index for the individual word being copied
    size_t total_tokens = ft_count_whitespace_tokens(s); // Calls updated counter

    while (i < total_tokens)
    {
        // Skip leading whitespace characters in 's'
        while (s[j] && ft_isspace(s[j]))
            j++;

        // If we didn't reach the end after skipping spaces
        if (s[j])
        {
            // Get the length of the next word
            size_t word_len = ft_count_word_len(s, j);
            // Allocate memory for the word + null terminator
            tofill[i] = malloc((word_len + 1) * sizeof(char));
            if (!tofill[i])
                return (ft_freeall(tofill, i)); // Use your original freeall

            // Copy the word (non-whitespace characters)
            k = 0;
            while (s[j] && !ft_isspace(s[j]))
            {
                tofill[i][k] = s[j];
                k++;
                j++;
            }
            tofill[i][k] = '\0'; // Null-terminate the copied word
            i++; // Move to the next slot in the 'tofill' array
        }
        else // Should not happen if ft_count_whitespace_tokens is correct, but good practice
        {
            break;
        }
    }
    tofill[i] = NULL; // Null-terminate the array of strings
    return (tofill);
}

// Frees the entire allocated array of strings.
static char **ft_freeall(char **tofill, size_t i)
{
    while (i > 0)
    {
        free(tofill[i - 1]);
        i--;
    }
    free(tofill);
    return (NULL);
}

// Counts the number of tokens separated by whitespace.
static size_t ft_count_whitespace_tokens(char const *s)
{
    size_t count = 0;
    size_t i = 0;

    while (s[i])
    {
        // Skip whitespace characters
        while (s[i] && ft_isspace(s[i]))
            i++;
        // If it's not whitespace and not the end, it's the start of a token
        if (s[i] && !ft_isspace(s[i]))
            count++;
        // Skip non-whitespace characters (the token itself)
        while (s[i] && !ft_isspace(s[i]))
            i++;
    }
    return (count);
}

/**
 * @brief Splits a string by any whitespace character defined by ft_isspace.
 *
 * @param s The string to split.
 * @return char** An array of strings (tokens), NULL-terminated.
 *         Returns NULL if allocation fails or if s is NULL.
 */
char **ft_split_whitespace(char const *s) // Renamed for clarity, removed 'c'
{
    char   **splitstr;
    size_t strcount;

    if (!s)
        return (NULL);

    // Count tokens using the whitespace counter
    strcount = ft_count_whitespace_tokens(s);

    // Allocate memory for the array of string pointers (+1 for NULL terminator)
    splitstr = (char **)malloc((strcount + 1) * sizeof(char *));
    if (!splitstr)
        return (NULL);

    // Fill the array with the tokens
    if (!ft_fill_whitespace_split(splitstr, s)) // Call updated filler
        return (NULL); // ft_fill_whitespace_split handles freeing on error

    return (splitstr);
}

// --- You would also need ft_isspace defined or included ---
/*
int ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n'|| c == '\f' || c == '\r' || c == '\v');
}
*/

// --- And potentially update your ft_tokenize function ---
/*
void ft_tokenize(t_token *token, char *line) // Assuming t_token is still relevant
{
    char **tkn_array;
    size_t cnt_tokens;

    // Use the new split function
    tkn_array = ft_split_whitespace(line);

    if (!tkn_array) {
        // Handle allocation error, maybe print message and return
        perror("Failed to split line");
        return;
    }

    // You'll need to iterate through tkn_array to count or process tokens
    // For example, just counting again (though redundant):
    cnt_tokens = 0;
    while(tkn_array[cnt_tokens]) {
        cnt_tokens++;
    }
    printf("Number_tokens: %ld\n", cnt_tokens);

    // Remember to free the allocated array and its contents when done
    // ft_freeall(tkn_array, cnt_tokens); // Or a similar freeing function
}
*/