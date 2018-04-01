/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_specular.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:32:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_data_speculos(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading SPECULAR value\x1b[0m", e);
		node->spec.x = ft_atof(attributes[(*i)++] + 6);
		node->spec.y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in SPEC from scene\x1b[0m", e);
		node->spec.z = ft_atof(attributes[(*i)++]);
		if (xml_check_float(&node->spec, 0, 1))
			s_error("\x1b[1;31mError SPECULAR can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading SPECULAR from scene\x1b[0m", e);
}
