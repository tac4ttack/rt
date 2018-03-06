/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:46:22 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/06 19:52:45 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		load_obj(t_env *e)
{
	ft_putendl("\x1b[1;32mFetching scene objects...\x1b[0m");
	xml_allocate_cam(e);
	xml_allocate_cone(e);
	xml_allocate_cyl(e);
	xml_allocate_light(e);
	xml_allocate_plane(e);
	xml_allocate_sphere(e);
	ft_putendl("\x1b[1;32mScene objects fetched!\x1b[0m");
}

void		load_scene(t_env *e)
{
	t_node	*list;

	ft_putendl("\n\x1b[1;32m/\\ Loading scene /\\\x1b[0m\n");
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
	ft_putendl("\x1b[1;32mSuccessfully loaded the scene!\n\x1b[0m");
}

void		frame_init(t_env *e)
{
	int		bpp;
	int		row;
	int		endian;

	if (!(e->frame = malloc(sizeof(t_frame))))
		s_error("\x1b[1;31mCan't initialize the frame\x1b[0m", e);
	e->frame->w = e->win_w;
	e->frame->h = e->win_h;
	if (!(e->frame->ptr = mlx_new_image(e->mlx, e->frame->w, e->frame->h)))
		s_error("\x1b[1;31mCan't create new mlx image\x1b[0m", e);
	if (!(e->frame->pix = mlx_get_data_addr(e->frame->ptr, \
							&(bpp), &(row), &(endian))))
		s_error("\x1b[1;31mCan't create image address\x1b[0m", e);
	e->frame->bpp = bpp;
	e->frame->row = row;
	e->frame->endian = endian;
}

void		env_init(t_env *e)
{
	ft_putendl("\n\x1b[1;32m/\\ Initializing RT environnement /\\\x1b[0m\n");
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
	e->redraw = 1;
	e->window = NULL;
	e->icon = NULL;
	ft_putendl("\x1b[1;32mRT environnement initialized!\n\x1b[0m");
//	printf("t_light_ray			: %-20lu\n", sizeof(t_light_ray));
//	printf("t_cam 				: %-20lu\n", sizeof(t_cam));
//	printf("t_cone 				: %-20lu\n", sizeof(t_cone));
//	printf("t_cylinder 			: %-20lu\n", sizeof(t_cylinder));
//	printf("t_light 			: %-20lu\n", sizeof(t_light));
//	printf("t_plane 			: %-20lu\n", sizeof(t_plane));
//	printf("t_sphere 			: %-20lu\n", sizeof(t_sphere));
//	printf("t_tor 				: %-20lu\n", sizeof(t_tor)); // TOR IS NO MORE!
//	printf("t_scene 			: %-20lu\n", sizeof(t_scene));
}

void		init(GtkApplication *app, gpointer data)
{
	t_env *e;

	(void)app;
	e = data;
	if (!(e->scene = malloc(sizeof(t_scene))))
		s_error("\x1b[1;31mCan't initialize scene buffer\x1b[0m", e);
	ft_bzero(e->scene, sizeof(t_scene));
	xml_init(e);
	env_init(e);
	if (!(e->frame_pixel_data = malloc(sizeof(int) * e->win_w * e->win_h)))
		s_error("\x1b[1;31mCan't initialize pixel buffer\x1b[0m", e);
	ft_bzero(e->frame_pixel_data, sizeof(int) * e->win_w * e->win_h);
	
//	printf("test1 = %x\n", ((int*)e->frame_pixel_data)[461312]);

//	if (!(e->mlx = mlx_init()))
//		s_error("\x1b[1;31mError can't initialize minilibx\x1b[0m", e);
//	if (!(e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "RT")))
//		s_error("\x1b[1;31mError minilibx window creation failed\x1b[0m", e);
//	frame_init(e);

	load_scene(e);
	if (opencl_init(e) != 0)
	{
		e->gpu = 0;
		opencl_init(e);
	}
	init_gtk(app, e);
	gtk_window_set_title (GTK_WINDOW(e->window), "RT - Initialized!");
	
//	gtk_main_loop(e);
}
