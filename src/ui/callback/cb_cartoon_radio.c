/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cartoon_radio.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:27:25 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_cartoon_four(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	e->scene->flag |= OPTION_CARTOON_FOUR;
	e->scene->flag ^= OPTION_CARTOON_TWO;
	e->scene->flag ^= OPTION_BW;
	e->scene->flag ^= OPTION_SEPIA;
}

void		cb_cartoon_two(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	e->scene->flag |= OPTION_CARTOON_TWO;
	e->scene->flag ^= OPTION_CARTOON_FOUR;
	e->scene->flag ^= OPTION_BW;
	e->scene->flag ^= OPTION_SEPIA;
}
