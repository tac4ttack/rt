/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/01 21:08:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_cone_data_n(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[2;31mError in cone, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[2;31mError in cone, DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[2;31mError in cone, SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[2;31mError in cone, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, cone_node);
}

static void	xml_cone_data(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (xml_check_node_format(att, 2) != 0)
		s_error("\x1b[2;31mError CONE format\x1b[0m", e);
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in cone, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != (int)NCON - 1)
		s_error("\x1b[2;31mError in cone, ID is incorrect\x1b[0m", e);
	else
		cone_node->id = ft_atoi(att[(*i)++] + 4);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in cone, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in cone, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "angle=\"", 7) != 0)
		s_error("\x1b[2;31mError in cone, ANGLE expected in #3\x1b[0m", e);
	else
		xml_data_angle(e, att, i, cone_node);
	xml_cone_data_n(e, att, cone_node, i);
}

void		xml_node_cone(t_env *e, char *node)
{
	t_node	*cone_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	e->scene->n_cones++;
	cone_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cone_data(e, tmp, cone_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[2;31mError CONES node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[2;31mError CONES node isn't closed\x1b[0m", e);
	cone_node->type = 1;
	if (XML->node_lst == NULL)
		XML->node_lst = cone_node;
	else
		xml_list_add_first(&XML->node_lst, cone_node);
	xml_node_clean(tmp);
}

void		xml_allocate_cone(t_env *e)
{
	if (NCON > 0)
	{
		if (!(e->cones = malloc(sizeof(t_cone) * NCON)))
			s_error("\x1b[2;31mCan't create cones array\x1b[0m", e);
	}
	else
		e->cones = NULL;
}

void		xml_push_cone(t_env *e, t_node *list)
{
	e->cones[list->id].size = sizeof(t_cone);
	e->cones[list->id].id = OBJ_CONE;
	e->cones[list->id].pos = list->pos;
	e->cones[list->id].dir = list->dir;
	e->cones[list->id].angle = list->angle;
	e->cones[list->id].color = list->color;
	e->cones[list->id].diff = list->diff;
	e->cones[list->id].spec = list->spec;
	e->cones[list->id].reflex = list->reflex;
	e->gen->add(e->gen, (void*)&e->cones[list->id]);
}
