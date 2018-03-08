#include "rt.h"

void				mount_image(t_env *e)
{
	GdkPixbuf		*pixbuf;

	pixbuf = NULL;
	pixbuf = gtk_new_image((unsigned char *)e->pixel_data, e->win_w, e->win_h);
	gtk_image_set_from_pixbuf(GTK_IMAGE(e->ui->frame_placeholder), pixbuf);
}

int		gtk_main_loop(t_env *e)
{
	char *fps;

	fps = NULL;
	if (e)
	{
		while (e->ui->redraw > 0)
		{
			ft_putendl("im in gtk main loop");

			update_fps(&e->fps);
			fps = ft_itoa(e->fps.ret_fps);
			fps = ft_strjoin_frs2("RT - ", fps);
			fps = ft_strjoin_frs1(fps, " ips");
		//	ft_putendl(fps); // Controle semble ok
			//gtk_window_set_title(GTK_WINDOW(e->ui->window), fps);

//			mlx_keyboard_repeated(e); /// TO REPLACE
//			mlx_clear_window(e->mlx, e->win); /// TO REPLACE

			opencl_draw(e);
			mount_image(e);

//			mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0); /// TO REPLACE
//			display_hud(e); // TO REPLACE
			free(fps);
		}
	}
	return (0);
}
