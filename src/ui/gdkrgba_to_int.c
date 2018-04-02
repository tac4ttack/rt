/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdkrgba_to_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:50 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GdkRGBA		int_to_gdkrbga(int color)
{
	GdkRGBA res;

	res.alpha = 1;
	res.red = (gdouble)((color & 0x00FF0000) >> 16) / 255;
	res.green = (gdouble)((color & 0x0000FF00) >> 8) / 255;
	res.blue = (gdouble)((color & 0x000000FF)) / 255;
	return (res);
}

int			gdkrgba_to_int(GdkRGBA color)
{
	cl_int4		swap;

	swap.w = 255;
	swap.x = color.red * 255;
	swap.y = color.green * 255;
	swap.z = color.blue * 255;
	return (((swap.x << 16) + (swap.y << 8) + (swap.z)));
}
