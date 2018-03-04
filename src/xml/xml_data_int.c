/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:32:12 by fmessina          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_type(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading LIGHT TYPE value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in TYPE from light\x1b[0m", e);
		node->light = ft_atoi(attributes[(*i)++] + 6);
		if (node->light < 0 || node->light > 2)
			s_error("\x1b[2;31mError LIGHT TYPE not between 0 & 2\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading LIGHT TYPE from scene\x1b[0m", e);
}

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
				s_error("\x1b[2;31mError reading COLOR value\x1b[0m", e);
			if (j == 3 && attr[(*i)][ft_strlen(attr[*i]) - 1] != '\"')
				s_error("\x1b[2;31mError in COLOR from scene\x1b[0m", e);
			if (j == 0)
				chan[j] = ft_atoi(attr[(*i)++] + 7);
			else
				chan[j] = ft_atoi(attr[(*i)++]);
			if (chan[j] < 0 || chan[j] > 255)
				s_error("\x1b[2;31mError COLOR range is 0 to 255\x1b[0m", e);
		}
		node->color = ((chan[0] << 24) + (chan[1] << 16) + \
		(chan[2] << 8) + chan[3]);
	}
	else
		s_error("\x1b[2;31mError reading COLOR from scene\x1b[0m", e);
}

void		xml_data_shrink(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading SHRINK value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in SHRINK from scene\x1b[0m", e);
		node->shrink = ft_atoi(attributes[(*i)++] + 8);
		if (node->shrink < 0)
			s_error("\x1b[2;31mError SHRINK can't be negative\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading SHRINK from scene\x1b[0m", e);
}
