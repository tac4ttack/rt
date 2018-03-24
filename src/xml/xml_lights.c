/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:58 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/24 19:50:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_light_data_v(t_env *e, char **att, t_node *light_node, int *i)
{
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mError in light, DIR expected in #3\x1b[0m", e);
	else
		xml_data_dir(e, att, i, light_node);
	if (ft_strncmp(att[*i], "brightness=\"", 12) != 0)
		s_error("\x1b[1;31mError in light BRIGHTNESS expected in #4\x1b[0m", e);
	else
		xml_data_brightness(e, att, i, light_node);
	if (ft_strncmp(att[*i], "shrink=\"", 8) != 0)
		s_error("\x1b[1;31mError in light, SHRINK expected in #4\x1b[0m", e);
	else
		xml_data_shrink(e, att, i, light_node);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mError in light, COLOR expected in #5\x1b[0m", e);
	else
		xml_data_color(e, att, i, light_node);
}

static void	xml_light_data(t_env *e, char **att, t_node *light_node, int *i)
{
	if (xml_check_node_format(att, 4) != 0)
		s_error("\x1b[1;31mError LIGHT format\x1b[0m", e);
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[1;31mError in light, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != (int)NLIG - 1)
		s_error("\x1b[1;31mError in light, ID is incorrect\x1b[0m", e);
	else
		light_node->id = ft_atoi(att[(*i)++] + 4);
	if (ft_strncmp(att[*i], "type=\"", 6) != 0)
		s_error("\x1b[1;31mError in light, TYPE expected in #1\x1b[0m", e);
	else
		xml_data_type(e, att, i, light_node);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mError in light, POS expected in #2\x1b[0m", e);
	else
		xml_data_pos(e, att, i, light_node);
	xml_light_data_v(e, att, light_node, i);
}

void		xml_node_light(t_env *e, char *node)
{
	t_node	*light_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	e->scene->n_lights++;
	light_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_light_data(e, tmp, light_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError LIGHT node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError LIGHT node isn't closed\x1b[0m", e);
	light_node->type = OBJ_LIGHT;
	if (XML->node_lst == NULL)
		XML->node_lst = light_node;
	else
		xml_list_add_first(&XML->node_lst, light_node);
	xml_node_clean(tmp);
}

void		xml_allocate_light(t_env *e)
{
	if (NLIG > 0)
	{
		if (!(e->lights = malloc(sizeof(t_light) * NLIG)))
			s_error("\x1b[1;31mCan't create lights array\x1b[0m", e);
	}
	else
		e->lights = NULL;
}

void		xml_push_light(t_env *e, t_node *list)
{
	e->lights[list->id].size = sizeof(t_light);
	//e->lights[list->id].id = list->light; //
	e->lights[list->id].type = list->light;
	e->lights[list->id].pos = list->pos;
	e->lights[list->id].dir = list->dir;
	e->lights[list->id].brightness = list->brightness;
	e->lights[list->id].shrink = list->shrink;
	e->lights[list->id].color = list->color;
	e->gen_lights->add(e->gen_lights, (void *)&e->lights[list->id]);
}
