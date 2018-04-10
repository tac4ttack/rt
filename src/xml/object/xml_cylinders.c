/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:18 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/10 18:37:09 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_cylinder_data_n(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mCylinder error, DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mCylinder error, SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "reflex=\"", 8) != 0)
		s_error("\x1b[1;31mCylinder error, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "refract=\"", 9) != 0)
		s_error("\x1b[2;31mCylinder error REFRACT expected in #8\x1b[0m", e);
	else
		xml_data_refract(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "opacity=\"", 9) != 0)
		s_error("\x1b[2;31mCylinder error, OPACITY expected in #9\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "p_limit_pos=\"", 13) != 0)
		s_error("\x1b[2;31mCylinder error, P_LIMIT_POS expected in #10\x1b[0m", e);
	else
		xml_data_plane_limit_pos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "p_limit_dir=\"", 13) != 0)
		s_error("\x1b[2;31mCylinder error, P_LIMIT_DIR expected in #11\x1b[0m", e);
	else
		xml_data_plane_limit_dir(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "flags=\"", 7) != 0)
		s_error("\x1b[1;31mCylinder error, FLAG expected in #12\x1b[0m", e);
	else
		xml_data_flag(e, att, i, cyl_node);
}

static void	xml_cylinder_data(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (xml_check_node_format(att, 3) != 0)
		s_error("\x1b[1;31mCylinder error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mCylinder error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mCylinder error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mCylinder error, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mCylinder error, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cyl_node);
	xml_cylinder_data_n(e, att, cyl_node, i);
}

void		xml_node_cylinder(t_env *e, char *node)
{
	t_node	*cyl_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	cyl_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cylinder_data(e, tmp, cyl_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError CYLINDER node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError CYLINDER node isn't closed\x1b[0m", e);
	cyl_node->type = OBJ_CYLINDER;
	if (XML->node_lst == NULL)
		XML->node_lst = cyl_node;
	else
		xml_list_add_first(&XML->node_lst, cyl_node);
	xml_node_clean(tmp);
}

static void	xml_push_cylinder_effects(t_cylinder *cylinder)
{
	cylinder->waves_p1.x = 0.8;
	cylinder->waves_p1.y = 0.8;
	cylinder->waves_p1.z = 0.8;
	cylinder->waves_p2.x = 5;
	cylinder->waves_p2.y = 5;
	cylinder->waves_p2.z = 5;
	cylinder->check_size.x = 1;
	cylinder->check_size.y = 1;
	cylinder->diff_map_id = -1;
	cylinder->diff_offset.x = 0;
	cylinder->diff_offset.y = 0;
	cylinder->diff_ratio.x = 1;
	cylinder->diff_ratio.y = 1;
	cylinder->u_axis = cross_vect(cylinder->dir);
}

void		xml_push_cyl(t_env *e, t_node *list)
{
	t_cylinder cylinder;

	cylinder.size = sizeof(t_cylinder);
	cylinder.id = e->current_index_objects;
	cylinder.type = OBJ_CYLINDER;
	cylinder.flags = list->flags;
	cylinder.pos = list->pos;
	cylinder.radius = list->radius;
	cylinder.color = list->color;
	cylinder.diff = list->diff;
	cylinder.spec = list->spec;
	cylinder.reflex = list->reflex;
	cylinder.refract = list->refract;
	cylinder.opacity = list->opacity;
	cylinder.limit_pos = list->limit_pos;
	cylinder.limit_dir = list->limit_dir;
	cylinder.dir = normalize_vect(list->dir);
	xml_push_cylinder_effects(&cylinder);
	e->gen_objects->add(e->gen_objects, (void*)&cylinder);
}
