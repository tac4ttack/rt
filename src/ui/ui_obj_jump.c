#include "rt.h"

static	char	*obj_jump_get_label(t_env *e, t_object *obj)
{
	char		*label;
	
	label = ft_strjoin_frs1(ft_itoa(gen_get_ptr_index(e->gen_objects, \
															obj) + 1), "# ");
	if (obj->type == OBJ_CONE)
		label = ft_strjoin_frs1(label, " CONE");
	else if (obj->type == OBJ_CYLINDER)
		label = ft_strjoin_frs1(label, " CYLINDER");
	else if (obj->type == OBJ_PLANE)
		label = ft_strjoin_frs1(label, " PLANE");
	else if (obj->type == OBJ_SPHERE)
		label = ft_strjoin_frs1(label, " SPHERE");
	else if (obj->type == OBJ_ELLIPSOID)
		label = ft_strjoin_frs1(label, " ELLIPSOID");
	else if (obj->type == OBJ_TORUS)
		label = ft_strjoin_frs1(label, " TORUS");
	return (label);
}

void			ui_obj_jump_list(t_env *e)
{
	size_t		i;
	void		*obj;
	char		*label;

	i = 0;
	gtk_combo_box_text_remove_all((GtkComboBoxText *)e->ui->obj_nav_jump_combo);
	obj = e->gen_objects->mem;
	while (i < e->gen_objects->length)
	{
		label = obj_jump_get_label(e, obj);
		gtk_combo_box_text_append((GtkComboBoxText *)e->ui->obj_nav_jump_combo,\
                           			NULL, label);
		free(label);
		obj = obj + ((t_object*)(obj))->size;
		i++;
	}
}
