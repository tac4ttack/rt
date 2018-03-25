#include "rt.h"

void	xml_data_diffiouse(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading DIFFUSE value\x1b[0m", e);
		node->diff.x = ft_atof(attributes[(*i)++] + 6);
		node->diff.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in DIFF from scene\x1b[0m", e);
		node->diff.z = ft_atof(attributes[(*i)++]);
		if (xml_check_float(&node->diff, 0, 1))
			s_error("\x1b[1;31mError DIFFUSE can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading DIFFUSE from scene\x1b[0m", e);
}
