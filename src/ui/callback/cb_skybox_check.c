/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_skybox_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:16:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 19:16:12 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cb_skybox_check(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	if (e->scene->flag & OPTION_SKYBOX)
		e->scene->flag ^= OPTION_SKYBOX;
	else
		e->scene->flag |= OPTION_SKYBOX;
}
