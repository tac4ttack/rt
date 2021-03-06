/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cameras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:04 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 17:18:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_data_cam_fov(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading FOV value\x1b[0m", e);
		node->fov = ft_atof(attributes[(*i)++] + 5);
		if (node->fov < 5 || node->fov > 120)
			s_error("\x1b[1;31mError FOV must be between 5 and 120\x1b[0m", e);
	}
	else
		s_error("\x1b[1;31mError reading FOV from scene\x1b[0m", e);
}

static void	xml_cam_data(t_env *e, char **att, t_node *cam_node, int *i)
{
	if (xml_check_node_format(att, 1) != 0)
		s_error("\x1b[1;31mCamera error format\x1b[0m", e);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[1;31mCamera error, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cam_node);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[1;31mCamera error, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cam_node);
	if (ft_strncmp(att[*i], "fov=\"", 5) != 0)
		s_error("\x1b[1;31mCamera error, FOV expected in #3\x1b[0m", e);
	else
		xml_data_cam_fov(e, att, i, cam_node);
}

void		xml_node_cam(t_env *e, char *node)
{
	t_node	*cam_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[1;31mError node is outside scene\x1b[0m", e);
	cam_node = xml_list_new(0);
	cam_node->id = e->scene->n_cams;
	e->scene->n_cams++;
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cam_data(e, tmp, cam_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[1;31mError CAMERA node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[1;31mError CAMERA node isn't closed\x1b[0m", e);
	cam_node->type = OBJ_CAM;
	if (XML->node_lst == NULL)
		XML->node_lst = cam_node;
	else
		xml_list_add_first(&XML->node_lst, cam_node);
	xml_node_clean(&tmp);
}

void		xml_allocate_cam(t_env *e)
{
	if (NCAM > 0)
	{
		if (!(e->cameras = malloc(sizeof(t_cam) * NCAM)))
			s_error("\x1b[1;31mCan't create cameras array\x1b[0m", e);
	}
	else
		e->cameras = NULL;
}

void		xml_push_cam(t_env *e, t_node *list)
{
	e->cameras[list->id].id = list->id;
	e->cameras[list->id].pos = list->pos;
	e->cameras[list->id].dir = list->dir;
	e->cameras[list->id].dir.x = 0;
	e->cameras[list->id].dir.y = 0;
	e->cameras[list->id].dir.z = 1;
	e->cameras[list->id].fov = list->fov;
	e->cameras[list->id].pitch = list->dir.x;
	e->cameras[list->id].yaw = list->dir.y;
	e->cameras[list->id].roll = list->dir.z;
}
