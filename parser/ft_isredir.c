#include "parser.h"

int	ft_isredir(int c)
{
	return (c == '<' || c == '>' || c == '>>' || c == '<<');
}