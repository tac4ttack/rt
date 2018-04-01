/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_diff_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 19:48:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_obj_diff_check(GtkButton *btn, gpointer data)
{
	t_env 		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_DIFF_MAP)
		obj->flags ^= OBJ_FLAG_DIFF_MAP;
	else
		obj->flags |= OBJ_FLAG_DIFF_MAP;
}

