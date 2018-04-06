/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:30:36 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 22:25:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_float3(const char *name, const cl_float3 data, const int fd)
{
	ft_putstr_fd(name, fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(ft_ftoa(data.x), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_ftoa(data.y), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_ftoa(data.z), fd);
	ft_putendl_fd("\"", fd);
}

void	xml_write_float(const char *name, const float data, const int fd)
{
	ft_putstr_fd(name, fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(ft_ftoa(data), fd);
	ft_putendl_fd("\"", fd);
}

void	xml_write_int(const char *name, const float data, const int fd)
{
	ft_putstr_fd(name, fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(ft_itoa(data), fd);
	ft_putendl_fd("\"", fd);
}

void	xml_write_color(const int color, const int fd)
{
	ft_putstr_fd("\tcolor=\"", fd);
	ft_putstr_fd(ft_itoa((color & 0xFF000000) >> 24), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_itoa((color & 0x00FF0000) >> 16), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_itoa((color & 0x0000FF00) >> 8), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_itoa((color & 0x000000FF)), fd);
	ft_putendl_fd("\"", fd);
}

void	xml_write_flags(const int flags, const int fd)
{
	ft_putstr_fd("\tflags=\"", fd);
	ft_putchar_fd('0', fd);
	(flags & OBJ_FLAG_WAVES ? ft_putchar_fd('1', fd) \
							: ft_putchar_fd('0', fd));
	(flags & OBJ_FLAG_CHECKERED ? ft_putchar_fd('1', fd) \
								: ft_putchar_fd('0', fd));
	(flags & OBJ_FLAG_DIFF_MAP ? ft_putchar_fd('1', fd) \
								: ft_putchar_fd('0', fd));
	(flags & OBJ_FLAG_BUMP_MAP ? ft_putchar_fd('1', fd) \
								: ft_putchar_fd('0', fd));
	(flags & OBJ_FLAG_PLANE_LIMIT ? ft_putchar_fd('1', fd) \
								: ft_putchar_fd('0', fd));
	(flags & OBJ_FLAG_PLANE_LIMIT_FIX ? ft_putchar_fd('1', fd) \
								: ft_putchar_fd('0', fd));
	ft_putendl_fd("\"", fd);
}
