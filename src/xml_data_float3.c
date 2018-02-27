/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_float3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:27:32 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/26 18:27:39 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	xml_data_speculos(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading SPECULAR value\x1b[0m", e);
		node->spec.x = ft_atof(attributes[(*i)++] + 6);
		node->spec.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in SPEC from scene\x1b[0m", e);
		node->spec.z = ft_atof(attributes[(*i)++]);
		if (check_float(&node->spec, 0, 1))
			s_error("\x1b[2;31mError SPECULAR can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading SPECULAR from scene\x1b[0m", e);
}

void	xml_data_diffiouse(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading DIFFUSE value\x1b[0m", e);
		node->diff.x = ft_atof(attributes[(*i)++] + 6);
		node->diff.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[2;31mError in DIFF from scene\x1b[0m", e);
		node->diff.z = ft_atof(attributes[(*i)++]);
		if (check_float(&node->diff, 0, 1))
			s_error("\x1b[2;31mError DIFFUSE can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading DIFFUSE from scene\x1b[0m", e);
}
