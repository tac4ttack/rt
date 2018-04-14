/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_radius.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 16:33:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_data_option(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading OPTION value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in OPTION from scene\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 8);
		if (node->radius <= 0)
			s_error("\x1b[1;31mError OPTION can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading OPTION from scene\x1b[0m", e);
}

void	xml_data_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading RADIUS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in RADIUS from scene\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 8);
		if (node->radius <= 0)
			s_error("\x1b[1;31mError RADIUS can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading RADIUS from scene\x1b[0m", e);
}

void	xml_data_plane_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading RADIUS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in RADIUS from scene\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 8);
		if (node->radius < 0)
			s_error("\x1b[1;31mError RADIUS under 0\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading RADIUS from scene\x1b[0m", e);
}

void	xml_data_lil_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading LILRADIUS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in LILRADIUS from scene\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 12);
		if (node->radius <= 0)
			s_error("\x1b[1;31mError LILRADIUS can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading LILRADIUS from scene\x1b[0m", e);
}

void	xml_data_big_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading BIGRADIUS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in BIGRADIUS from scene\x1b[0m", e);
		node->radius2 = ft_atof(attributes[(*i)++] + 12);
		if (node->radius2 <= 0)
			s_error("\x1b[1;31mError BIGRADIUS can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading BIGRADIUS from scene\x1b[0m", e);
}
