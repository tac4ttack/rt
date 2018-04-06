/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:36:27 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 20:37:14 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_write_cameras(t_env *e, const int fd, t_cam *cameras)
{
	int		i;
	t_cam	*current_cam;

	i = 0;
	while (i < (int)e->scene->n_cams)
	{
		current_cam = &cameras[i];
		ft_putstr_fd("\t<cam\n", fd);
		xml_write_float3("\tpos", current_cam->pos, fd);
		xml_write_float3("\tdir", current_cam->dir, fd);
		xml_write_int("\tfov", (int)current_cam->fov, fd);
		ft_putstr_fd("/>\n", fd);
		i++;
	}
}
