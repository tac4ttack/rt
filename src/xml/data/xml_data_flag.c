#include "rt.h"

void		xml_data_flag(t_env *e, char **attributes, int *i, t_node *node)
{
	int j;

	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading FLAG value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in FLAG from scene\x1b[0m", e);
		j = 7;
		printf("%s\n", attributes[(*i)]);
		while (attributes[(*i)][j] && attributes[(*i)][j] != '\"')
		{
			if (attributes[(*i)][j] - 48)
			{
				printf("%c %i\n", attributes[(*i)][j], attributes[(*i)][j] - 48);
				node->flags |= (1 << (j - 7));
			}
			j++;
		}
		(*i)++;
		int k = node->flags;
		while (k)
		{
			printf("%i\n", k%2);
			k /= 2;
		}
		printf("\n");
	}
	else
		s_error("\x1b[1;31mError reading FLAG from scene\x1b[0m", e);
}
