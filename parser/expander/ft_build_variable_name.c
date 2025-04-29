#include "../parser.h"

static size_t	ft_vtsize(const char *string, int j)
{
	size_t	size = 0;

	while (string[j] && ft_ispt_variable(string[j]))
	{
		size++;
		j++;
	}
	return (size);
}

static char *ft_build_digit(const char *string)
{
	char *vt_name;

	vt_name = malloc(2);
	if (!vt_name)
		return (NULL);
	vt_name[0] = string[0];
	vt_name[1] = '\0';
	return (vt_name);
}

static char *ft_build_world(const char *string, size_t *var_size)
{
	char	*vt_name;
	size_t	j;
	int		k;

	j = 1;
	k = 0; 
	*var_size = ft_vtsize(string, j);
	if (var_size == 0)
		return (ft_strdup(""));
	vt_name = malloc(sizeof(char) * (*var_size + 1));
	if (!vt_name)
		return (NULL);
	while (j <= *var_size)
			vt_name[k++] = string[j++];
	vt_name[k] = '\0';
	return (vt_name);
}
char	*ft_build_variable_name(const char *orign, int peak, int *index)
{
	char		*vt_name;
	size_t		var_size;

	var_size = 0;
	if (peak == 2)
	{
		vt_name = ft_build_digit(orign);
		if (!vt_name)
			return (NULL);
		*index += 2;
	}
	if (peak == 1)
	{	
		vt_name = ft_build_world(orign, &var_size);
		if (!vt_name)
			return (NULL);
		*index += var_size + 1;
	}
	return (vt_name);
}
