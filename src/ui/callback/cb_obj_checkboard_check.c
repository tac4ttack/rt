/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_checkboard_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/02 18:13:58 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_checkboard_check(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	ft_putendl("prout");
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_CHECKERED)
		obj->flags ^= OBJ_FLAG_CHECKERED;
	else
	{
		if (obj->flags & OBJ_FLAG_DIFF_MAP)
			obj->flags ^= OBJ_FLAG_DIFF_MAP;
		obj->flags |= OBJ_FLAG_CHECKERED;
	}
}
