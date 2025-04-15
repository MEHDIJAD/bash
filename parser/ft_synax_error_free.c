#include "parser.h"

int quote_error(const char *line)
{
	int		index;
	int		in_quote_flag;

	in_quote_flag = 0;
	index = 0;
	while (line[index])
	{
		if (in_quote_flag == 0 && line[index] == '\'')
			in_quote_flag = 1;
		else if (in_quote_flag == 0 && line[index] == '\"')
			in_quote_flag = 2;
		else if (in_quote_flag == 1 && line[index] == '\'')
			in_quote_flag = 0;
		else if (in_quote_flag == 2 && line[index] == '\"')
			in_quote_flag = 0;
		index++;
	}
	return (in_quote_flag != 0); //TODO-> NC (new code or nuclear code)
}
/*	
	if in_quot_flag = 0 -> 0 != 0 false -> no error
	else if in_quot_flag = 1 || 2 != 0 true -> error
	Return 1 (true -> error)
	Return 0 (false -> no error)
	the quastion is is quot_error ?
*/

int ft_helper_pipe_func(const char *line)
{
	size_t lenght;
	int start;
	int end;

	lenght =  ft_strlen(line);
	if (lenght == 0)
		return (0);
	start = 0;
	while(line[start] && ft_isspace(line[start]))
		start++;
	if (!line[start] || line[start] == '|')
		return (1);
	end = lenght - 1;
	while (end >= 0 && ft_isspace(line[end]))
		end--;
	if (line[end] == '|')
		return (1);
	return (0);
}
int pipe_error(const char *line)
{
	int i;
	bool last_was_pipe;

	if (ft_helper_pipe_func(line))
		return (1);
	i = 0;
	last_was_pipe = false;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			// ignore this case and move one
		}
		else if (line[i] == '|')
		{
			if (last_was_pipe)
				return (1);
			last_was_pipe = true;
		}
		else
			last_was_pipe = false;
		i++;
	}
	return (0);
}
int	redir_error(const char *line)
{
	size_t lenght;
	int end;

	lenght = ft_strlen(line);
	if (lenght == 0)
		return (0);
	end = lenght - 1;
	while (end >= 0 && ft_isspace(line[end]))
		end--;
	if (end < 0)
		return (0);
	if (line[end] == '>' || line[end] == '<')
		return (1);
	return (0);
}
int ft_synax_error_free(const char *line)
{
	if (!line) //! keep this so you do not repeat in all error funcs 
		return (0);
	// if (redir_error(line) == 1){
	// 	printf("invalid cmd\n");
	// 	return (0);
	// }
	// else{
	// 	printf("valid cmd\n");
	// 	return (1);
	// }
	return (!quote_error(line) && !pipe_error(line) && !redir_error(line));
}