/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_paraboloid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 20:59:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/25 16:35:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_paraboloid_data_n(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mError in paraboloid, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "height=\"", 8) != 0)
		s_error("\x1b[1;31mError in paraboloid, HEIGHT expected in #5\x1b[0m", e);
	else
		xml_data_height(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mError in paraboloid, \
				DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mError in paraboloid, \
				SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[1;31mError in paraboloid, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mError in paraboloid, REFRACT expected in #8\x1b[0m", e);
	else
		xml_data_refract(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "opacity=\"", 6) != 0)
		s_error("\x1b[2;31mError in plane, OPACITY expected in #9\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, cyl_node);
}

static void	xml_paraboloid_data(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (xml_check_node_format(att, 8) != 0)
		s_error("\x1b[1;31mError in PARABOLOID format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mError in paraboloid, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mError in paraboloid, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mError in paraboloid, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, cyl_node);
	xml_paraboloid_data_n(e, att, cyl_node, i);
}

void		xml_node_paraboloid(t_env *e, char *node)
{
	t_node	*cyl_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	cyl_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_paraboloid_data(e, tmp, cyl_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError PARABOLOID node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError PARABOLOID node isn't closed\x1b[0m", e);
	cyl_node->type = OBJ_PARABOLOID;
	if (XML->node_lst == NULL)
		XML->node_lst = cyl_node;
	else
		xml_list_add_first(&XML->node_lst, cyl_node);
	xml_node_clean(tmp);
}

void		xml_push_paraboloid(t_env *e, t_node *list)
{
	t_paraboloid paraboloid;

	paraboloid.size = sizeof(t_paraboloid);
	paraboloid.id = e->current_index_objects;
	paraboloid.type = OBJ_PARABOLOID;
	paraboloid.pos = list->pos;
	paraboloid.base_dir = normalize_vect(list->dir);
	paraboloid.dir = normalize_vect(list->dir);
	paraboloid.radius = list->radius;
	paraboloid.color = list->color;
	paraboloid.height = list->height;
	paraboloid.diff = list->diff;
	paraboloid.spec = list->spec;
	paraboloid.reflex = list->reflex;
	paraboloid.refract = list->refract;
	paraboloid.opacity = list->opacity;
	e->gen_objects->add(e->gen_objects, (void*)&paraboloid);
}
