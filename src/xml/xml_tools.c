/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:35:58 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/05 15:09:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_node_clean(char **target)
{
	int	i;

	i = 0;
	if (target)
		while (target[i])
		{
			free(target[i]);
			target[i] = NULL;
			i++;
		}
	free(target);
	target = NULL;
}

int		xml_check_char(char c)
{
	if ((c < 32 || c > 125) && c != 0 && c != 9 && c != 10)
		return (1);
	else
		return (0);
}

char	*xml_check_line(t_env *e, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (xml_check_char(buf[i]) != 0)
		{
			free(buf);
			s_error("\x1b[1;31mError target file is invalid\x1b[0m", e);
		}
		(buf[i] == '\t' ? buf[i] = ' ' : 0);
		(buf[i] == '<' ? XML->lbra++ : 0);
		(buf[i] == '>' ? XML->rbra++ : 0);
		(buf[i] == '/' ? XML->slas++ : 0);
		(buf[i] == '"' ? XML->dquo++ : 0);
		(buf[i] == '!' ? XML->excl++ : 0);
		i++;
	}
	return (buf);
}
