/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_ellipsoid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 17:32:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/03 18:13:25 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_ellipsoid_data_n(t_env *e, char **att, \
								t_node *ellipsoid_node, int *i)
{
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mEllipsoid error, DIFFUSE expected in #6\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mEllipsoid error, SPECULAR expected in #7\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[1;31mEllipsoid error, REFLEX expected in #8\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mEllipsoid error, REFRACT expected in #9\x1b[0m", e);
	else
		xml_data_refract(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "opacity=\"", 6) != 0)
		s_error("\x1b[2;31mEllipsoid error, OPACITY expected in #10\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, ellipsoid_node);
}

static void	xml_ellipsoid_data(t_env *e, char **att, \
								t_node *ellipsoid_node, int *i)
{
	if (xml_check_node_format(att, 7) != 0)
		s_error("\x1b[1;31mEllipsoid error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mEllipsoid error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mEllipsoid error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mEllipsoid error, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "axis_size=\"", 11) != 0)
		s_error("\x1b[1;31mEllipsoid error AXIS_SIZE expected in #4\x1b[0m", e);
	else
		xml_data_axis_size(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mEllipsoid error, COLOR expected in #5\x1b[0m", e);
	else
		xml_data_color(e, att, i, ellipsoid_node);
	xml_ellipsoid_data_n(e, att, ellipsoid_node, i);
}

void		xml_node_ellipsoid(t_env *e, char *node)
{
	t_node	*ellipsoid_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	ellipsoid_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_ellipsoid_data(e, tmp, ellipsoid_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError ELLIPSOID node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError ELLIPSOID node isn't closed\x1b[0m", e);
	ellipsoid_node->type = OBJ_ELLIPSOID;
	if (XML->node_lst == NULL)
		XML->node_lst = ellipsoid_node;
	else
		xml_list_add_first(&XML->node_lst, ellipsoid_node);
	xml_node_clean(tmp);
}

static void	xml_push_ellipsoid_effects(t_ellipsoid *ellipsoid)
{
	ellipsoid->limit_pos.x = 0;
	ellipsoid->limit_pos.y = 0;
	ellipsoid->limit_pos.z = 0;
	ellipsoid->limit_dir.x = 0;
	ellipsoid->limit_dir.y = 0;
	ellipsoid->limit_dir.z = 0;
	ellipsoid->waves_p1.x = 0.8;
	ellipsoid->waves_p1.y = 0.8;
	ellipsoid->waves_p1.z = 0.8;
	ellipsoid->waves_p2.x = 5;
	ellipsoid->waves_p2.y = 5;
	ellipsoid->waves_p2.z = 5;
	ellipsoid->check_size.x = 1;
	ellipsoid->check_size.y = 1;
	ellipsoid->diff_map_id = -1;
	ellipsoid->diff_map_size.x = 0;
	ellipsoid->diff_map_size.y = 0;
	ellipsoid->diff_map_size.z = 1;
}

void		xml_push_ellipsoid(t_env *e, t_node *list)
{
	t_ellipsoid ellipsoid;

	ellipsoid.size = sizeof(t_ellipsoid);
	ellipsoid.id = e->current_index_objects;
	ellipsoid.type = OBJ_ELLIPSOID;
	ellipsoid.flags = 0;
	ellipsoid.pos = list->pos;
	ellipsoid.dir = list->dir;
	ellipsoid.radius = list->radius;
	ellipsoid.color = list->color;
	ellipsoid.diff = list->diff;
	ellipsoid.spec = list->spec;
	ellipsoid.reflex = list->reflex;
	ellipsoid.refract = list->refract;
	ellipsoid.opacity = list->opacity;
	ellipsoid.axis_size = list->axis_size;
	xml_push_ellipsoid_effects(&ellipsoid);
	e->gen_objects->add(e->gen_objects, (void*)&ellipsoid);
}
