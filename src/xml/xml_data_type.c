/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:47 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:32:48 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_type(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading LIGHT TYPE value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in TYPE from light\x1b[0m", e);
		node->light = ft_atoi(attributes[(*i)++] + 6);
		if (node->light < 0 || node->light > 2)
			s_error("\x1b[1;31mError LIGHT TYPE not between 0 & 2\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading LIGHT TYPE from scene\x1b[0m", e);
}
