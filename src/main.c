/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:09:13 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/17 11:22:52 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	charge_texture(t_env *e, const char *name, const int index)
{
	int		i = 0;
	int		j = 0;
	guchar	*picsou;

	e->raw_texture.pixbuf = gdk_pixbuf_new_from_file(name, NULL);
	e->raw_texture.pixels = gdk_pixbuf_get_pixels(e->raw_texture.pixbuf);
	e->raw_texture.n_channels = gdk_pixbuf_get_n_channels(e->raw_texture.pixbuf);
	e->raw_texture.rowstride = gdk_pixbuf_get_rowstride(e->raw_texture.pixbuf);
	e->raw_texture.width = gdk_pixbuf_get_width(e->raw_texture.pixbuf);
	e->raw_texture.height = gdk_pixbuf_get_height(e->raw_texture.pixbuf);
	if (!(e->texture[index].pixel_array = (unsigned int *)malloc((sizeof(unsigned int) * (e->raw_texture.width * e->raw_texture.height)))))
		s_error("Error: Failed to charge RAM Texture", e);
	e->texture[index].width = e->raw_texture.width;
	e->texture[index].height = e->raw_texture.height;
	while (j < e->texture[index].height)
	{
		i = 0;
		while (i < e->texture[index].width)
		{
			picsou = e->raw_texture.pixels + j * e->raw_texture.rowstride + i * e->raw_texture.n_channels;
			e->texture[index].pixel_array[i + (j * e->texture[index].width)] = (picsou[0] << 16) + (picsou[1] << 8) + picsou[2];
			i++;
		}
		j++;
	}
	g_object_unref(e->raw_texture.pixbuf);
}

void		load_texture(t_env *e)
{
	int i;


	if (!(e->texture = (t_tex *)malloc(sizeof(t_tex) * NB_TEXTURE)))
		s_error("Error: Failed to charge RAM Texture", e);
	i = 0;
	charge_texture(e, "./textures/medium_ntoniolo.jpg", 0);
	//charge_texture(e, "./textures/earthhd.jpg", 0);
	charge_texture(e, "./textures/Moonhd.jpg", 1);
	charge_texture(e, "./textures/starmap_g4k.jpg", 2);
	charge_texture(e, "./textures/pierres_jaune.png", 3);
}


void			print_usage(void)
{
	ft_putendl("\n\x1b[1;31musage: rt <scene.xml>\x1b[0m");
	exit(EXIT_FAILURE);
}

int				main(int ac, char **av)
{
	t_env		*e;

	if (ac != 2)
		print_usage();
	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[1;31mCan't initialize RT\x1b[0m", NULL);
	ft_bzero(e, sizeof(t_env));
	if (!(e->ui = malloc(sizeof(t_ui))))
		s_error("\x1b[1;31mCan't initialize UI data structure\x1b[0m", e);
	ft_bzero(e->ui, sizeof(t_ui));
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	e->scene_file = ft_strdup(av[1]);
	load_texture(e);
	e->ui->app = gtk_application_new("ray.tracer", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(e->ui->app, "startup", G_CALLBACK(init), (gpointer)e);
	g_signal_connect(e->ui->app, "activate", G_CALLBACK(init_gtk), (gpointer)e);
	e->ui->gtkstatus = g_application_run(G_APPLICATION(e->ui->app), --ac, ++av);
	return (0);
}
