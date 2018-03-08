#include "rt.h"

void				mount_image(t_env *e)
{
	//GdkPixbuf		*pixbuf;

//	pixbuf = NULL;
	e->ui->pixbuf = gtk_new_image((unsigned char *)e->pixel_data, e->win_w, e->win_h);
	gtk_image_set_from_pixbuf((struct _GtkImage *)e->ui->frame_placeholder, e->ui->pixbuf);
}
/*
static gboolean		gtk_loop(void *data)
{
	t_vm	*vm;

	vm = (t_vm *)data;
	vm->gtk.time = g_get_monotonic_time();
	while (IS_UNSET(vm->flag, STOP))
	{
		if (IS_UNSET(vm->flag, END)
			&& (IS_UNSET(vm->flag, PAUSE) || IS_SET(vm->flag, STEP)))
		{
			if (gtk_cycle(vm))
				break ;
		}
		while (gtk_events_pending())
			if (gtk_main_iteration())
				return (FALSE);
	}
	vm->gtk.time = g_get_monotonic_time();
	while (g_get_monotonic_time() - vm->gtk.time < 100000)
		;
	gtk_main_quit();
	return (FALSE);
}
*/
gboolean		gtk_main_loop(void *ptr)
{
	t_env *e;
	e = (t_env *)ptr;
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
			printf("%s\n", fps);
		//	ft_putendl(fps); // Controle semble ok
			//gtk_window_set_title(GTK_WINDOW(e->ui->window), fps);

//			mlx_keyboard_repeated(e); /// TO REPLACE
//			mlx_clear_window(e->mlx, e->win); /// TO REPLACE

			opencl_draw(e);
			mount_image(e);

//			mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0); /// TO REPLACE
//			display_hud(e); // TO REPLACE
			free(fps);
			//gtk_widget_show_all((GtkWidget *)e->ui->main_window);
			/*while ((gtk_events_pending()))
			{
				if (gtk_main_iteration())
					return (FALSE);
				//printf("One\n");
			}*/
		//	gtk_main_iteration_do(FALSE);
			while (gtk_events_pending())
			{
				printf("Oui\n");
				if (gtk_main_iteration())
					return (FALSE);
			}
		}
	}
	return (0);
}
