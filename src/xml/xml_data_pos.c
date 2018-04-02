/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:33 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:32:34 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_pos(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading POS value\x1b[0m", e);
		node->pos.x = ft_atof(attributes[(*i)++] + 5);
		node->pos.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in POS vector from scene\x1b[0m", e);
		node->pos.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading POS vector from scene\x1b[0m", e);
}
