/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:26 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 18:14:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_box_data_n(t_env *e, char **att, t_node *box_node, int *i)
{
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mBox error, SPECULAR expected in #5\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, box_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[1;31mBox error, REFLEX expected in #6\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, box_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mBox error, REFRACT expected in #7\x1b[0m", e);
	else
		xml_data_refract(e, att, i, box_node);
	if (ft_strncmp(att[*i], "opacity=\"", 6) != 0)
		s_error("\x1b[2;31mBox error, OPACITY expected in #8\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, box_node);
	if (ft_strncmp(att[*i], "min=\"", 5) != 0)
		s_error("\x1b[2;31mBox error, MIN expected in #9\x1b[0m", e);
	else
		xml_data_min_max(e, att, i, &box_node->min);
	if (ft_strncmp(att[*i], "max=\"", 5) != 0)
		s_error("\x1b[2;31mBox error, MAX expected in #10\x1b[0m", e);
	else
		xml_data_min_max(e, att, i, &box_node->max);
}

static void	xml_box_data(t_env *e, char **att, t_node *box_node, int *i)
{
	if (xml_check_node_format(att, 10) != 0)
		s_error("\x1b[1;31mBox error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mBox error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, box_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mBox error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, box_node);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mBox error, COLOR expected in #3\x1b[0m", e);
	else
		xml_data_color(e, att, i, box_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mBox error, DIFFUSE expected in #4\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, box_node);
	xml_box_data_n(e, att, box_node, i);
}

void		xml_node_box(t_env *e, char *node)
{
	t_node	*box_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	box_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_box_data(e, tmp, box_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError BOX node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError BOX node isn't closed\x1b[0m", e);
	box_node->type = OBJ_BOX;
	if (XML->node_lst == NULL)
		XML->node_lst = box_node;
	else
		xml_list_add_first(&XML->node_lst, box_node);
	xml_node_clean(tmp);
}

static void	xml_push_box_effects(t_box *box)
{
	box->limit_pos.x = 0;
	box->limit_pos.y = 0;
	box->limit_pos.z = 0;
	box->limit_dir.x = 0;
	box->limit_dir.y = 0;
	box->limit_dir.z = 0;
	box->waves_p1.x = 0.8;
	box->waves_p1.y = 0.8;
	box->waves_p1.z = 0.8;
	box->waves_p2.x = 5;
	box->waves_p2.y = 5;
	box->waves_p2.z = 5;
	box->check_size.x = 1;
	box->check_size.y = 1;
	box->diff_map_id = -1;
	box->diff_map_size.x = 0;
	box->diff_map_size.y = 0;
	box->diff_map_size.z = 1;
}

void		xml_push_box(t_env *e, t_node *list)
{
	t_box box;

	box.size = sizeof(t_box);
	box.id = e->current_index_objects;
	box.type = OBJ_BOX;
	box.flags = 0;
	box.pos = list->pos;
	box.dir = list->dir;
	box.color = list->color;
	box.diff = list->diff;
	box.spec = list->spec;
	box.reflex = list->reflex;
	box.refract = list->refract;
	box.opacity = list->opacity;
	box.min = list->min;
	box.max = list->max;
	xml_push_box_effects(&box);
	e->gen_objects->add(e->gen_objects, (void*)&box);
}
