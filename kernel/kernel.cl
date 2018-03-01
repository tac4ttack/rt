#include "kernel_header.hcl"
#include "kernel_matrix.hcl"
#include "kernel_cam.hcl"
//#include "kernel_color.hcl"
//#include "kernel_cone.hcl"
//#include "kernel_cylinder.hcl"
#include "kernel_data.hcl"
#include "kernel_debug.hcl"
//#include "kernel_plane.hcl"
#include "kernel_sphere.hcl"

float					ft_dot(float3 a, float3 b)
{
	return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}
float					ft_dot_local(float3 a, const __local float3 *b)
{
	return ((a.x*b->x) + (a.y*b->y) + (a.z*b->z));
}

float3	get_cylinder_abc(const __private float3 dir, const __private float3 ray, const __private  float3 origin)
{
	float3		abc;

	// SEMBLE OK
	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir));
	return (abc);
}

float					inter_cylinder(const t_cylinder __local *cylinder, const float3 ray, const float3 origin)
{
	float3				abc;
	float3				pos;
	float				d;
	float				res1 = 0;
	float				res2 = 0;
	float				m;

	pos = origin - cylinder->pos;
//	__private float3 dir = cylinder->dir;
	//abc.x = ft_dot(ray, ray) - (ft_dot_local(ray, &cylinder->dir) * ft_dot_local(ray, &cylinder->dir));
	//abc.y = 2 * (dot(ray, origin) - (ft_dot_local(ray, &cylinder->dir) * ft_dot_local(origin, &cylinder->dir)));
	//abc.z = dot(origin, origin) - (dot(origin, &cylinder->dir) * ft_dot_local(origin, &cylinder->dir)) - (cylinder->radius * cylinder->radius);
	//float3 lul = fast_normalize((*cylinder).dir);
	abc = get_cylinder_abc(cylinder->dir, ray, pos);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		res1 = (-abc[1]) / (2 * abc[0]);
	else
	{
		res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
		res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	}
	if (res1 < 0 && res2 < 0)
		return (0);
	/*if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
	{
		if (cylinder->height == 0 || (dot(ray, fast_normalize(lul) * res1 +
			dot(origin, fast_normalize(lul))) < cylinder->height && dot(ray, fast_normalize(lul) * res1 +
			dot(origin, fast_normalize(lul))) > 0))
			return (res1);
	}*/
	if (1)
		;
	//if (1)//cylinder->height == 0)
		return (res2);
	//else
		return (0);
}

t_hit			ray_hit(const __local t_scene *scene, const float3 origin, const float3 ray)
{
	unsigned int				i;
	int							max;
	t_hit						hit;
	float						dist;
	t_object 		__local		*obj;
	size_t						mem_index_obj;

	//max = get_max_obj(scene);
	dist = 0;
	i = 0;
	hit = hit_init();
	mem_index_obj = 0;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = scene->mem_obj + mem_index_obj;
		/*if (obj->id == OBJ_CONE)
		{
			//printf("%.2f %.2f %.2f\n", obj->dir.x,obj->dir.y, obj->dir.z);
			//printf("%.2f\n", ((const __local t_cone *)obj)->angle);
			if (((dist = inter_cone((const __local t_cone *)obj, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.obj = obj;
			}
		}
		else */if (obj->id == OBJ_SPHERE)
		{
			if (((dist = inter_sphere(obj, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.obj = obj;
			}
		}
		else if (obj->id == OBJ_CYLINDER)
		{
			if (((dist = inter_cylinder(obj, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.obj = obj;
			}
		}/*
		else if (i < scene->n_planes)
		{
			if (((dist = inter_plan(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
		}
		else if (i < scene->n_spheres)
		{
			if (((dist = inter_sphere(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 5;
				hit.id = i;
			}
		}*/
		i++;
		mem_index_obj += obj->size;
	}
	return (hit);
}
/*
float3			get_hit_normale(const __local t_scene *scene, float3 ray, t_hit hit)
{
	float3		res, save;

	if (hit.type == 1)
		res = get_cone_normale(scene, hit);
	else if (hit.type == 2)
		res = get_cylinder_normal(scene, hit);
	else if (hit.type == 4)
	{
		if (dot(PLANE[hit.id].normale, -ray) < 0)
			res = -PLANE[hit.id].normale;
		else
			res = PLANE[hit.id].normale;

		if (scene->flag & OPTION_WAVE)
		{
			//					VAGUELETTE						//
			save = res;
			save.y = res.y + 0.8 * sin((hit.pos.x + scene->u_time));
			return (fast_normalize(save));
		}
	}
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id].pos;
	save = res;
	if (scene->flag & OPTION_WAVE)
	{
		//						VAGUELETTE							//
		save.x = res.x + 0.8 * sin(res.y * 10 + scene->u_time);
		save.z = res.z + 0.8 * sin(save.x * 10 + scene->u_time);
		save.y = res.y + 0.8 * sin(res.x * 10 + scene->u_time);
	}

	return (fast_normalize(save));
}

unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	int					i;
	i = 0;
	unsigned int		res_color;
	res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	tmp = 0;
	float3				reflect;
	reflect = 0;
	float3 __private	diffuse;
	diffuse = 0;
	float __private	brightness;
	brightness = 0;
	int __private hue;
	hue = 0;
	int __private hue_light;
	hue_light = 0;
	unsigned int __private col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	col_r = 0;
	col_g = 0;
	col_b = 0;
	obj_r = 0;
	obj_g = 0;
	obj_b = 0;
	l_r = 0;
	l_g = 0;
	l_b = 0;
	t_light_ray			light_ray;
	t_hit				light_hit;
	float __private pow_of_spec;
	pow_of_spec = 0;
	int __private light_color;
	light_color = 0;
	float3 __private speculos;
	speculos = 0;

	while (i < scene->n_lights)
	{
		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0.f)
			;
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0.f)
			{
				brightness = (float __private)LIGHT[light_hit.id].brightness;

				if (hit.type == 1)
					diffuse = (float3 __private)CONES[hit.id].diff;
				else if (hit.type == 2)
					diffuse = (float3 __private)CYLIND[hit.id].diff;
				else if (hit.type == 4)
					diffuse = (float3 __private)PLANE[hit.id].diff;
				else if (hit.type == 5)
					diffuse = (float3 __private)SPHERE[hit.id].diff;
				else
					diffuse = 0.f;

				if (hit.type == 1)
					hue = (int __private)CONES[hit.id].color;
				if (hit.type == 2)
					hue = (int __private)CYLIND[hit.id].color;
				if (hit.type == 3)
					hue = (int __private)LIGHT[hit.id].color;
				if (hit.type == 4)
					hue = (int __private)PLANE[hit.id].color;
				if (hit.type == 5)
					hue = (int __private)SPHERE[hit.id].color;

				if (hit.type == 1)
					hue_light = (int __private)CONES[light_hit.id].color;
				if (hit.type == 2)
					hue_light = (int __private)CYLIND[light_hit.id].color;
				if (hit.type == 3)
					hue_light = (int __private)LIGHT[light_hit.id].color;
				if (hit.type == 4)
					hue_light = (int __private)PLANE[light_hit.id].color;
				if (hit.type == 5)
					hue_light = (int __private)SPHERE[light_hit.id].color;
				col_r = (res_color & 0xFF0000) >> 16;
				col_g = (res_color & 0x00FF00) >> 8;
				col_b = (res_color & 0x0000FF);
				obj_r = (hue & 0xFF0000) >> 16;
				obj_g = (hue & 0x00FF00) >> 8;
				obj_b = (hue & 0x00000FF);
				l_r = (hue_light & 0xFF0000) >> 16;
				l_g = (hue_light & 0x00FF00) >> 8;
				l_b = (hue_light & 0x0000FF);

				col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > 0.f)
			{
				speculos = 0.f;
				if (hit.type == 1)
					speculos = (float3 __private)CONES[hit.id].spec;
				else if (hit.type == 2)
					speculos = (float3 __private)CYLIND[hit.id].spec;
				else if (hit.type == 4)
					speculos = (float3 __private)PLANE[hit.id].spec;
				else if (hit.type == 5)
					speculos = (float3 __private)SPHERE[hit.id].spec;
				else
					speculos = 0.f;
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = native_powr(tmp, (LIGHT[light_hit.id].shrink));
				light_color = LIGHT[light_hit.id].color;
				col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
				col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
		}
		i++;
	}
	return (res_color);
}

unsigned int			phong2(const __local t_scene *scene, const t_hit hit, const float3 ray)
{

	int __private hue_light;
	unsigned int __private col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	int __private modx, mody, modz;
	int __private hue;
	float __private	brightness;
	float3 __private	diffuse;
	float3				reflect;
	float				tmp;
	unsigned int		res_color;
	int					i;
	int __private light_color;
	float3 __private speculos;
	float __private pow_of_spec;
	t_light_ray			light_ray;
	t_hit				light_hit;

	i = 0;
	if (hit.type == 1)
		hue = (int __private)CONES[hit.id].color;
	else if (hit.type == 2)
		hue = (int __private)CYLIND[hit.id].color;
	else if (hit.type == 3)
		hue = (int __private)LIGHT[hit.id].color;
	else if (hit.type == 4)
		hue = (int __private)PLANE[hit.id].color;
	else if (hit.type == 5)
		hue = (int __private)SPHERE[hit.id].color;

	if (hit.type == 1)
		hue_light = (int __private)CONES[0].color;
	else if (hit.type == 2)
		hue_light = (int __private)CYLIND[0].color;
	else if (hit.type == 3)
		hue_light = (int __private)LIGHT[0].color;
	else if (hit.type == 4)
		hue_light = (int __private)PLANE[0].color;
	else if (hit.type == 5)
		hue_light = (int __private)SPHERE[0].color;

	if (hit.type == 1)
		speculos = (float3 __private)CONES[hit.id].spec;
	else if (hit.type == 2)
		speculos = (float3 __private)CYLIND[hit.id].spec;
	else if (hit.type == 4)
		speculos = 0;//speculos = (float3 __private)PLANE[hit.id].spec;
	else if (hit.type == 5)
		speculos = (float3 __private)SPHERE[hit.id].spec;
	else
		speculos = 0.f;

	col_r = (hue & 0x00FF0000) >> 16;
	col_g = (hue & 0x0000FF00) >> 8;
	col_b = (hue & 0x000000FF);
	col_r = (0.01 + col_r * scene->ambient.x > 255 ? 255 : 0.01 + col_r * scene->ambient.x);
	col_g = (0.01 + col_g * scene->ambient.y > 255 ? 255 : 0.01 + col_g * scene->ambient.y);
	col_b = (0.01 + col_b * scene->ambient.z > 255 ? 255 : 0.01 + col_b * scene->ambient.z);
	res_color = ((col_r << 16) + (col_g << 8) + col_b);

	while (++i < scene->n_lights)
	{
	light_ray.dir = LIGHT[i].pos - hit.pos;
	light_ray.dist = fast_length(light_ray.dir);
	light_ray.dir = fast_normalize(light_ray.dir);
	light_hit = ray_hit(scene, hit.pos, light_ray.dir);
	light_hit.id = i;
	light_hit.type = 3;

	reflect = 0;
	diffuse = 0;
	brightness = 0;
	modx = 0;
	mody = 0;
	modz = 0;
	col_r = 0;
	col_g = 0;
	col_b = 0;
	obj_r = 0;
	obj_g = 0;
	obj_b = 0;
	l_r = 0;
	l_g = 0;
	l_b = 0;
	pow_of_spec = 0;
	light_color = 0;
	tmp = 0;

	float3 touch;
	touch = scene->cameras->pos + scene->cameras->dir * hit.dist;

		if (!(light_hit.dist < light_ray.dist && light_hit.dist > 0))
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0.f)
			{
				brightness = (float __private)LIGHT[light_hit.id].brightness;

				if (hit.type == 1)
					diffuse = (float3 __private)CONES[hit.id].diff;
				else if (hit.type == 2)
					diffuse = (float3 __private)CYLIND[hit.id].diff;
				else if (hit.type == 4)
				{
					diffuse = (float3 __private)PLANE[hit.id].diff;
					modx = hit.pos.x;
					mody = hit.pos.y;
					modz = hit.pos.z;
					modx = abs((int)(hit.pos.x) % 4);
					mody = abs((int)(hit.pos.y) % 4);
					modz = abs((int)(hit.pos.z) % 4);
					if (modx)
					{
						if ((modz && mody) || (!modz && !mody))
							hue = 0xFFFFFFFF;
						else
							hue = 0;
					}
					else
					{
						if ((modz && mody) || (!modz && !mody))
							hue = 0;
						else
						{
							hue = 0xFFFFFFFF;
						}
					}
				}
				else if (hit.type == 5)
					diffuse = (float3 __private)SPHERE[hit.id].diff;
				else
					diffuse = 0;

				col_r = (res_color & 0xFF0000) >> 16;
				col_g = (res_color & 0x00FF00) >> 8;
				col_b = (res_color & 0x0000FF);
				obj_r = (hue & 0xFF0000) >> 16;
				obj_g = (hue & 0x00FF00) >> 8;
				obj_b = (hue & 0x00000FF);
				l_r = (hue_light & 0xFF0000) >> 16;
				l_g = (hue_light & 0x00FF00) >> 8;
				l_b = (hue_light & 0x0000FF);

				col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > 0.f)
			{
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = native_powr(tmp, (LIGHT[light_hit.id].shrink));
				light_color = LIGHT[light_hit.id].color;
				col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
				col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
		}
		i++;
	}
	return (res_color);
}
*/
/* BACKUP OF PHONG
unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	float3				reflect = 0;

	t_light_ray			light_ray;
	t_hit				light_hit = hit_init();

	while (++i < scene->n_lights)
	{
		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		{
		}
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0)
				res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > 0)
				res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
} */
/*
static unsigned int		bounce(const __local t_scene *scene, const float3 ray, t_hit old_hit, int depth)
{
	unsigned int	color = 0;
	float3			reflex = ray;
	t_hit			new_hit;
	float			reflex_coef = 0;
	while (depth > 0)
	{
		// PREMIÈRE LOI DE SNELL-DESCARTES ///////////////////////////////////////////////////////////
		reflex = fast_normalize(reflex - (2 * (float)dot(old_hit.normale, reflex) * old_hit.normale));
		//////////////////////////////////////////////////////////////////////////////////////////////
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(scene, old_hit.obj->pos, reflex);
		//reflex_coef = get_obj_reflex(scene, old_hit);
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.obj->pos = (new_hit.dist * reflex) + old_hit.obj->pos;
			//new_hit.normale = get_hit_normale(scene, reflex, new_hit);
			new_hit.obj->pos = new_hit.obj->pos + ((new_hit.dist / 100) * new_hit.normale);
			color = 0xFFFFFF;
			//color = blend_factor(blend_add(color, phong(scene, new_hit, reflex)), reflex_coef);
		}
//		if (get_obj_reflex(scene, new_hit) == 0)
			return (color);
		old_hit = new_hit;
		--depth;
	}
	return (color);
}
*/
static unsigned int	get_pixel_color(const __local t_scene *scene, float3 ray)
{
	t_hit			hit;
	int				depth = scene->depth;
	unsigned int	color  = 0;
	unsigned int	bounce_color = 0;
	int tt = (int)scene->u_time;

	hit.dist = MAX_DIST;
	hit = ray_hit(scene, (ACTIVECAM.pos), ray);
	if (hit.dist > 0 && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
	//	hit.obj->pos = (hit.dist * ray) + (ACTIVECAM.pos);
		//hit.normale = get_hit_normale(scene, ray, hit);
	//	hit.obj->pos = hit.obj->pos + ((hit.dist / SHADOW_BIAS) * hit.normale);
		color = 0xFF0000;
		return (color);
		//color = phong(scene, hit, ray);
	//	if (depth > 0 && (get_obj_reflex(scene, hit) > 0))
	//		bounce_color = bounce(scene, ray, hit, depth);
	//	return (blend_add(color, bounce_color));
	}
	return (0xFFFFFF);
	//return (get_ambient(scene, BACKCOLOR));
}

__kernel void	ray_trace(	__global	char		*output,
							__global	t_hit		*target_obj,
							__global	t_scene		*scene_data,
							__global	t_cam		*cameras_data,
							__global	t_cone		*cones_data,
							__global	t_cylinder	*cylinders_data,
							__global	t_light		*lights_data,
							__global	t_plane		*planes_data,
							__global	t_sphere	*spheres_data,
							__local		t_scene		*scene,
							__local		t_cam		*cameras,
							__local		t_cone		*cones,
							__local		t_cylinder	*cylinders,
							__local		t_light		*lights,
							__local		t_plane		*planes,
							__local		t_sphere	*spheres,
							__private	float		u_time,
							__global	void		*global_mem_obj,
							__local		void		*mem_obj,
							__private	size_t		mem_size_obj
							)
{
 	event_t	ev;
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cones, (__global char *)cones_data, sizeof(t_cone) * scene->n_cones, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cylinders, (__global char *)cylinders_data, sizeof(t_cylinder) * scene->n_cylinders, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)lights, (__global char *)lights_data, sizeof(t_light) * scene->n_lights, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)planes, (__global char *)planes_data, sizeof(t_plane) * scene->n_planes, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)spheres, (__global char *)spheres_data, sizeof(t_sphere) * scene->n_spheres, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)mem_obj, (__global char *)global_mem_obj, mem_size_obj, 0);
	wait_group_events(1, &ev);


	uint2	pix;
	pix.x = get_global_id(0);
	pix.y = get_global_id(1);

	scene->cameras = cameras;
	scene->cones = cones;
	scene->cylinders = cylinders;
	scene->lights = lights;
	scene->planes = planes;
	scene->spheres = spheres;
	scene->u_time = u_time;
	scene->mem_obj = mem_obj;
	scene->mem_size_obj = mem_size_obj;

/*if (1)
	{
		printf("t_light_ray			: %-20lu\n", sizeof(t_light_ray));
		printf("t_cam 				: %-20lu\n", sizeof(t_cam));
		printf("t_cone 				: %-20lu\n", sizeof(t_cone));
		printf("t_cylinder 			: %-20lu\n", sizeof(t_cylinder));
		printf("t_light 			: %-20lu\n", sizeof(t_light));
		printf("t_plane 			: %-20lu\n", sizeof(t_plane));
		printf("t_sphere 			: %-20lu\n", sizeof(t_sphere));
		printf("t_tor 				: %-20lu\n", sizeof(t_tor));
		printf("t_scene 			: %-20lu\n", sizeof(t_scene));
		printf("int 				: %-20lu\n", sizeof(int));
		printf("float 				: %-20lu\n", sizeof(float));
		printf("float3 				: %-20lu\n", sizeof(float3));
		printf("\n\n");
	}*/
	/*if (!pix.x && !pix.y){
	printf("Cone\n");
	printf("t_cone 		: %-20lu\n", sizeof(t_cone));
	printf("Pos: %.2f %.2f %.2f ||",
						cones->pos.x,
						cones->pos.y,
						cones->pos.z
								);
	printf("Dir: %.2f %.2f %.2f ||",
						cones->dir.x,
						cones->dir.y,
						cones->dir.z
								);
	printf("Pos: %x ||", cones->color);
	printf("Angle: %.2f\n", cones->angle);
	printf("modr...");
}*/
	__private t_tor	mojo[2047];
	__private t_tor *tree = &mojo;

	int			id = pix.x + (scene->win_w * pix.y); // NE PAS VIRER ID CAR BESOIN DANS MACRO OUTPUTE

	unsigned int final_color = 0;

	float3	prim_ray = get_ray_cam(scene, pix);

	if (pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target_obj = ray_hit(scene, ACTIVECAM.pos, prim_ray);
	final_color = get_pixel_color(scene, prim_ray);
	/*if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);*/
	OUTPUTE = final_color;
}
