/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_brightness.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:31:55 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:31:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_data_brightness(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading BRIGHTNESS value\x1b[0m", e);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in BRIGHT from scene\x1b[0m", e);
		node->brightness = ft_atof(attributes[(*i)++] + 12);
		if (xml_check_float(NULL, node->brightness, 1))
			s_error("\x1b[1;31mError BRIGHTNESS must be 0 <= n <= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading BRIGHTNESS from scene\x1b[0m", e);
}
