/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:05:41 by fmessina          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_pos(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading POS value\x1b[0m", e);
		node->pos.x = ft_atof(attributes[(*i)++] + 5);
		node->pos.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in POS vector from scene\x1b[0m", e);
		node->pos.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading POS vector from scene\x1b[0m", e);
}

void		xml_data_dir(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading DIR value\x1b[0m", e);
		node->dir.x = ft_atof(attributes[(*i)++] + 5);
		node->dir.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in DIR vector from scene\x1b[0m", e);
		node->dir.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading DIR vector from scene\x1b[0m", e);
	if (node->dir.x == 0 && node->dir.y == 0 && node->dir.z == 0)
		node->dir.x = 1;
}

void		xml_data_normale(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading NORMALE value\x1b[0m", e);
		node->normale.x = ft_atof(attributes[(*i)++] + 9);
		node->normale.y = ft_atof(attributes[(*i)++]);
		if (attributes[*i][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in NORMALE vector from scene\x1b[0m", e);
		node->normale.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading NORMALE vector from scene\x1b[0m", e);
	if (node->normale.x == 0 && node->normale.y == 0 && node->normale.z == 0)
		node->normale.x = 1;
}
