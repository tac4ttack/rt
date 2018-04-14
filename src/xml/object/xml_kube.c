/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_kube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:28:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 18:30:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_kube_data_m(t_env *e, char **att, t_node *kube_node, int *i)
{
	if (ft_strncmp(att[*i], "refract=\"", 9) != 0)
		s_error("\x1b[2;31mKube error, REFRACT expected in #9\x1b[0m", e);
	else
		xml_data_refract(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "opacity=\"", 9) != 0)
		s_error("\x1b[2;31mKube error, OPACITY expected in #10\x1b[0m", e);
	else
		xml_data_opacity(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "p_limit_pos=\"", 13) != 0)
		s_error("\x1b[2;31mKube error, P_LIMIT_POS expected in #11\x1b[0m", e);
	else
		xml_data_plane_limit_pos(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "p_limit_dir=\"", 13) != 0)
		s_error("\x1b[2;31mKube error, P_LIMIT_DIR expected in #12\x1b[0m", e);
	else
		xml_data_plane_limit_dir(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "flags=\"", 7) != 0)
		s_error("\x1b[1;31mKube error, FLAG expected in #13\x1b[0m", e);
	else
		xml_data_flag(e, att, i, kube_node);
}

static void	xml_kube_data_n(t_env *e, char **att, t_node *kube_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[1;31mKube error, COLOR expected in #5\x1b[0m", e);
	else
		xml_data_color(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[1;31mKube error, DIFFUSE expected in #6\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[1;31mKube error, SPECULAR expected in #7\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "reflex=\"", 8) != 0)
		s_error("\x1b[1;31mKube error, REFLEX expected in #8\x1b[0m", e);
	else
		xml_data_reflex(e, att, i, kube_node);
	xml_kube_data_m(e, att, kube_node, i);
}

static void	xml_kube_data(t_env *e, char **att, t_node *kube_node, int *i)
{
	if (xml_check_node_format(att, 10) != 0)
		s_error("\x1b[1;31mKube error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mKube error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mKube error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, kube_node);
	if (ft_strncmp(att[*i], "option=\"", 8) != 0)
		s_error("\x1b[1;31mKube error, OPTION expected in #3\x1b[0m", e);
	else
		xml_data_option(e, att, i, kube_node);
	xml_kube_data_n(e, att, kube_node, i);
}

void		xml_node_kube(t_env *e, char *node)
{
	t_node	*kube_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	kube_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_kube_data(e, tmp, kube_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError KUBE node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError KUBE node isn't closed\x1b[0m", e);
	kube_node->type = OBJ_KUBE;
	if (XML->node_lst == NULL)
		XML->node_lst = kube_node;
	else
		xml_list_add_first(&XML->node_lst, kube_node);
	xml_node_clean(tmp);
}
