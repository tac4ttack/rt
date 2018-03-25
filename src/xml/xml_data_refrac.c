#include "rt.h"

void	xml_data_refract(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading REFRACT value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in REFRACT from scene\x1b[0m", e);
		node->refract = ft_atof(attributes[(*i)++] + 9);
		if (node->refract < 0 || (node->refract > 0 && node->refract < 1))
			s_error("\x1b[2;31mError REFRACT must be 0 or >= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading REFRACT from scene\x1b[0m", e);
}
