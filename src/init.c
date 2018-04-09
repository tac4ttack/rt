/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:46:22 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/09 23:33:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		load_scene_objects(t_env *e)
{
	t_node	*list;

	list = XML->node_lst;
	while (list != NULL)
	{
		e->current_index_objects++;
		if (list->type == OBJ_CONE)
			xml_push_cone(e, list);
		if (list->type == OBJ_CYLINDER)
			xml_push_cyl(e, list);
		if (list->type == OBJ_PLANE)
			xml_push_plane(e, list);
		if (list->type == OBJ_SPHERE)
			xml_push_sphere(e, list);
		if (list->type == OBJ_ELLIPSOID)
			xml_push_ellipsoid(e, list);
		if (list->type == OBJ_BOX)
			xml_push_box(e, list);
		if (list->type == OBJ_TORUS)
			xml_push_torus(e, list);
		list = list->next;
	}
	xml_list_clean(e, &XML->node_lst);
	ft_putendl("\x1b[1;29mSuccessfully loaded the scene!\n\x1b[0m");
}

void		load_scene(t_env *e)
{
	t_node	*list;

	ft_putendl("\n\x1b[1;32m/\\ Loading scene /\\\x1b[0m\n");
	xml_allocate_cam(e);
	list = XML->node_lst;
	while (list != NULL)
	{
		e->current_index_objects++;
		if (list->type == OBJ_CAM)
			xml_push_cam(e, list);
		if (list->type == OBJ_LIGHT)
			xml_push_light(e, list);
		list = list->next;
	}
	load_scene_objects(e);
}

void		env_init(t_env *e)
{
	ft_putendl("\n\x1b[1;32m/\\ Initializing RT environnement /\\\x1b[0m\n");
	e->scene->depth = 0;
	e->scene->over_sampling = 1;
	e->target = -1;
	if (DBUG == 1)
		e->scene->flag |= OPTION_DEBUG;
	e->gpu = IS_GPU;
	if (e->gpu == 1)
		e->scene->flag |= OPTION_GPU;
	e->ui->redraw = 1;
	ft_putendl("\x1b[1;29mRT environnement initialized!\n\x1b[0m");
}
/*
void		cl_init(t_env *e)
{
	if (!(e->cl = cl_construct("./kernel/kernel.cl", WIDTH, HEIGHT,
	(e->scene->flag & OPTION_GPU) ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU)))
		s_error("\x1b[2;31mError t_cl creation failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, WIDTH * HEIGHT * 4)))
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


	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[0].width * e->texture[0].height)))
	 	s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[1].width * e->texture[1].height)))
	 	s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[2].width * e->texture[2].height)))
	 	s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[3].width * e->texture[3].height)))
		s_error("\x1b[2;31mError creation cl_mem failed bite\x1b[0m", e);

	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[6], CL_TRUE, 0,
							sizeof(unsigned int) * e->texture[0].width * e->texture[0].height,
							e->texture[0].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text0 arguments to kernel!", e);
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[7], CL_TRUE, 0,
							sizeof(unsigned int) * e->texture[1].width * e->texture[1].height,
							e->texture[1].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text1 arguments to kernel!", e);
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[8], CL_TRUE, 0,
							sizeof(unsigned int) * e->texture[2].width * e->texture[2].height,
							e->texture[2].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text2 arguments to kernel!", e);
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[9], CL_TRUE, 0,
							sizeof(unsigned int) * e->texture[3].width * e->texture[3].height,
							e->texture[3].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text3 arguments to kernel!", e);
}*/

void		init(GtkApplication *app, gpointer data)
{
	t_env	*e;

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
	if (!(e->pixel_data = malloc(sizeof(int) * WIDTH * HEIGHT)))
		s_error("\x1b[1;31mCan't initialize pixel buffer\x1b[0m", e);
	ft_bzero(e->pixel_data, sizeof(int) * WIDTH * HEIGHT);
	load_scene(e);
	ft_putendl("\n\x1b[1;32m/\\ Loading UI... /\\\x1b[0m\n");

	init_cuda(&e->cuda, e->scene, e->gen_objects, e->gen_lights, e->texture);

	opencl_draw(e);
}
