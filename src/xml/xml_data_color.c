/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:31:58 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:31:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_color(t_env *e, char **attr, int *i, t_node *node)
{
	int		chan[4];
	int		j;

	j = -1;
	ft_memset(chan, 0, 4 * sizeof(int));
	if (e && attr && node)
	{
		while (++j < 4)
		{
			if (attr[(*i)] == NULL)
				s_error("\x1b[1;31mError reading COLOR value\x1b[0m", e);
			if (j == 3 && attr[(*i)][ft_strlen(attr[*i]) - 1] != '\"')
				s_error("\x1b[1;31mError in COLOR from scene\x1b[0m", e);
			if (j == 0)
				chan[j] = ft_atoi(attr[(*i)++] + 7);
			else
				chan[j] = ft_atoi(attr[(*i)++]);
			if (chan[j] < 0 || chan[j] > 255)
				s_error("\x1b[1;31mError COLOR range is 0 to 255\x1b[0m", e);
		}
		node->color = ((chan[0] << 24) + (chan[1] << 16) + \
		(chan[2] << 8) + chan[3]);
	}
	else
		s_error("\x1b[1;31mError reading COLOR from scene\x1b[0m", e);
}
