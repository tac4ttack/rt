/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_css.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:32 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:33 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_css(t_env *e)
{
	e->ui->css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(e->ui->css_provider, \
									"theme/bidou/gtk.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), \
	GTK_STYLE_PROVIDER(e->ui->css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
