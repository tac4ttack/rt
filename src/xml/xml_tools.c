/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:35:58 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 20:14:12 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_node_clean(char ***target)
{
	int		i;
	char	**s;

	s = *target;
	i = 0;
	if (s)
		while (s[i])
			ft_memdel((void**)&s[i++]);
	ft_memdel((void **)target);
}

int			xml_check_char(char c)
{
	if ((c < 32 || c > 125) && c != 0 && c != 9 && c != 10)
		return (1);
	else
		return (0);
}

char		*xml_check_line(t_env *e, char *buf)
{
	int		i;

	i = 0;
	if (buf == NULL)
		return (NULL);
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
