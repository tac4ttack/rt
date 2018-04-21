/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_ellipsoid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 17:32:51 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/21 23:41:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_ellipsoid_data_m(t_env *e, char **att, \
								t_node *ellipsoid_node, int *i)
{
	if (ft_strncmp(att[*i], "opacity=\"", 9) != 0)
		s_error("\x1b[2;31mEllipsoid error, OPACITY expected in #10\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "p_limit_pos=\"", 13) != 0)
		s_error("\x1b[2;31mEllipsoid error, P_LIMIT_POS expected in #10\x1b[0m",
																			e);
	else
		xml_data_plane_limit_pos(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "p_limit_dir=\"", 13) != 0)
		s_error("\x1b[2;31mEllipsoid error, P_LIMIT_DIR expected in #11\x1b[0m",
																			e);
	else
		xml_data_plane_limit_dir(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "min=\"", 5) != 0)
		s_error("\x1b[1;31mEllipsoid error, MIN expected in #12\x1b[0m", e);
	else
		xml_data_min_max(e, att, i, &ellipsoid_node->min);
	if (ft_strncmp(att[*i], "max=\"", 5) != 0)
		s_error("\x1b[1;31mEllipsoid error, MAX expected in #13\x1b[0m", e);
	else
		xml_data_min_max(e, att, i, &ellipsoid_node->max);
	if (ft_strncmp(att[*i], "flags=\"", 7) != 0)
		s_error("\x1b[1;31mEllipsoid error, FLAG expected in #14\x1b[0m", e);
	else
		xml_data_flag(e, att, i, ellipsoid_node);
}

static void	xml_ellipsoid_data_n(t_env *e, char **att, \
								t_node *ellipsoid_node, int *i)
{
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mEllipsoid error, DIFFUSE expected in #6\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mEllipsoid error, SPECULAR expected in #7\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "reflex=\"", 8) != 0)
		s_error("\x1b[1;31mEllipsoid error, REFLEX expected in #8\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "refract=\"", 9) != 0)
		s_error("\x1b[2;31mEllipsoid error, REFRACT expected in #9\x1b[0m", e);
	else
		xml_data_refract(e, att, i, ellipsoid_node);
	xml_ellipsoid_data_m(e, att, ellipsoid_node, i);
}

static void	xml_ellipsoid_data(t_env *e, char **att, \
								t_node *ellipsoid_node, int *i)
{
	if (xml_check_node_format(att, 7) != 0)
		s_error("\x1b[1;31mEllipsoid error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mEllipsoid error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mEllipsoid error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mEllipsoid error, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "axis_size=\"", 11) != 0)
		s_error("\x1b[1;31mEllipsoid error AXIS_SIZE expected in #4\x1b[0m", e);
	else
		xml_data_axis_size(e, att, i, ellipsoid_node);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mEllipsoid error, COLOR expected in #5\x1b[0m", e);
	else
		xml_data_color(e, att, i, ellipsoid_node);
	xml_ellipsoid_data_n(e, att, ellipsoid_node, i);
}

void		xml_node_ellipsoid(t_env *e, char *node)
{
	t_node	*ellipsoid_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	ellipsoid_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_ellipsoid_data(e, tmp, ellipsoid_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError ELLIPSOID node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError ELLIPSOID node isn't closed\x1b[0m", e);
	ellipsoid_node->type = OBJ_ELLIPSOID;
	if (XML->node_lst == NULL)
		XML->node_lst = ellipsoid_node;
	else
		xml_list_add_first(&XML->node_lst, ellipsoid_node);
	xml_node_clean(&tmp);
}
