#include "rt.h"

void		xml_data_shrink(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading SHRINK value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in SHRINK from scene\x1b[0m", e);
		node->shrink = ft_atoi(attributes[(*i)++] + 8);
		if (node->shrink < 0)
			s_error("\x1b[1;31mError SHRINK can't be negative\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading SHRINK from scene\x1b[0m", e);
}
