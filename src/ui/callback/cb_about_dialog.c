/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_about_dialog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:29 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 01:38:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void 		write_cam(t_env *e, const int fd, t_cam *tcam)
{
	int i = 0;
	t_cam *cam;

	while (i < (int)e->scene->n_cams)
	{
		cam = &tcam[i];
		dprintf(fd, "<cam		pos=\"%.2f, %.2f, %.2f\"\n",
						cam->pos.x, cam->pos.y, cam->pos.z);
		dprintf(fd, "dir=\"%.2f, %.2f, %.2f\"\n",
						cam->dir.x, cam->dir.y, cam->dir.z);
		dprintf(fd, "fov=\"%.2f\"\n/>", cam->fov);
		i++;
	}
}

void		write_sphere(const int fd, const t_object *ptr)
{
	t_sphere	*obj = (t_sphere *)ptr;
	dprintf(fd, "<sphere	");
	dprintf(fd, "pos=\"%.2f, %.2f, %.2f\"\n",
							obj->pos.x, obj->pos.y, obj->pos.z);
	dprintf(fd, "dir=\"%.2f, %.2f, %.2f\"\n",
							obj->dir.x, obj->dir.y, obj->dir.z);
	dprintf(fd, "radius=\"%.2f\"\n",
							obj->radius);
	dprintf(fd, "color=\"%i, %i, %i, %i\"\n",
							(obj->color & 0xFF000000) >> 24,
							(obj->color & 0x00FF0000) >> 16,
							(obj->color & 0x0000FF00) >> 8,
							(obj->color & 0x000000FF));
	dprintf(fd, "diff=\"%.2f, %.2f, %.2f\"\n",
							obj->diff.x, obj->diff.y, obj->diff.z);
	dprintf(fd, "spec=\"%.2f, %.2f, %.2f\"\n",
							obj->spec.x, obj->spec.y, obj->spec.z);
	dprintf(fd, "reflex=\"%.2f\"\n", obj->reflex);
	dprintf(fd, "refract=\"%.2f\"\n", obj->refract);
	dprintf(fd, "opacity=\"%.2f\"\n", obj->opacity);
	dprintf(fd, "p_limit_pos=\"%.2f, %.2f, %.2f\"\n", obj->limit_pos.x, obj->limit_pos.y, obj->limit_pos.z);
	dprintf(fd, "p_limit_dir=\"%.2f, %.2f, %.2f\"\n", obj->limit_dir.x, obj->limit_dir.y, obj->limit_dir.z);
	dprintf(fd, "flags=\"");
	for (int i = 0; i < 16; i++)
		dprintf(fd, "%i", (obj->flags & (1 << i)) == 1);
	dprintf(fd, "\"\n/>\n");
}
void		write_cone(const int fd, const t_object *ptr)
{
	t_cone	*obj = (t_cone *)ptr;
	dprintf(fd, "<cone	");
	dprintf(fd, "pos=\"%.2f, %.2f, %.2f\"\n",
							obj->pos.x, obj->pos.y, obj->pos.z);
	dprintf(fd, "dir=\"%.2f, %.2f, %.2f\"\n",
							obj->dir.x, obj->dir.y, obj->dir.z);
	dprintf(fd, "angle=\"%.2f\"\n",
							obj->angle);
	dprintf(fd, "color=\"%i, %i, %i, %i\"\n",
							(obj->color & 0xFF000000) >> 24,
							(obj->color & 0x00FF0000) >> 16,
							(obj->color & 0x0000FF00) >> 8,
							(obj->color & 0x000000FF));
	dprintf(fd, "diff=\"%.2f, %.2f, %.2f\"\n",
							obj->diff.x, obj->diff.y, obj->diff.z);
	dprintf(fd, "spec=\"%.2f, %.2f, %.2f\"\n",
							obj->spec.x, obj->spec.y, obj->spec.z);
	dprintf(fd, "reflex=\"%.2f\"\n", obj->reflex);
	dprintf(fd, "refract=\"%.2f\"\n", obj->refract);
	dprintf(fd, "opacity=\"%.2f\"\n", obj->opacity);
	dprintf(fd, "p_limit_pos=\"%.2f, %.2f, %.2f\"\n", obj->limit_pos.x, obj->limit_pos.y, obj->limit_pos.z);
	dprintf(fd, "p_limit_dir=\"%.2f, %.2f, %.2f\"\n", obj->limit_dir.x, obj->limit_dir.y, obj->limit_dir.z);
	dprintf(fd, "flags=\"");
	for (int i = 0; i < 16; i++)
		dprintf(fd, "%i", (obj->flags & (1 << i)) == 1);
	dprintf(fd, "\"\n/>\n");
}
void		write_cylinder(const int fd, const t_object *ptr)
{
	t_cylinder	*obj = (t_cylinder *)ptr;
	dprintf(fd, "<cylinder	");
	dprintf(fd, "pos=\"%.2f, %.2f, %.2f\"\n",
							obj->pos.x, obj->pos.y, obj->pos.z);
	dprintf(fd, "dir=\"%.2f, %.2f, %.2f\"\n",
							obj->dir.x, obj->dir.y, obj->dir.z);
	dprintf(fd, "radius=\"%.2f\"\n",
							obj->radius);
	dprintf(fd, "color=\"%i, %i, %i, %i\"\n",
							(obj->color & 0xFF000000) >> 24,
							(obj->color & 0x00FF0000) >> 16,
							(obj->color & 0x0000FF00) >> 8,
							(obj->color & 0x000000FF));
	dprintf(fd, "height=\"%.2f\"\n",
							obj->height);
	dprintf(fd, "diff=\"%.2f, %.2f, %.2f\"\n",
							obj->diff.x, obj->diff.y, obj->diff.z);
	dprintf(fd, "spec=\"%.2f, %.2f, %.2f\"\n",
							obj->spec.x, obj->spec.y, obj->spec.z);
	dprintf(fd, "reflex=\"%.2f\"\n", obj->reflex);
	dprintf(fd, "refract=\"%.2f\"\n", obj->refract);
	dprintf(fd, "opacity=\"%.2f\"\n", obj->opacity);
	dprintf(fd, "p_limit_pos=\"%.2f, %.2f, %.2f\"\n", obj->limit_pos.x, obj->limit_pos.y, obj->limit_pos.z);
	dprintf(fd, "p_limit_dir=\"%.2f, %.2f, %.2f\"\n", obj->limit_dir.x, obj->limit_dir.y, obj->limit_dir.z);
	dprintf(fd, "flags=\"");
	for (int i = 0; i < 16; i++)
		dprintf(fd, "%i", (obj->flags & (1 << i)) == 1);
	dprintf(fd, "\"\n/>\n");
}
void		write_ellipsoid(const int fd, const t_object *ptr)
{
	t_ellipsoid	*obj = (t_ellipsoid *)ptr;
	dprintf(fd, "<ellipsoid	");
	dprintf(fd, "pos=\"%.2f, %.2f, %.2f\"\n",
							obj->pos.x, obj->pos.y, obj->pos.z);
	dprintf(fd, "dir=\"%.2f, %.2f, %.2f\"\n",
							obj->dir.x, obj->dir.y, obj->dir.z);
	dprintf(fd, "radius=\"%.2f\"\n",
							obj->radius);
	dprintf(fd, "axis_size=\"%.2f, %.2f, %.2f\"\n", obj->axis_size.x, obj->axis_size.y, obj->axis_size.z);
	dprintf(fd, "color=\"%i, %i, %i, %i\"\n",
							(obj->color & 0xFF000000) >> 24,
							(obj->color & 0x00FF0000) >> 16,
							(obj->color & 0x0000FF00) >> 8,
							(obj->color & 0x000000FF));
	dprintf(fd, "diff=\"%.2f, %.2f, %.2f\"\n",
							obj->diff.x, obj->diff.y, obj->diff.z);
	dprintf(fd, "spec=\"%.2f, %.2f, %.2f\"\n",
							obj->spec.x, obj->spec.y, obj->spec.z);
	dprintf(fd, "reflex=\"%.2f\"\n", obj->reflex);
	dprintf(fd, "refract=\"%.2f\"\n", obj->refract);
	dprintf(fd, "opacity=\"%.2f\"\n", obj->opacity);
	dprintf(fd, "p_limit_pos=\"%.2f, %.2f, %.2f\"\n", obj->limit_pos.x, obj->limit_pos.y, obj->limit_pos.z);
	dprintf(fd, "p_limit_dir=\"%.2f, %.2f, %.2f\"\n", obj->limit_dir.x, obj->limit_dir.y, obj->limit_dir.z);
	dprintf(fd, "flags=\"");
	for (int i = 0; i < 16; i++)
		dprintf(fd, "%i", (obj->flags & (1 << i)) == 1);
	dprintf(fd, "\"\n/>\n");
}
void		write_plane(const int fd, const t_object *ptr)
{
	t_plane	*obj = (t_plane *)ptr;
	dprintf(fd, "<plane	");
	dprintf(fd, "pos=\"%.2f, %.2f, %.2f\"\n",
							obj->pos.x, obj->pos.y, obj->pos.z);
	dprintf(fd, "normale=\"%.2f, %.2f, %.2f\"\n",
							obj->normal.x, obj->normal.y, obj->normal.z);
	dprintf(fd, "color=\"%i, %i, %i, %i\"\n",
							(obj->color & 0xFF000000) >> 24,
							(obj->color & 0x00FF0000) >> 16,
							(obj->color & 0x0000FF00) >> 8,
							(obj->color & 0x000000FF));
	dprintf(fd, "diff=\"%.2f, %.2f, %.2f\"\n",
							obj->diff.x, obj->diff.y, obj->diff.z);
	dprintf(fd, "spec=\"%.2f, %.2f, %.2f\"\n",
							obj->spec.x, obj->spec.y, obj->spec.z);
	dprintf(fd, "reflex=\"%.2f\"\n", obj->reflex);
	dprintf(fd, "refract=\"%.2f\"\n", obj->refract);
	dprintf(fd, "opacity=\"%.2f\"\n", obj->opacity);
	dprintf(fd, "radius=\"%.2f\"\n", obj->radius);
	dprintf(fd, "p_limit_pos=\"%.2f, %.2f, %.2f\"\n", obj->limit_pos.x, obj->limit_pos.y, obj->limit_pos.z);
	dprintf(fd, "p_limit_dir=\"%.2f, %.2f, %.2f\"\n", obj->limit_dir.x, obj->limit_dir.y, obj->limit_dir.z);
	dprintf(fd, "flags=\"");
	for (int i = 0; i < 16; i++)
		dprintf(fd, "%i", (obj->flags & (1 << i)) == 1);
	dprintf(fd, "\"\n/>\n");
}
void		write_lights(const int fd, const t_light *light)
{
	dprintf(fd, "<light		type=\"%i\"\n", light->type);
	dprintf(fd, "pos=\"%.2f, %.2f, %.2f\"\n", light->pos.x, light->pos.y, light->pos.z);
	dprintf(fd, "dir=\"%.2f, %.2f, %.2f\"\n", light->dir.x, light->dir.y, light->dir.z);
	dprintf(fd, "brightness=\"%.2f\"\n", light->brightness);
	dprintf(fd, "shrink=\"%i\"\n", light->shrink);
	dprintf(fd, "color=\"%i, %i, %i, %i\"\n",
							(light->color & 0xFF000000) >> 24,
							(light->color & 0x00FF0000) >> 16,
							(light->color & 0x0000FF00) >> 8,
							(light->color & 0x000000FF));
	dprintf(fd, "/>\n");
}

static void save(t_env *e)
{
	int 			fd;
	size_t			mem_index;
	size_t			unit_index;
	t_gen			*gen;
	t_object		*obj;

	fd = open("./save.xml", O_RDWR | O_TRUNC);
	dprintf(fd, "<?xml version=\"1.0\"?>");
	dprintf(fd, "<scene			res=\"%i, %i\" ambient=\"%.2f, %.2f, %.2f\">",
				e->scene->win_w, e->scene->win_h,
				e->scene->ambient.x,
				e->scene->ambient.y,
				e->scene->ambient.z);
	write_cam(e, fd, e->cameras);
	mem_index = 0;
	unit_index = 0;
	gen = e->gen_objects;
	while (mem_index < gen->mem_size)
	{
		obj = gen->mem + mem_index;
		if (obj->type == OBJ_SPHERE)
			write_sphere(fd, obj);
		else if (obj->type == OBJ_CYLINDER)
			write_cylinder(fd, obj);
		else if (obj->type == OBJ_CONE)
			write_cone(fd, obj);
		else if (obj->type == OBJ_PLANE)
			write_plane(fd, obj);
		else if (obj->type == OBJ_ELLIPSOID)
			write_ellipsoid(fd, obj);
		mem_index += *((int *)(gen->mem + mem_index));
		unit_index++;
	}
	mem_index = 0;
	unit_index = 0;
	gen = e->gen_lights;
	t_light *l;
	while (mem_index < gen->mem_size)
	{
		l = gen->mem + mem_index;
		write_lights(fd, l);
		mem_index += *((int *)(gen->mem + mem_index));
		unit_index++;
	}
	close(fd);
}

void		cb_about_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	gtk_dialog_run(GTK_DIALOG(e->ui->about_window));
	gtk_widget_destroy(e->ui->about_window);
	printf("PRRRIINNT\n");
	save(e);
}
