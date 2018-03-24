/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:46 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/24 19:50:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_plane_data_n(t_env *e, char **att, t_node *plane_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mError in plane, COLOR expected in #3\x1b[0m", e);
	else
		xml_data_color(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mError in plane, DIFFUSE expected in #4\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mError in plane, SPECULAR expected in #5\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[1;31mError in plane, REFLEX expected in #6\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mError in plane, REFRACT expected in #7\x1b[0m", e);
	else
		xml_data_refract(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "opacity=\"", 6) != 0)
		s_error("\x1b[2;31mError in plane, OPACITY expected in #8\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, plane_node);
}

static void	xml_plane_data(t_env *e, char **att, t_node *plane_node, int *i)
{
	if (xml_check_node_format(att, 5) != 0)
		s_error("\x1b[1;31mError PLANE format\x1b[0m", e);
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[1;31mError in plane, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != (int)NPLA - 1)
		s_error("\x1b[1;31mError in plane, ID is incorrect\x1b[0m", e);
	else
		plane_node->id = ft_atoi(att[(*i)++] + 4);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mError in plane, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "normale=\"", 9) != 0)
		s_error("\x1b[1;31mError in plane, NORMALE expected in #2\x1b[0m", e);
	else
		xml_data_normale(e, att, i, plane_node);
	xml_plane_data_n(e, att, plane_node, i);
}

void		xml_node_plane(t_env *e, char *node)
{
	t_node	*plane_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	e->scene->n_planes++;
	plane_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_plane_data(e, tmp, plane_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError PLANE node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError PLANE node isn't closed\x1b[0m", e);
	plane_node->type = OBJ_PLANE;
	if (XML->node_lst == NULL)
		XML->node_lst = plane_node;
	else
		xml_list_add_first(&XML->node_lst, plane_node);
	xml_node_clean(tmp);
}

void		xml_allocate_plane(t_env *e)
{
	if (NPLA > 0)
	{
		if (!(e->planes = malloc(sizeof(t_plane) * NPLA)))
			s_error("\x1b[1;31mCan't create planes array\x1b[0m", e);
	}
	else
		e->planes = NULL;
}

void		xml_push_plane(t_env *e, t_node *list)
{
	e->planes[list->id].size = sizeof(t_plane);
	e->planes[list->id].id = OBJ_PLANE;
	e->planes[list->id].pos = list->pos;
	e->planes[list->id].normale = list->normale;
	e->planes[list->id].color = list->color;
	e->planes[list->id].diff = list->diff;
	e->planes[list->id].spec = list->spec;
	e->planes[list->id].reflex = list->reflex;
	e->planes[list->id].refract = list->refract;
	e->planes[list->id].opacity = list->opacity;
	e->gen_objects->add(e->gen_objects, (void*)&e->planes[list->id]);
}
