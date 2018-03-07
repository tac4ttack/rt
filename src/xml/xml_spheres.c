/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:26 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/07 18:42:22 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_sphere_data_n(t_env *e, char **att, t_node *sphere_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mError in sphere, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mError in sphere, DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mError in sphere, SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "reflex=\"", 6) != 0)
		s_error("\x1b[1;31mError in sphere, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "refract=\"", 6) != 0)
		s_error("\x1b[2;31mError in sphere, REFRACT expected in #7\x1b[0m", e);
	else
		xml_data_refract(e, att, i, sphere_node);
}

static void	xml_sphere_data(t_env *e, char **att, t_node *sphere_node, int *i)
{
	if (xml_check_node_format(att, 6) != 0)
		s_error("\x1b[1;31mError SPHERE format\x1b[0m", e);
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[1;31mError in sphere, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != (int)NSPH - 1)
		s_error("\x1b[1;31mError in sphere, ID is incorrect\x1b[0m", e);
	else
		sphere_node->id = ft_atoi(att[(*i)++] + 4);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mError in sphere, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mError in sphere, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, sphere_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mError in sphere, RADIUS expected in #3\x1b[0m", e);
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
	e->scene->n_spheres++;
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
	sphere_node->type = 5;
	if (XML->node_lst == NULL)
		XML->node_lst = sphere_node;
	else
		xml_list_add_first(&XML->node_lst, sphere_node);
	xml_node_clean(tmp);
}

void		xml_allocate_sphere(t_env *e)
{
	if (NSPH > 0)
	{
		if (!(e->spheres = malloc(sizeof(t_sphere) * NSPH)))
			s_error("\x1b[1;31mCan't create spheres array\x1b[0m", e);
	}
	else
		e->spheres = NULL;
}

void		xml_push_sphere(t_env *e, t_node *list)
{
	e->spheres[list->id].size = sizeof(t_sphere);
	e->spheres[list->id].id = OBJ_SPHERE;
	e->spheres[list->id].pos = list->pos;
	e->spheres[list->id].dir = list->dir;
	e->spheres[list->id].radius = list->radius;
	e->spheres[list->id].color = list->color;
	e->spheres[list->id].diff = list->diff;
	e->spheres[list->id].spec = list->spec;
	e->spheres[list->id].reflex = list->reflex;
	e->spheres[list->id].refract = list->refract;
	e->gen_objects->add(e->gen_objects, (void*)&e->spheres[list->id]);
}
