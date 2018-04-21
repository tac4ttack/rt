/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:46:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/21 23:34:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_strlen(&attributes[(*i)][j + 7]) - 1 != 8)
				s_error("\x1b[1;31mError in FLAG : expect 8 [01] elements\x1b[0m", e);
		j = 7;
		while (attributes[(*i)][j] && attributes[(*i)][j] != '\"')
		{
			if (attributes[(*i)][j] - 48)
				node->flags |= (1 << (j - 7));
			j++;
		}
		(*i)++;
	}
	else
		s_error("\x1b[1;31mError reading FLAG from scene\x1b[0m", e);
}
