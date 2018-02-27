/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:27:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_data_reflex(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading REFLEX value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in REFLEX from scene\x1b[0m", e);
		node->reflex = ft_atof(attributes[(*i)++] + 8);
		if (check_float(NULL, node->reflex, 1))
			s_error("\x1b[2;31mError REFLEX must be 0 <= n <= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading REFLEX from scene\x1b[0m", e);
}

void	xml_data_brightness(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading BRIGHTNESS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in BRIGHT from scene\x1b[0m", e);
		node->brightness = ft_atof(attributes[(*i)++] + 12);
		if (check_float(NULL, node->brightness, 1))
			s_error("\x1b[2;31mError BRIGHTNESS must be 0 <= n <= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading BRIGHTNESS from scene\x1b[0m", e);
}

void	xml_data_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading RADIUS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in RADIUS from scene\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 8);
		if (node->radius <= 0)
			s_error("\x1b[2;31mError RADIUS can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading RADIUS from scene\x1b[0m", e);
}

void	xml_data_angle(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading ANGLE value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in ANGLE from scene\x1b[0m", e);
		node->angle = ft_atof(attributes[(*i)++] + 7);
	}
	else
		s_error("\x1b[2;31mError reading ANGLE from scene\x1b[0m", e);
}

/*
** à garder au chaud pour plus tard
*/

void	xml_data_height(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading HEIGHT value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in HEIGHT from scene\x1b[0m", e);
		node->height = ft_atof(attributes[(*i)++] + 8);
		if (node->height < 0)
			s_error("\x1b[2;31mError HEIGHT can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading HEIGHT from scene\x1b[0m", e);
}
