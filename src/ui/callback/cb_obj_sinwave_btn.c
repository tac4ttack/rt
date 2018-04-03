/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_sinwave.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 15:50:52 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_sinwave_btn(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_WAVES)
		obj->flags ^= OBJ_FLAG_WAVES;
	else
		obj->flags |= OBJ_FLAG_WAVES;
}
