/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:46 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 18:31:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_plane_data_m(t_env *e, char **att, t_node *plane_node, int *i)
{
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[1;31mPlane error, RADIUS expected in #9\x1b[0m", e);
	else
		xml_data_plane_radius(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "p_limit_pos=\"", 13) != 0)
		s_error("\x1b[2;31mPlane error, P_LIMIT_POS expected in #10\x1b[0m", e);
	else
		xml_data_plane_limit_pos(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "p_limit_dir=\"", 13) != 0)
		s_error("\x1b[2;31mPlane error, P_LIMIT_DIR expected in #11\x1b[0m", e);
	else
		xml_data_plane_limit_dir(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "flags=\"", 7) != 0)
		s_error("\x1b[1;31mPlane error, FLAG expected in #12\x1b[0m", e);
	else
		xml_data_flag(e, att, i, plane_node);
}

static void	xml_plane_data_n(t_env *e, char **att, t_node *plane_node, int *i)
{
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mPlane error, SPECULAR expected in #5\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "reflex=\"", 8) != 0)
		s_error("\x1b[1;31mPlane error, REFLEX expected in #6\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "refract=\"", 9) != 0)
		s_error("\x1b[2;31mPlane error, REFRACT expected in #7\x1b[0m", e);
	else
		xml_data_refract(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "opacity=\"", 9) != 0)
		s_error("\x1b[2;31mPlane error, OPACITY expected in #8\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, plane_node);
	xml_plane_data_m(e, att, plane_node, i);
}

static void	xml_plane_data(t_env *e, char **att, t_node *plane_node, int *i)
{
	if (xml_check_node_format(att, 5) != 0)
		s_error("\x1b[1;31mPlane error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mPlane error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "normale=\"", 9) != 0)
		s_error("\x1b[1;31mPlane error, NORMALE expected in #2\x1b[0m", e);
	else
		xml_data_normale(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mPlane error, COLOR expected in #3\x1b[0m", e);
	else
		xml_data_color(e, att, i, plane_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mPlane error, DIFFUSE expected in #4\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, plane_node);
	xml_plane_data_n(e, att, plane_node, i);
}

void		xml_node_plane(t_env *e, char *node)
{
	t_node	*plane_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
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
