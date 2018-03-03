/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/03 20:27:14 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	flush(t_env *e)
{
	if (e->kernel_src)
		free(e->kernel_src);
	if (XML)
		free(XML);
	if (e->frame && e->frame->ptr)
		mlx_destroy_image(e->mlx, e->frame->ptr);
	if (e->frame)
		free(e->frame);
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e)
		free(e);
}

void	s_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[2;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
	flush(e);
	exit(EXIT_FAILURE);
}

void	p_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[2;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
	perror(NULL);
	flush(e);
	exit(EXIT_FAILURE);
}

int		quit(t_env *e)
{
	flush(e);
	ft_putendl("Exiting");
	exit(EXIT_SUCCESS);
	return (0);
}
