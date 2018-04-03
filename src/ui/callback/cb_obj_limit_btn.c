/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 15:56:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_limit_btn(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_PLANELIMIT)
		obj->flags ^= OBJ_FLAG_PLANELIMIT;
	else
		obj->flags |= OBJ_FLAG_PLANELIMIT;
}
