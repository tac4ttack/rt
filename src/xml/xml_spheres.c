/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:26 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 19:25:14 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_sphere_data_n(t_env *e, char **att, t_node *sphere_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mSphere error, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mSphere error, DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mSphere error, SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[1;31mSphere error, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mSphere error, REFRACT expected in #8\x1b[0m", e);
	else
		xml_data_refract(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "opacity=\"", 6) != 0)
		s_error("\x1b[2;31mSphere error, OPACITY expected in #9\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, sphere_node);
}

static void	xml_sphere_data(t_env *e, char **att, t_node *sphere_node, int *i)
{
	if (xml_check_node_format(att, 6) != 0)
		s_error("\x1b[1;31mSphere error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mSphere error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mSphere error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mSphere error, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, sphere_node);
	xml_sphere_data_n(e, att, sphere_node, i);
}

void		xml_node_sphere(t_env *e, char *node)
{
	t_node	*sphere_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	sphere_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_sphere_data(e, tmp, sphere_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError SPHERE node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError SPHERE node isn't closed\x1b[0m", e);
	sphere_node->type = OBJ_SPHERE;
	if (XML->node_lst == NULL)
		XML->node_lst = sphere_node;
	else
		xml_list_add_first(&XML->node_lst, sphere_node);
	xml_node_clean(tmp);
}

static void	xml_push_sphere_effects(t_sphere *sphere)
{
	sphere->limit_pos.x = 0;
	sphere->limit_pos.y = 0;
	sphere->limit_pos.z = 0;
	sphere->limit_dir.x = 0;
	sphere->limit_dir.y = 0;
	sphere->limit_dir.z = 0;
	sphere->waves_p1.x = 0.8;
	sphere->waves_p1.y = 0.8;
	sphere->waves_p1.z = 0.8;
	sphere->waves_p2.x = 5;
	sphere->waves_p2.y = 5;
	sphere->waves_p2.z = 5;
	sphere->check_size.x = 1;
	sphere->check_size.y = 1;
	sphere->diff_map_id = -1;
	sphere->diff_offset.x = 0;
	sphere->diff_offset.y = 0;
	sphere->diff_ratio.x = 1;
	sphere->diff_ratio.y = 1;
}

void		xml_push_sphere(t_env *e, t_node *list)
{
	t_sphere sphere;

	sphere.size = sizeof(t_sphere);
	sphere.id = e->current_index_objects;
	sphere.type = OBJ_SPHERE;
	sphere.pos = list->pos;
	sphere.flags = 0;
	sphere.dir = list->dir;
	sphere.radius = list->radius;
	sphere.color = list->color;
	sphere.diff = list->diff;
	sphere.spec = list->spec;
	sphere.reflex = list->reflex;
	sphere.refract = list->refract;
	sphere.opacity = list->opacity;
	xml_push_sphere_effects(&sphere);
	e->gen_objects->add(e->gen_objects, (void*)&sphere);
}
