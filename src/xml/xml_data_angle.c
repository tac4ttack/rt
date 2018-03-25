#include "rt.h"

void	xml_data_angle(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading ANGLE value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in ANGLE from scene\x1b[0m", e);
		node->angle = ft_atof(attributes[(*i)++] + 7);
	}
	else
		s_error("\x1b[1;31mError reading ANGLE from scene\x1b[0m", e);
}

