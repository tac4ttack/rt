/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:46:22 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/06 20:27:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_print_structure_memory_size()
{
	printf("t_cam 				: %-20lu\n", sizeof(t_cam));
	printf("t_cone 				: %-20lu\n", sizeof(t_cone));
	printf("t_cylinder 			: %-20lu\n", sizeof(t_cylinder));
	printf("t_light 			: %-20lu\n", sizeof(t_light));
	printf("t_plane 			: %-20lu\n", sizeof(t_plane));
	printf("t_sphere 			: %-20lu\n", sizeof(t_sphere));
	printf("t_tor 				: %-20lu\n", sizeof(t_tor));
	printf("t_scene 			: %-20lu\n", sizeof(t_scene));
	printf("cl_int				: %-20lu\n", sizeof(cl_int));
	printf("cl_float			: %-20lu\n", sizeof(cl_float));
	printf("cl_float3			: %-20lu\n", sizeof(cl_float3));
}

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
<<<<<<< HEAD
	e->gpu = 1;
=======
	//if (IS_GPU)
		e->scene->flag |= OPTION_GPU;
>>>>>>> 3afeadce2ce771bf5010a28d4f1b7eac8cf5fafe
	e->tree = tor_create(e);
}

void		init(t_env *e, int ac, char *av)
{
	ft_bzero(e, sizeof(t_env));
	if (!(e->scene = ft_memalloc(sizeof(t_scene))))
		s_error("\x1b[2;31mCan't initialize scene buffer\x1b[0m", e);
	if (!(e->gen_objects = construct_gen()))
		s_error("\x1b[2;31mCan't initialize t_gen\x1b[0m", e);
	if (!(e->gen_lights = construct_gen()))
		s_error("\x1b[2;31mCan't initialize t_gen\x1b[0m", e);
	ft_bzero(e->scene, sizeof(t_scene));
	xml_init(e, ac, av);
	env_init(e);
	if (!(e->mlx = mlx_init()))
		s_error("\x1b[2;31mError can't initialize minilibx\x1b[0m", e);
	if (!(e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "RT")))
		s_error("\x1b[2;31mError minilibx window creation failed\x1b[0m", e);
	frame_init(e);
	printf("%i %i %i\n", e->scene->win_w, e->scene->win_h, (e->scene->flag & OPTION_GPU));
	if (!(e->cl = construct_cl("./kernel/kernel.cl", "ray_trace", e->scene->win_w, e->scene->win_h,
			(e->scene->flag & OPTION_GPU) ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU)))
		s_error("\x1b[2;31mError t_cl creation failed\x1b[0m", e);
	//if (e->debug)
		init_print_structure_memory_size();
	if (!(e->cl->add_buffer(e->cl, e->scene->win_w * e->scene->win_h * 4)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, e->gen_objects->mem_size)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(t_scene))))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(t_cam) * NCAM)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, e->gen_lights->mem_size)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(int))))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
}
