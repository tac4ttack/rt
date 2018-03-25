#include "rt.h"

void	xml_data_opacity(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading OPACITY value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in OPACITY from scene\x1b[0m", e);
		node->opacity = ft_atof(attributes[(*i)++] + 9);
		if (node->opacity < 0 || node->opacity > 1)
			s_error("\x1b[2;31mError OPACITY must be 0 <= n <= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading REFRACT from scene\x1b[0m", e);
}
