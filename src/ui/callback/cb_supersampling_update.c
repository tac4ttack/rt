/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_supersampling_update.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:49 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:19:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_supersampling_update(GtkScale *scale, gpointer data)
{
	gint	value;
	t_env	*e;

	e = data;
	value = (gint)gtk_range_get_value(GTK_RANGE(scale));
	if (value == 1)
		e->scene->over_sampling = 1;
	else if (value == 2)
		e->scene->over_sampling = 2;
	else if (value == 3)
		e->scene->over_sampling = 4;
	else if (value == 4)
		e->scene->over_sampling = 8;
	else if (value == 5)
		e->scene->over_sampling = 16;
	return (FALSE);
}
