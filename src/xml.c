/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:33:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/03 20:36:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_read_file(t_env *e)
{
	int		status;
	char	*buf;

	status = 1;
	while (status == 1)
	{
		status = get_next_line(XML->scene_fd, &buf);
		if (status == -1)
			p_error("\x1b[2;31mError reading scene\x1b[0m", e);
		else if (status == 0)
			break ;
		else
		{
			buf = xml_check_line(e, ft_strtrim_free(buf));
			XML->scene = ft_strjoin_free(XML->scene, ft_strjoin_frs1(buf, " "));
		}
	}
	close(XML->scene_fd);
}

void		xml_get_file(t_env *e, char *av)
{
//	if (ac > 2)
//		s_error("\x1b[2;31mError, too many arguments\x1b[0m", e);
//	else if (ac == 2)
		XML->scene = ft_strdup(av);
//	else
//	{
//		ft_putendl("\x1b[2;33mNo scene file specified, loading default\x1b[0m");
//		XML->scene = ft_strdup("./scenes/default.xml");
//	}
	if ((XML->scene_fd = open(XML->scene, O_RDONLY)) < 0)
		p_error("\x1b[2;31mCan't open scene file\x1b[0m", e);
	ft_bzero((void*)XML->scene, ft_strlen(XML->scene));
	xml_read_file(e);
	xml_parse_nodes(e);
}

void		xml_init(t_env *e, char *av)
{
	if (!(XML = malloc(sizeof(t_xml))))
		s_error("\x1b[2;31mCan't initialize the xml buffer\x1b[0m", e);
	ft_bzero(XML, sizeof(t_xml));
	XML->node_lst = NULL;
	xml_get_file(e, av);
}
