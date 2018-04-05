/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_postproc_radio.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/02 19:20:02 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_postproc_none(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	e->scene->flag ^= OPTION_BW;
	e->scene->flag ^= OPTION_SEPIA;
	e->scene->flag ^= OPTION_CARTOON_TWO;
	e->scene->flag ^= OPTION_CARTOON_FOUR;
}

void		cb_postproc_sepia(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	e->scene->flag ^= OPTION_BW;
	e->scene->flag |= OPTION_SEPIA;
}

void		cb_postproc_bw(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	e->scene->flag |= OPTION_BW;
	e->scene->flag ^= OPTION_SEPIA;
}

void		cb_postproc_invert(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	if (e->scene->flag & OPTION_INVERT)
		e->scene->flag ^= OPTION_INVERT;
	else
		e->scene->flag |= OPTION_INVERT;
}
