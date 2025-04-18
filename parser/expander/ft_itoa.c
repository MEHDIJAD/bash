#include "../parser.h"

static size_t	ft_countnblen(int n)
{
	size_t	nlen;

	if (n == 0)
		return (1);
	nlen = 0;
	if (n < 0)
		nlen++;
	while (n != 0)
	{
		n /= 10;
		nlen++;
	}
	return (nlen);
}

char	*ft_itoa(int n)
{
	size_t	nlen;
	size_t	l;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nlen = ft_countnblen(n);
	ptr = (char *)malloc((nlen + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	l = 0;
	if (n < 0)
	{
		l = 1;
		ptr[0] = '-';
		n = -n;
	}
	ptr[nlen] = '\0';
	while (nlen-- > l)
	{
		ptr[nlen] = (n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}