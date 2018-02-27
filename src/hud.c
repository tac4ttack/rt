/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:48:13 by fmessina          #+#    #+#             */
/*   Updated: 2018/02/25 13:20:21 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		display_hud_cam(t_env *e)
{
	char		*mvt;
	char		*rot;

	mvt = ft_strjoin_frs2("CAM.X = ", ft_ftoa(ACTIVECAM.pos.x));
	mlx_string_put(e->mlx, e->win, 10, 10, 0x00ffffff, mvt);
	free(mvt);
	mvt = ft_strjoin_frs2("CAM.Y = ", ft_ftoa(ACTIVECAM.pos.y));
	mlx_string_put(e->mlx, e->win, 10, 25, 0x00ffffff, mvt);
	free(mvt);
	mvt = ft_strjoin_frs2("CAM.Z = ", ft_ftoa(ACTIVECAM.pos.z));
	mlx_string_put(e->mlx, e->win, 10, 40, 0x00ffffff, mvt);
	free(mvt);
	rot = ft_strjoin_frs2("CAM.PITCH = ", ft_ftoa(ACTIVECAM.pitch));
	mlx_string_put(e->mlx, e->win, 10, 55, 0x00ffffff, rot);
	free(rot);
	rot = ft_strjoin_frs2("CAM.YAW = ", ft_ftoa(ACTIVECAM.yaw));
	mlx_string_put(e->mlx, e->win, 10, 70, 0x00ffffff, rot);
	free(rot);
	rot = ft_strjoin_frs2("CAM.ROLL = ", ft_ftoa(ACTIVECAM.roll));
	mlx_string_put(e->mlx, e->win, 10, 85, 0x00ffffff, rot);
	free(rot);
}

static	char	*hud_get_obj_type(t_env *e)
{
	if (ACTIVEOBJ.type == 0)
		return ("CAM #");
	if (ACTIVEOBJ.type == 1)
		return ("CONE #");
	else if (ACTIVEOBJ.type == 2)
		return ("CYLINDER #");
	else if (ACTIVEOBJ.type == 3)
		return ("LIGHT #");
	else if (ACTIVEOBJ.type == 4)
		return ("PLANE #");
	else
		return ("SPHERE #");
}

static void		display_hud_obj_pos(t_env *e)
{
	cl_float3	*obj_pos;
	char		*pos;
	char		*obj;

	obj_pos = get_target_pos(e);
	if (obj_pos)
	{
		obj = ft_strjoin_frs2(hud_get_obj_type(e), ft_itoa(ACTIVEOBJ.id));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 115, 0x00ffffff, obj);
		free(obj);
		pos = ft_strjoin_frs2("POS.X = ", ft_ftoa(obj_pos->x));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 100, 0x00ffffff, pos);
		free(pos);
		pos = ft_strjoin_frs2("POS.Y = ", ft_ftoa(obj_pos->y));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 85, 0x00ffffff, pos);
		free(pos);
		pos = ft_strjoin_frs2("POS.Z = ", ft_ftoa(obj_pos->z));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 70, 0x00ffffff, pos);
		free(pos);
	}
}

static void		display_hud_obj_dir(t_env *e)
{
	cl_float3	*obj_dir;
	char		*dir;

	obj_dir = get_target_dir(e);
	if (obj_dir)
	{
		dir = ft_strjoin_frs2("DIR.X = ", ft_ftoa(obj_dir->x));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 55, 0x00ffffff, dir);
		free(dir);
		dir = ft_strjoin_frs2("DIR.Y = ", ft_ftoa(obj_dir->y));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 40, 0x00ffffff, dir);
		free(dir);
		dir = ft_strjoin_frs2("DIR.Z = ", ft_ftoa(obj_dir->z));
		mlx_string_put(e->mlx, e->win, 10, HEIGHT - 25, 0x00ffffff, dir);
		free(dir);
	}
}

void			display_hud(t_env *e)
{
	char		*refl;
	char		*fps;

	refl = ft_strjoin_frs2("depth = ", ft_itoa(e->scene->depth));
	mlx_string_put(e->mlx, e->win, 10, 115, 0x00ffffff, refl);
	free(refl);
	display_hud_cam(e);
	display_hud_obj_pos(e);
	display_hud_obj_dir(e);
	fps = ft_itoa(e->fps.ret_fps);
	mlx_string_put(e->mlx, e->win, e->win_w - 40, 10, 0x00ffffff, fps);
	free(fps);
}
