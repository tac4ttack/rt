#include "rt.h"

void	xml_data_reflex(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading REFLEX value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in REFLEX from scene\x1b[0m", e);
		node->reflex = ft_atof(attributes[(*i)++] + 8);
		if (xml_check_float(NULL, node->reflex, 1))
			s_error("\x1b[1;31mError REFLEX must be 0 <= n <= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading REFLEX from scene\x1b[0m", e);
}
