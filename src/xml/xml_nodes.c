/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:01:40 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 00:01:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** xml_check_node_format mod details
** 0 = scene
** 1 = camera
** 2 = cone
** 3 = cylinder
** 4 = light
** 5 = plane
** 6 = sphere
** 7 = ellipsoid
** 8 = paraboloid
** 9 = torus
** 10 = box
*/

int					xml_check_node_format(char **node, int mod)
{
	cl_int2			i;

	i.x = 0;
	i.y = 6;
	if (node)
	{
		i.y = (mod == 1 ? 9 : i.y);
		i.y = (mod == 4 ? 15 : i.y);
		i.y = (mod == 10 ? 33 + 1 : i.y);
		i.y = (mod == 7 ? 31 + 1 : i.y);
		if (mod == 2 || mod == 5 || mod == 6)
			i.y = 28 + 1;
		if (mod == 3 || mod == 8 || mod == 9)
			i.y = 29 + 1;
		while (i.x <= i.y)
		{
			if (i.x == i.y && node[i.x] != NULL)
				return (1);
			else if (i.x < i.y && node[i.x] == NULL)
				return (1);
			i.x++;
		}
		return (0);
	}
	return (1);
}

void				xml_node_generic(t_env *e, char *node, char mod)
{
	char			*tmp;

	tmp = ft_strtrim(node);
	if (mod == 0)
	{
		if (ft_strcmp(tmp, "?xml version=\"1.0\"?>") != 0)
			s_error("\x1b[1;31mError XML header is invalid\x1b[0m", e);
	}
	else if (mod == 1)
	{
		if ((node = ft_strstr(tmp, "-->")) != NULL)
		{
			XML->is_comm = 0;
			if (ft_strlen(node) != 3)
			{
				ft_putstr("\x1b[1;31mWRONG NODE = \x1b[0m");
				ft_putstr(node);
				s_error("\x1b[1;31mError in XML syntax\x1b[0m", e);
			}
		}
		else
			XML->is_comm = 1;
	}
	free(tmp);
}

static void			xml_process_node_obj(t_env *e, char *node)
{
	if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "cone") == 0)
		xml_node_cone(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "cylinder") == 0)
		xml_node_cylinder(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "plane") == 0)
		xml_node_plane(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "sphere") == 0)
		xml_node_sphere(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "ellipsoid") == 0)
		xml_node_ellipsoid(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "torus") == 0)
		xml_node_torus(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "box") == 0)
		xml_node_box(e, node);
	else
		s_error("\x1b[1;31mError wrong node type\x1b[0m", e);
	xml_node_clean(XMLSUB);
}

void				xml_process_node(t_env *e, char *node)
{
	if (!(XMLSUB = ft_strsplit(node, ' ')) || xml_check_attr(e, XMLSUB) != 0)
		s_error("\x1b[1;31mInput file is not valid\x1b[0m", e);
	if (ft_strcmp(XMLSUB[0], "!--") == 0 || XML->is_comm == 1)
		xml_node_generic(e, node, 1);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "?xml") == 0)
		s_error("\x1b[1;31mError double XML header\x1b[0m", e);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "scene") == 0)
		xml_node_scene(e, node, 0);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "/scene>") == 0)
		xml_node_scene(e, node, 1);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "cam") == 0)
		xml_node_cam(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XMLSUB[0], "light") == 0)
		xml_node_light(e, node);
	else
		xml_process_node_obj(e, node);
}

void				xml_parse_nodes(t_env *e)
{
	int				i;

	ft_putendl("\x1b[1;29mParsing the scene...\x1b[0m");
	i = 0;
	if ((XML->nodes = ft_strsplit(e->scene_file, '<')) == NULL)
		s_error("\x1b[1;31mError getting nodes\x1b[0m", e);
	while (XML->nodes[i])
	{
		if (i == 0)
			xml_node_generic(e, XML->nodes[i], 0);
		else
			xml_process_node(e, XML->nodes[i]);
		i++;
	}
	ft_putendl("\n\x1b[1;29mFinished processing the scene!\x1b[0m\n");
}
