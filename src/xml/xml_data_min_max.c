#include "rt.h"

void	xml_data_min_max(t_env *e, char **attributes, int *i, cl_float3 *f)
{
	if (f && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading MINMAX value\x1b[0m", e);
		f->x = ft_atof(attributes[(*i)++] + 5);
		f->y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in MINMAX vector from scene\x1b[0m", e);
		f->z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading MINMAX vector from scene\x1b[0m", e);
}
