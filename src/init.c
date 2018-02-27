/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:46:22 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/27 16:19:19 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		load_obj(t_env *e)
{
	xml_allocate_cam(e);
	xml_allocate_cone(e);
	xml_allocate_cyl(e);
	xml_allocate_light(e);
	xml_allocate_plane(e);
	xml_allocate_sphere(e);
}

void		load_scene(t_env *e)
{
	t_node	*list;

	load_obj(e);
	list = XML->node_lst;
	while (list != NULL)
	{
		if (list->type == 0)
			xml_push_cam(e, list);
		if (list->type == 1)
			xml_push_cone(e, list);
		if (list->type == 2)
			xml_push_cyl(e, list);
		if (list->type == 3)
			xml_push_light(e, list);
		if (list->type == 4)
			xml_push_plane(e, list);
		if (list->type == 5)
			xml_push_sphere(e, list);
		list = list->next;
	}
	xml_list_clean(e, &XML->node_lst);
}

void		frame_init(t_env *e)
{
	int		bpp;
	int		row;
	int		endian;

	if (!(e->frame = malloc(sizeof(t_frame))))
		s_error("\x1b[2;31mCan't initialize the frame\x1b[0m", e);
	e->frame->w = e->win_w;
	e->frame->h = e->win_h;
	if (!(e->frame->ptr = mlx_new_image(e->mlx, e->frame->w, e->frame->h)))
		s_error("\x1b[2;31mCan't create new mlx image\x1b[0m", e);
	if (!(e->frame->pix = mlx_get_data_addr(e->frame->ptr, \
							&(bpp), &(row), &(endian))))
		s_error("\x1b[2;31mCan't create image address\x1b[0m", e);
	e->frame->bpp = bpp;
	e->frame->row = row;
	e->frame->endian = endian;
	load_scene(e);
}

void		env_init(t_env *e)
{
	e->scene->depth = 0;
	e->scene->tor_count = pow(2, e->scene->depth + 1) - 1;
	e->win_w = e->scene->win_w;
	e->win_h = e->scene->win_h;
	e->count = e->win_h * e->win_w;
	e->debug = DBUG;
	e->cen_x = e->win_w / 2;
	e->cen_y = e->win_h / 2;
	e->gpu = IS_GPU;
	e->run = 0;
	e->tree = tor_create(e);
	//printf("t_light_ray			: %-20lu\n", sizeof(t_light_ray));
	printf("t_cam 				: %-20lu\n", sizeof(t_cam));
	printf("t_cone 				: %-20lu\n", sizeof(t_cone));
	printf("t_cylinder 			: %-20lu\n", sizeof(t_cylinder));
	printf("t_light 			: %-20lu\n", sizeof(t_light));
	printf("t_plane 			: %-20lu\n", sizeof(t_plane));
	printf("t_sphere 			: %-20lu\n", sizeof(t_sphere));
	printf("t_tor 				: %-20lu\n", sizeof(t_tor));
	printf("t_scene 			: %-20lu\n", sizeof(t_scene));
}

void		init(t_env *e, int ac, char *av)
{
	ft_bzero(e, sizeof(t_env));
	ft_bzero(&e->target_obj, sizeof(t_hit));
	if (!(e->scene = malloc(sizeof(t_scene))))
		s_error("\x1b[2;31mCan't initialize scene buffer\x1b[0m", e);
	ft_bzero(e->scene, sizeof(t_scene));
	xml_init(e, ac, av);
	env_init(e);
	if (!(e->mlx = mlx_init()))
		s_error("\x1b[2;31mError can't initialize minilibx\x1b[0m", e);
	if (!(e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "RT")))
		s_error("\x1b[2;31mError minilibx window creation failed\x1b[0m", e);
	frame_init(e);
	if (opencl_init(e, e->count * 4) != 0)
	{
		e->gpu = 0;
		opencl_init(e, e->count * 4);
	}
}
