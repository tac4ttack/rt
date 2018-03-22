/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:46:22 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/23 00:07:10 by ntoniolo         ###   ########.fr       */
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
//	printf("t_tor 				: %-20lu\n", sizeof(t_tor));
	printf("t_scene 			: %-20lu\n", sizeof(t_scene));
	printf("cl_int				: %-20lu\n", sizeof(cl_int));
	printf("cl_float			: %-20lu\n", sizeof(cl_float));
	printf("cl_float3			: %-20lu\n", sizeof(cl_float3));
}

void		load_obj(t_env *e)
{
	ft_putendl("\x1b[1;29mFetching scene objects...\x1b[0m");
	xml_allocate_cam(e);
	xml_allocate_cone(e);
	xml_allocate_cyl(e);
	xml_allocate_light(e);
	xml_allocate_plane(e);
	xml_allocate_sphere(e);
	ft_putendl("\x1b[1;29mScene objects fetched!\x1b[0m");
}

void		load_scene(t_env *e)
{
	t_node	*list;

	ft_putendl("\n\x1b[1;32m/\\ Loading scene /\\\x1b[0m\n");
	e->scene->over_sampling = 1;
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
	ft_putendl("\x1b[1;29mSuccessfully loaded the scene!\n\x1b[0m");
}

void		env_init(t_env *e)
{
	ft_putendl("\n\x1b[1;32m/\\ Initializing RT environnement /\\\x1b[0m\n");
	e->scene->depth = 0;
	e->target = -1;
	e->scene->tor_count = pow(2, e->scene->depth + 1) - 1; // USELESS?
	e->debug = DBUG;
	e->gpu = IS_GPU;
	if (e->gpu == 1)
		e->scene->flag |= OPTION_GPU;
	e->ui->redraw = 1;
	ft_putendl("\x1b[1;29mRT environnement initialized!\n\x1b[0m");
}

void		init(GtkApplication* app, gpointer data)
{
	t_env *e;

	(void)app;
	e = data;
	if (!(e->scene = ft_memalloc(sizeof(t_scene))))
		s_error("\x1b[2;31mCan't initialize scene buffer\x1b[0m", e);
	if (!(e->gen_objects = gen_construct()))
		s_error("\x1b[2;31mCan't initialize objects t_gen\x1b[0m", e);
	if (!(e->gen_lights = gen_construct()))
		s_error("\x1b[2;31mCan't initialize lights t_gen\x1b[0m", e);
	ft_bzero(e->scene, sizeof(t_scene));
	xml_init(e);
	env_init(e);
	if (!(e->pixel_data = malloc(sizeof(int) * e->scene->win_w * e->scene->win_h)))
		s_error("\x1b[1;31mCan't initialize pixel buffer\x1b[0m", e);
	ft_bzero(e->pixel_data, sizeof(int) * e->scene->win_w * e->scene->win_h);
	load_scene(e);



	if (!(e->cl = cl_construct("./kernel/kernel.cl", "ray_trace", e->scene->win_w, e->scene->win_h,
			(e->scene->flag & OPTION_GPU) ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU)))
		s_error("\x1b[2;31mError t_cl creation failed\x1b[0m", e);

	if (e->debug)
	{
		printf("%i %i %i\n", e->scene->win_w, e->scene->win_h, (e->scene->flag & OPTION_GPU));
		init_print_structure_memory_size();
	}

	if (!(e->cl->add_buffer(e->cl, e->scene->win_w * e->scene->win_h * 4)))
		s_error("\x1b[2;31mError creation FRAMEBUFFER cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, e->gen_objects->mem_size)))
		s_error("\x1b[2;31mError creation OBJECTS cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(t_scene))))
		s_error("\x1b[2;31mError creation SCENE cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(t_cam) * NCAM)))
		s_error("\x1b[2;31mError creation CAMERAS cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, e->gen_lights->mem_size)))
		s_error("\x1b[2;31mError creation LIGHTS cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(int))))
		s_error("\x1b[2;31mError creation TARGETOBJ cl_mem failed\x1b[0m", e);
	opencl_set_args(e, e->cl);
	opencl_draw(e);
}
