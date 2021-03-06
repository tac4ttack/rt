/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:46:22 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/21 21:17:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	load_scene_objects(t_env *e)
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
		if (list->type == OBJ_TORUS)
			xml_push_torus(e, list);
		if (list->type == OBJ_KUBE)
			xml_push_kube(e, list);
		list = list->next;
	}
	xml_list_clean(e, &XML->node_lst);
	ft_putendl("\x1b[1;29mSuccessfully loaded the scene!\n\x1b[0m");
}

static void	load_scene(t_env *e)
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

static void	env_init(t_env *e)
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

static bool	scene_requirements(t_env *e, t_scene *scene)
{
	if (!scene->n_cams || !e->gen_lights->length || !e->gen_objects->length)
		return (false);
	if (scene->win_w > 2000 || scene->win_h > 2000)
		return (false);
	return (true);
}

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
	xml_init(e);
	env_init(e);
	load_scene(e);
	if (!scene_requirements(e, e->scene))
		s_error("\x1b[2;31mScene requirements\x1b[0m", e);
	if (!(e->pixel_data = ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		s_error("\x1b[1;31mCan't initialize pixel buffer\x1b[0m", e);
	ft_putendl("\n\x1b[1;32m/\\ Loading UI... /\\\x1b[0m\n");
	init_kernel(e);
	draw(e);
}
