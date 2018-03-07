/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:18 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/04 21:23:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_cylinder_data_n(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[2;31mError in cylinder, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "height=\"", 8) != 0)
		s_error("\x1b[2;31mError in cylinder, HEIGHT expected in #5\x1b[0m", e);
	else
		xml_data_height(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[2;31mError in cylinder, \
				DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[2;31mError in cylinder, \
				SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[2;31mError in cylinder, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mError in cylinder, REFRACT expected in #8\x1b[0m", e);
	else
		xml_data_refract(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "opacity=\"", 6) != 0)
		s_error("\x1b[2;31mError in plane, OPACITY expected in #9\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, cyl_node);
}

static void	xml_cylinder_data(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (xml_check_node_format(att, 3) != 0)
		s_error("\x1b[2;31mError CYLINDER format\x1b[0m", e);
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in cylinder, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != (int)NCYL - 1)
		s_error("\x1b[2;31mError in cylinder, ID is incorrect\x1b[0m", e);
	else
		cyl_node->id = ft_atoi(att[(*i)++] + 4);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in cylinder, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in cylinder, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cyl_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[2;31mError in cylinder, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, cyl_node);
	xml_cylinder_data_n(e, att, cyl_node, i);
}

void		xml_node_cylinder(t_env *e, char *node)
{
	t_node	*cyl_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	e->scene->n_cylinders++;
	cyl_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cylinder_data(e, tmp, cyl_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[2;31mError CYLINDER node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[2;31mError CYLINDER node isn't closed\x1b[0m", e);
	cyl_node->type = 2;
	if (XML->node_lst == NULL)
		XML->node_lst = cyl_node;
	else
		xml_list_add_first(&XML->node_lst, cyl_node);
	xml_node_clean(tmp);
}

void		xml_allocate_cyl(t_env *e)
{
	if (NCYL > 0)
	{
		if (!(e->cylinders = malloc(sizeof(t_cylinder) * NCYL)))
			s_error("\x1b[2;31mCan't create cylinders array\x1b[0m", e);
	}
	else
		e->cylinders = NULL;
}

void		xml_push_cyl(t_env *e, t_node *list)
{
	e->cylinders[list->id].size = sizeof(t_cylinder);
	e->cylinders[list->id].id = OBJ_CYLINDER;
	e->cylinders[list->id].pos = list->pos;
	e->cylinders[list->id].base_dir = normalize_vect(list->dir);
	e->cylinders[list->id].dir = normalize_vect(list->dir);
	e->cylinders[list->id].radius = list->radius;
	e->cylinders[list->id].color = list->color;
	e->cylinders[list->id].height = list->height;
	e->cylinders[list->id].diff = list->diff;
	e->cylinders[list->id].spec = list->spec;
	e->cylinders[list->id].reflex = list->reflex;
	e->cylinders[list->id].refract = list->refract;
	e->cylinders[list->id].opacity = list->opacity;
	e->gen_objects->add(e->gen_objects, (void*)&e->cylinders[list->id]);
}
