#include "rt.h"

int		gtk_main_loop(t_env *e)
{
	char *fps;

	fps = NULL;
	if (e)
	{
		update_fps(&e->fps);
		fps = ft_itoa(e->fps.ret_fps);
		fps = ft_strjoin_frs2("RT - ", fps);
		fps = ft_strjoin_frs1(fps, " ips");
		gtk_window_set_title (GTK_WINDOW(e->window), fps);
//		mlx_keyboard_repeated(e); /// TO REPLACE
//		mlx_clear_window(e->mlx, e->win); /// TO REPLACE
		opencl_draw(e);
		e->frame_pixel_buffer = gdk_pixbuf_new_from_bytes((GBytes*)e->frame_pixel_data,
                          GDK_COLORSPACE_RGB,
                          TRUE,
                          8,
                          e->win_w,
                          e->win_h,
                          1024 * 4);
		gtk_image_set_from_pixbuf(GTK_IMAGE(e->frame_placeholder), e->frame_pixel_buffer);
		gtk_widget_show(e->frame_placeholder);
//		mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0); /// TO REPLACE
//		display_hud(e); // TO REPLACE
		free(fps);
	}
	return (0);
}
