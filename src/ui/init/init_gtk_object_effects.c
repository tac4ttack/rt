/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_object_effects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:25:27 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 16:20:52 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_object_effects(t_env *e)
{
	init_gtk_object_limit(e);
	init_gtk_object_sinwave(e);
	init_gtk_object_diffmap(e);
	init_gtk_object_checkboard(e);
	init_cb_object_limit(e);
	init_cb_object_sinwave(e);
	init_cb_object_diffmap(e);
	init_cb_object_checkboard(e);
}
