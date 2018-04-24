/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:04 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/04 22:47:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_dir(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading DIR value\x1b[0m", e);
		node->dir.x = ft_atof(attributes[(*i)++] + 5);
		node->dir.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in DIR vector from scene\x1b[0m", e);
		node->dir.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading DIR vector from scene\x1b[0m", e);
	if (node->dir.x == 0 && node->dir.y == 0 && node->dir.z == 0)
		node->dir.x = 1;
}

void		xml_data_plane_limit_dir(t_env *e, char **attributes, int *i, \
										t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading Plane limit DIR value\x1b[0m", e);
		node->limit_dir.x = ft_atof(attributes[(*i)++] + 5);
		node->limit_dir.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in Plane limit DIR from scene\x1b[0m", e);
		node->limit_dir.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading Plane limit DIR from scene\x1b[0m", e);
	if (node->limit_dir.x == 0 && node->limit_dir.y == 0 \
								&& node->limit_dir.z == 0)
		node->limit_dir.x = 1;
}
