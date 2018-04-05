/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_about_dialog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:29 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 01:02:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	dprintf(fd, "reflex=\"%.2f\"\n", obj->refract);
	dprintf(fd, "reflex=\"%.2f\"\n", obj->opacity);
	dprintf(fd, "p_limit_pos=\"%.2f, %.2f, %.2f\"\n", obj->limit_pos.x, obj->limit_pos.y, obj->limit_pos.z);
	dprintf(fd, "p_limit_dir=\"%.2f, %.2f, %.2f\"\n", obj->limit_dir.x, obj->limit_dir.y, obj->limit_dir.z);
	dprintf(fd, "flags=");
	for (int i = 0; i < 16; i++)
		dprintf(fd, "%i", (obj->flags & (1 << i)) == 1);
	dprintf(fd, "\n/>\n");
}

static void save(t_env *e)
{
	int 			fd;
	size_t			mem_index;
	size_t			unit_index;
	t_gen			*gen;
	t_object		*obj;

	fd = open("./save.xml", O_RDWR | O_TRUNC);
	mem_index = 0;
	unit_index = 0;
	gen = e->gen_objects;
	while (mem_index < gen->mem_size)
	{
		obj = gen->mem + mem_index;
		if (obj->type == OBJ_SPHERE)
		{
			printf("oui\n");
			write_sphere(fd, obj);
		}
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
