/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:36:27 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 15:15:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xml_write_cameras(t_env *e, const int fd, t_cam *cameras)
{
	int		i;
	t_cam	current_cam;

	i = 0;
	while (i < (int)e->scene->n_cams)
	{
		current_cam = cameras[i];
		ft_putstr_fd("\t<cam\n", fd);
		xml_write_float3("\tpos", current_cam.pos, fd);
		ft_putstr_fd("\tdir", fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(ft_ftoa(current_cam.pitch), fd);
		ft_putstr_fd(", ", fd);
		ft_putstr_fd(ft_ftoa(current_cam.yaw), fd);
		ft_putstr_fd(", ", fd);
		ft_putstr_fd(ft_ftoa(current_cam.roll), fd);
		ft_putendl_fd("\"", fd);
		xml_write_int("\tfov", (int)current_cam.fov, fd);
		ft_putstr_fd("/>\n", fd);
		i++;
	}
}
