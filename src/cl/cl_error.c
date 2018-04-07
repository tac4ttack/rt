#include "libft.h"

void		opencl_error(const char *err, const void *p, size_t cb, void *u)
{
	(void)p;
	(void)cb;
	(void)u;
	ft_putstr_fd(err, 2);
	ft_putchar('\n');
}
