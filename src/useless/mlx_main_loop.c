/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:44:28 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 19:36:32 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	t_p2i a;
**	a.x = WIDTH / 2;
**	a.y = HEIGHT / 2 - 15;
**	t_p2i b;
**	b.x = WIDTH / 2;
**	b.y = HEIGHT / 2 + 15;
**	mlx_img_line(e->frame, a, b, 0x00660066);
**	a.x = WIDTH / 2 - 15;
**	a.y = HEIGHT / 2;
**	b.x = WIDTH / 2 + 15;
**	b.y = HEIGHT / 2;
**	mlx_img_line(e->frame, a, b, 0x00660066);
*/

int		mlx_main_loop(t_env *e)
{
	if (e)
	{
		update_fps(&e->fps);
		mlx_keyboard_repeated(e);
		mlx_clear_window(e->mlx, e->win);
		opencl_draw(e);
		mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0);
		display_hud(e);
	}
	return (0);
}
