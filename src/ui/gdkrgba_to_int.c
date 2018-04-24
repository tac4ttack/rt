/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdkrgba_to_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:50 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/20 16:31:00 by fmessina         ###   ########.fr       */
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
	int		swap[3];

	swap[0] = color.red * 255;
	swap[1] = color.green * 255;
	swap[2] = color.blue * 255;
	return (((swap[0] << 16) + (swap[1] << 8) + (swap[2])));
}
