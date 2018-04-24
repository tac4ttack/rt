/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_cut_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:21:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 19:21:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cb_obj_cut_check(GtkToggleButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_CUT)
		obj->flags ^= OBJ_FLAG_CUT;
	else
		obj->flags |= OBJ_FLAG_CUT;
}
