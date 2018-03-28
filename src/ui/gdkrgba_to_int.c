#include "rt.h"

GdkRGBA		int_to_gdkrbga(int color)
{
	GdkRGBA res;

	res.alpha = 1;
	res.red = (gdouble)((color & 0x00FF0000) >> 16) / 255;
	res.green = (gdouble)((color & 0x0000FF00) >> 8) / 255;
	res.blue = (gdouble)((color & 0x000000FF)) / 255;
	return (res);
}

int			gdkrgba_to_int(GdkRGBA color)
{
	cl_int4		swap;

	swap.w = 255;
	swap.x = color.red * 255;
	swap.y = color.green * 255;
	swap.z = color.blue * 255;
	return (((swap.x << 16) + (swap.y << 8) + (swap.z)));
}
