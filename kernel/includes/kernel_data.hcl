#ifndef KERNEL_DATA_HCL
# define KERNEL_DATA_HCL

t_hit			hit_init(void)
{
	t_hit		hit;

	hit.dist = 0.f;
	hit.normale = 0.f;
	hit.obj = 0;
	hit.pos = 0.f;
	return (hit);
}

int				get_max_obj(const __local t_scene *scene)
{
	unsigned int			res = scene->n_cones;

	if (scene->n_cylinders > res)
		res = scene->n_cylinders;
	if (scene->n_planes > res)
		res = scene->n_planes;
	if (scene->n_spheres > res)
		res = scene->n_spheres;
	return (res);
}

#endif
