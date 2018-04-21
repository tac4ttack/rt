/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_update_limit_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 17:50:42 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 17:51:19 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

void	ui_obj_update_cut_check(t_env *e, t_object *obj)
{
	if (obj->flags & OBJ_FLAG_CUT)
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_cut_check), TRUE);
		if (!(obj->flags & OBJ_FLAG_CUT))
			obj->flags |= OBJ_FLAG_CUT;
	}
	else
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_cut_check), FALSE);
		if (obj->flags & OBJ_FLAG_CUT)
			obj->flags ^= OBJ_FLAG_CUT;
	}
}

void	ui_obj_update_limit_plane_check(t_env *e, t_object *obj)
{
	if (obj->flags & OBJ_FLAG_PLANE_LIMIT)
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_plane_limit_button), TRUE);
		if (!(obj->flags & OBJ_FLAG_PLANE_LIMIT))
			obj->flags |= OBJ_FLAG_PLANE_LIMIT;
	}
	else
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_plane_limit_button), FALSE);
		if (obj->flags & OBJ_FLAG_PLANE_LIMIT)
			obj->flags ^= OBJ_FLAG_PLANE_LIMIT;
	}
}

void	ui_obj_update_limit_fix_check(t_env *e, t_object *obj)
{
	if (obj->flags & OBJ_FLAG_PLANE_LIMIT_FIX)
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_plane_limit_fix_button),
			TRUE);
		if (!(obj->flags & OBJ_FLAG_PLANE_LIMIT_FIX))
			obj->flags |= OBJ_FLAG_PLANE_LIMIT_FIX;
	}
	else
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_plane_limit_fix_button),\
			FALSE);
		if (obj->flags & OBJ_FLAG_PLANE_LIMIT_FIX)
			obj->flags ^= OBJ_FLAG_PLANE_LIMIT_FIX;
	}
}
