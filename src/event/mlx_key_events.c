/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:47:00 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/03 13:25:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			mlx_keyboard_repeated(t_env *e)
{
	if (!e)
		exit(EXIT_FAILURE);
	(KP_ESC ? quit(e) : 0);
	if (KP_W || KP_S || KP_A || KP_D || KP_C || KP_SPC || \
		KP_DA || KP_UA || KP_LA || KP_RA || KP_Z)
		ui_cam(e);
	if (KP_I || KP_J || KP_K || KP_L || KP_U || KP_O || \
		KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9)
		ui_obj(e);
	if (KP_NMIN || KP_NPLU)
	{
		if (KP_NPLU)
			e->scene->depth++;
		if (KP_NMIN)
			(e->scene->depth > 0 ? e->scene->depth-- : 0);
		e->scene->tor_count = pow(2, e->scene->depth + 1) - 1;
	}
/*	if (KP_1)
	{
		if (e->scene->flag & OPTION_WAVE)
			e->scene->flag ^= OPTION_WAVE;
		else
			e->scene->flag |= OPTION_WAVE;
	}
	if (KP_2)
	{
		if (e->scene->flag & OPTION_BW)
			e->scene->flag ^= OPTION_BW;
		if (e->scene->flag & OPTION_SEPIA)
			e->scene->flag ^= OPTION_SEPIA;
		else
			e->scene->flag |= OPTION_SEPIA;
	}
	if (KP_3)
	{
		if (e->scene->flag & OPTION_SEPIA)
			e->scene->flag ^= OPTION_SEPIA;
		if (e->scene->flag & OPTION_BW)
			e->scene->flag ^= OPTION_BW;
		else
			e->scene->flag |= OPTION_BW;
	}*/
	//opencl_allocate_scene_memory(e);
}
