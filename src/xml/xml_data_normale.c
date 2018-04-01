/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_normale.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:30 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:32:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_normale(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading NORMALE value\x1b[0m", e);
		node->normale.x = ft_atof(attributes[(*i)++] + 9);
		node->normale.y = ft_atof(attributes[(*i)++]);
		if (attributes[*i][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in NORMALE vector from scene\x1b[0m", e);
		node->normale.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading NORMALE vector from scene\x1b[0m", e);
	if (node->normale.x == 0 && node->normale.y == 0 && node->normale.z == 0)
		node->normale.x = 1;
}
