/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_plane_limit_btn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/10 19:34:29 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_plane_limit_btn(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_PLANE_LIMIT)
		obj->flags ^= OBJ_FLAG_PLANE_LIMIT;
	else
		obj->flags |= OBJ_FLAG_PLANE_LIMIT;	
}

void			cb_obj_plane_limit_fix_btn(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_PLANE_LIMIT_FIX)
		obj->flags ^= OBJ_FLAG_PLANE_LIMIT_FIX;
	else
		obj->flags |= OBJ_FLAG_PLANE_LIMIT_FIX;
}
