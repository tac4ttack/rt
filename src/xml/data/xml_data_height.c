/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:25 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/10 16:38:04 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_data_height(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading HEIGHT value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in HEIGHT from scene\x1b[0m", e);
		// node->height = ft_atof(attributes[(*i)++] + 8);
		// if (node->height < 0)
		// 	s_error("\x1b[1;31mError HEIGHT can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading HEIGHT from scene\x1b[0m", e);
}
