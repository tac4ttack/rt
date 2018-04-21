/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 20:35:40 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/21 20:35:41 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void						s_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
	if (e)
		flush(e);
	cudaDeviceReset();
	exit(EXIT_FAILURE);
}

void						p_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	perror((const char *)str);
	flush(e);
	cudaDeviceReset();
	exit(EXIT_FAILURE);
}
