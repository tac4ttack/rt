/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 23:38:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_cone_data_lim(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (ft_strncmp(att[*i], "p_limit_pos=\"", 13) != 0)
		s_error("\x1b[2;31mCone error, P_LIMIT_POS expected in #10\x1b[0m", e);
	else
		xml_data_plane_limit_pos(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "p_limit_dir=\"", 13) != 0)
		s_error("\x1b[2;31mCone error, P_LIMIT_DIR expected in #11\x1b[0m", e);
	else
		xml_data_plane_limit_dir(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "min=\"", 5) != 0)
		s_error("\x1b[1;31mCone error, MIN expected in #12\x1b[0m", e);
	else
		xml_data_min_max(e, att, i, &cone_node->min);
	if (ft_strncmp(att[*i], "max=\"", 5) != 0)
		s_error("\x1b[1;31mCone error, MAX expected in #13\x1b[0m", e);
	else
		xml_data_min_max(e, att, i, &cone_node->max);
	if (ft_strncmp(att[*i], "flags=\"", 7) != 0)
		s_error("\x1b[1;31mCone error, FLAG expected in #14\x1b[0m", e);
	else
		xml_data_flag(e, att, i, cone_node);
}

static void	xml_cone_data_m(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (ft_strncmp(att[*i], "refract=\"", 9) != 0)
		s_error("\x1b[2;31mCone error, REFRACT expected in #8\x1b[0m", e);
	else
		xml_data_refract(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "opacity=\"", 9) != 0)
		s_error("\x1b[2;31mCone error, OPACITY expected in #9\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, cone_node);
	xml_cone_data_lim(e, att, cone_node, i);
}

static void	xml_cone_data_n(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mCone error, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mCone error, DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mCone error, SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "reflex=\"", 8) != 0)
		s_error("\x1b[1;31mCone error, REFLEX expected in #7\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, cone_node);
	xml_cone_data_m(e, att, cone_node, i);
}

static void	xml_cone_data(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (xml_check_node_format(att, 2) != 0)
		s_error("\x1b[1;31mCone error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mCone error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mCone error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cone_node);
	if (ft_strncmp(att[*i], "angle=\"", 7) != 0)
		s_error("\x1b[1;31mCone error, ANGLE expected in #3\x1b[0m", e);
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
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	cone_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cone_data(e, tmp, cone_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError CONES node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError CONES node isn't closed\x1b[0m", e);
	cone_node->type = OBJ_CONE;
	if (XML->node_lst == NULL)
		XML->node_lst = cone_node;
	else
		xml_list_add_first(&XML->node_lst, cone_node);
	xml_node_clean(&tmp);
}
