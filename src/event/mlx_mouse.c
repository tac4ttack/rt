/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:50:17 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/04 23:20:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		mlx_mouse_events(int btn, int x, int y, t_env *e)
{
	if (btn == 1)
	{
		e->scene->flag |= OPTION_RUN;
		e->scene->mou_x = x;
		e->scene->mou_y = y;
	}
	return (0);
}
