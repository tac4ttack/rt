/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:33:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:28:25 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_read_file(t_env *e)
{
	int		status;
	char	*buf;

	ft_putendl("\x1b[1;29mReading scene file...\x1b[0m");
	status = 1;
	while (status == 1)
	{
		status = get_next_line(e->scene_fd, &buf);
		if (status == -1)
			p_error("\x1b[1;31mError reading scene\x1b[0m", e);
		else if (status == 0)
			break ;
		else
		{
			buf = xml_check_line(e, ft_strtrim_free(buf));
			e->scene_file = ft_strjoin_free(e->scene_file, \
											ft_strjoin_frs1(buf, " "));
		}
	}
	ft_putendl("\x1b[1;29mScene read\n\x1b[0m");
	close(e->scene_fd);
}

void		xml_get_file(t_env *e)
{
	ft_putendl("\x1b[1;29mOpening scene file...\x1b[0m");
	if ((e->scene_fd = open(e->scene_file, O_RDONLY)) < 0)
		p_error("\x1b[1;31mCan't open scene file\x1b[0m", e);
	ft_bzero((void*)e->scene_file, ft_strlen(e->scene_file));
	ft_putendl("\x1b[1;29mScene file opened\n\x1b[0m");
	xml_read_file(e);
	xml_parse_nodes(e);
}

void		xml_init(t_env *e)
{
	ft_putendl("\n\x1b[1;32m/\\ Processing XML scene file /\\\n\x1b[0m");
	if (!(XML = malloc(sizeof(t_xml))))
		s_error("\x1b[1;31mCan't initialize the xml buffer\x1b[0m", e);
	ft_bzero(XML, sizeof(t_xml));
	XML->node_lst = NULL;
	xml_get_file(e);
}
