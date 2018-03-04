/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_check_attr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:28:15 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/04 23:26:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_float(cl_float4 *clf, float f, int mod)
{
	if (mod == 0)
	{
		if (clf->x < 0 || clf->y < 0 || clf->z < 0)
			return (1);
		if (clf->x > 1 || clf->y > 1 || clf->z > 1)
			return (1);
	}
	else if (f < 0 || f > 1)
		return (1);
	return (0);
}

int			xml_check_attnode(char *att, int j)
{
	int		ok;

	ok = 0;
	while (att[j])
	{
		if ((att[j] < 48 || att[j] > 57) && att[j] != '.' && att[j] != '-')
		{
			if (att[j] != ',' && att[j] != '"')
				return (1);
			ok = 1;
			if (att[j + 1] != '\0' && att[j + 1] != '>')
				return (1);
		}
		if (att[j + 1] == '>')
			++j;
		++j;
	}
	if (ok == 0)
		return (1);
	return (0);
}

int			xml_check_attr(t_env *e, char **att)
{
	int		i;
	int		j;

	i = 1;
	if (XML->is_comm == 0)
		while (att[i])
		{
			if (ft_strcmp(att[0], "!--") == 0)
				return (0);
			j = 0;
			if (att[i][j] >= 97 && att[i][j] <= 122)
				while (att[i][j] && att[i][j] != '=')
					j++;
			if (att[i][j] == 0)
				return (1);
			if (att[i][j] == '=')
				j += 2;
			if (xml_check_attnode(att[i], j) == 1)
				return (1);
			++i;
			while (att[i] && (ft_strcmp(att[i], "/>") == 0 || \
			ft_strcmp(att[i], "-->") == 0 || ft_strcmp(att[i], "/>-->") == 0))
				++i;
		}
	return (0);
}
