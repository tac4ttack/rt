#include "libft.h"

void		*ft_memnew(void *ptr, size_t mem_size)
{
	char	*new;

	if (!(new = ft_memalloc(mem_size)))
		return (NULL);
	ft_memcpy(new, ptr, mem_size);
	return ((void*)new);
}
