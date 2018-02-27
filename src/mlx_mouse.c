/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:50:17 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		mlx_mouse_events(int btn, int x, int y, t_env *e)
{
	if (btn == 1)
	{
		e->run = 1;
		e->scene->mou_x = x;
		e->scene->mou_y = y;
	}
	return (0);
}
