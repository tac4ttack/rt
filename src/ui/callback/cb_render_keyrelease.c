/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_render_keyrelease.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:40 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:25:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cb_render_keyrelease_adds(t_env *e, guint key)
{
	(key == KEY_W ? KEY_STATE_W = 0 : 0);
	(key == KEY_A ? KEY_STATE_A = 0 : 0);
	(key == KEY_S ? KEY_STATE_S = 0 : 0);
	(key == KEY_D ? KEY_STATE_D = 0 : 0);
	(key == KEY_C ? KEY_STATE_C = 0 : 0);
	(key == KEY_I ? KEY_STATE_I = 0 : 0);
	(key == KEY_J ? KEY_STATE_J = 0 : 0);
	(key == KEY_K ? KEY_STATE_K = 0 : 0);
	(key == KEY_L ? KEY_STATE_L = 0 : 0);
	(key == KEY_U ? KEY_STATE_U = 0 : 0);
	(key == KEY_O ? KEY_STATE_O = 0 : 0);
	(key == KEY_Z ? KEY_STATE_Z = 0 : 0);
	(key == KEY_1 ? KEY_STATE_1 = 0 : 0);
}

gboolean	cb_render_keyrelease(GtkWidget *widget, GdkEvent *ev, gpointer data)
{
	t_env	*e;
	guint	key;

	(void)widget;
	e = data;
	if (!e)
		exit(EXIT_FAILURE);
	key = ev->key.keyval;
	(key == KEY_UA ? KEY_STATE_UA = 0 : 0);
	(key == KEY_DA ? KEY_STATE_DA = 0 : 0);
	(key == KEY_LA ? KEY_STATE_LA = 0 : 0);
	(key == KEY_RA ? KEY_STATE_RA = 0 : 0);
	(key == KEY_ESC ? KEY_STATE_ESC = 0 : 0);
	(key == KEY_SPC ? KEY_STATE_SPC = 0 : 0);
	(key == KEY_NPLU ? KEY_STATE_NPLU = 0 : 0);
	(key == KEY_NMIN ? KEY_STATE_NMIN = 0 : 0);
	(key == KEY_N4 ? KEY_STATE_N4 = 0 : 0);
	(key == KEY_N5 ? KEY_STATE_N5 = 0 : 0);
	(key == KEY_N6 ? KEY_STATE_N6 = 0 : 0);
	(key == KEY_N7 ? KEY_STATE_N7 = 0 : 0);
	(key == KEY_N8 ? KEY_STATE_N8 = 0 : 0);
	(key == KEY_N9 ? KEY_STATE_N9 = 0 : 0);
	cb_render_keyrelease_adds(e, key);
	return (TRUE);
}
