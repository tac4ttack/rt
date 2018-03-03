#include "kernel_header.hcl"
#include "kernel_matrix.hcl"
#include "kernel_cam.hcl"
//#include "kernel_color.hcl"
//#include "kernel_cone.hcl"
//#include "kernel_cylinder.hcl"
#include "kernel_data.hcl"
#include "kernel_debug.hcl"
//#include "kernel_plane.hcl"
//#include "kernel_sphere.hcl"

static float4	get_cylinder_abc(const float radius, const float4 dir, const float4 ray, const float4 origin)
{
	float4		abc;

	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

float4			get_cylinder_normal(const __local t_cylinder *cylinder, t_hit hit)
{
	float4 res = 0;
	float4 v = 0;
	float4 project = 0;
	float doty = 0;

	v = hit.pos - cylinder->pos;
	doty = dot(v, fast_normalize(cylinder->dir));

	project = doty * fast_normalize(cylinder->dir);
	res = v - project;
	return (fast_normalize(res));
}

float					inter_cylinder(const __local t_cylinder *cylinder, const float4 ray, const float4 origin)
{
	float4				abc;
	float4				pos;
	float				d;
	float				res1 = 0;
	float				res2 = 0;
	float				m;

	pos = origin - cylinder->pos;
	abc = get_cylinder_abc(cylinder->radius, fast_normalize(cylinder->dir), ray, pos);
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
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return (res2);
	return (res1);
}

float4	get_sphere_abc(const __local t_sphere *sphere, const float4 ray, const float4 origin)
{
	float4		abc = 0;

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (sphere->radius * sphere->radius);
	return (abc);
}

float			inter_sphere(const __local t_sphere *sphere, const float4 ray, const float4 origin)
{
	float4		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float4		pos = 0;

	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return (res1);
	return (res2);
}

t_hit			ray_hit(const __local t_scene *scene, const float4 origin, const float4 ray, int x, int y)
{
//	printf("Enter: Rayhit\n");
	t_hit						hit;
	float						dist;
	t_object 		__local		*obj;
	size_t						mem_index_obj;

	dist = 0;
	hit = hit_init();
	mem_index_obj = 0;
	obj = 0;

//	printf("0 0\n");
//	printf("Origin:  %.2f %.2f %.2f\n", origin.x, origin.y, origin.z);
//	printf("Ray   :  %.2f %.2f %.2f\n", ray.x, ray.y, ray.z);
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = scene->mem_obj + mem_index_obj;
		if (obj->id == OBJ_SPHERE)
			dist = inter_sphere(obj, ray, origin);
		else if (obj->id == OBJ_CYLINDER)
			dist = inter_cylinder(obj, ray, origin);
		if ((dist < hit.dist || hit.dist == 0) && dist > EPSILON)
		{
			hit.dist = dist;
			hit.obj = obj;
		}
		mem_index_obj += obj->size;
	}
	return (hit);
}

float4			get_hit_normale(const __local t_scene *scene, float4 ray, t_hit hit)
{
	float4		res;

	if (hit.obj->id == OBJ_SPHERE)
		res = hit.pos - hit.obj->pos;
	else if (hit.obj->id == OBJ_CYLINDER)
		res = get_cylinder_normal(hit.obj, hit);

	return (fast_normalize(res));
}
/*
unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float4 ray)
{
	int					i;
	i = 0;
	unsigned int		res_color;
	res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	tmp = 0;
	float4				reflect;
	reflect = 0;
	float4 __private	diffuse;
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
	float4 __private speculos;
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
					diffuse = (float4 __private)CONES[hit.id].diff;
				else if (hit.type == 2)
					diffuse = (float4 __private)CYLIND[hit.id].diff;
				else if (hit.type == 4)
					diffuse = (float4 __private)PLANE[hit.id].diff;
				else if (hit.type == 5)
					diffuse = (float4 __private)SPHERE[hit.id].diff;
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
					speculos = (float4 __private)CONES[hit.id].spec;
				else if (hit.type == 2)
					speculos = (float4 __private)CYLIND[hit.id].spec;
				else if (hit.type == 4)
					speculos = (float4 __private)PLANE[hit.id].spec;
				else if (hit.type == 5)
					speculos = (float4 __private)SPHERE[hit.id].spec;
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
*/

unsigned int			phong2(const __local t_scene *scene, const t_hit hit, const float4 ray, int x, int y)
{
	const __local 		t_object *obj;

	int __private 		hue_light;
	unsigned int __private col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	int __private 		modx, mody, modz;
	int __private 		hue;
	float __private		brightness;
	float4 __private	diffuse;
	float4				reflect;
	float				tmp;
	unsigned int		res_color;
	int					i;
	int __private 		light_color;
	float4 __private 	speculos;
	float __private		 pow_of_spec;
	t_light_ray			light_ray;
	t_hit				light_hit;

	i = 0;
	obj = hit.obj;
	hue = obj->color;
	speculos = obj->spec;

	col_r = (hue & 0x00FF0000) >> 16;
	col_g = (hue & 0x0000FF00) >> 8;
	col_b = (hue & 0x000000FF);
	col_r = (0.01 + col_r * scene->ambient.x > 255 ? 255 : 0.01 + col_r * scene->ambient.x);
	col_g = (0.01 + col_g * scene->ambient.y > 255 ? 255 : 0.01 + col_g * scene->ambient.y);
	col_b = (0.01 + col_b * scene->ambient.z > 255 ? 255 : 0.01 + col_b * scene->ambient.z);
	res_color = ((col_r << 16) + (col_g << 8) + col_b);

	light_ray.dir = LIGHT[i].pos - hit.pos;
	light_ray.dist = fast_length(light_ray.dir);
	light_ray.dir = fast_normalize(light_ray.dir);
//	printf("GOOOOO\n");
	light_hit = ray_hit(scene, hit.pos, light_ray.dir, x, y);

	hue_light = LIGHT[i].color;

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

		if (!(light_hit.dist < light_ray.dist && light_hit.dist > 0))
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0.f)
			{
				brightness = (float __private)LIGHT[i].brightness;

				diffuse = obj->diff;

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
		}
		i++;

	return (res_color);
}

/* BACKUP OF PHONG
unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float4 ray)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	float4				reflect = 0;

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
static unsigned int		bounce(const __local t_scene *scene, const float4 ray, t_hit old_hit, int depth)
{
	unsigned int	color = 0;
	float4			reflex = ray;
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
		//	if (get_obj_reflex(scene, new_hit) == 0)
			return (color);
		old_hit = new_hit;
		--depth;
	}
	return (color);
}
*/

unsigned int	get_pixel_color(const __local t_scene *scene, float4 ray, int x, int y)
{
	t_hit			hit;
	int				depth;
	unsigned int	color;
	unsigned int	bounce_color;

	hit = hit_init();
	depth = scene->depth;
	color = 0;
	bounce_color = 0;
	hit.dist = MAX_DIST;
	hit = ray_hit(scene, (ACTIVECAM.pos), ray, x, y);
//	printf("Exit1st ray\n");
	if (hit.dist > EPSILON && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
//		printf("Is Hit\n");
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normale = get_hit_normale(scene, ray, hit);
		hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * hit.normale);
		color = phong2(scene, hit, ray, x, y);
	//	if (depth > 0 && (get_obj_reflex(scene, hit) > 0))
	//		bounce_color = bounce(scene, ray, hit, depth);
	//	return (blend_add(color, bounce_color));
	}
//	printf("Return\n");
	return (color);
	//return (get_ambient(scene, BACKCOLOR));
}

__kernel void	ray_trace(	__global	char		*output,
							__global	char		*global_mem_obj,
							__local		char		*mem_obj,
							__private	size_t		mem_size_obj,
							__private	float		u_time,
							__global	t_scene		*scene_data,
							__global	t_cam		*cameras_data,
							__global	t_light		*lights_data,
							__local		t_scene		*scene,
							__local		t_cam		*cameras,
							__local		t_light		*lights
							)
{
	/*
	__global	t_hit		*target_obj,
	*/
 	event_t			ev;
	int				id;
	uint2			pix;
	float4			prim_ray;
	unsigned int	final_color;
	float			ratio;
	float4			cam_ray;

	final_color = 0;
	pix.x = get_global_id(0) % 1024;
	pix.y = get_global_id(0) / 1024;
	id = pix.x + (1024 * pix.y);


	ev = async_work_group_copy((__local char *)mem_obj, (__global char *)global_mem_obj, mem_size_obj, 0);
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	ev = async_work_group_copy((__local char *)lights, (__global char *)lights_data, sizeof(t_light) * scene->n_lights, 0);
	wait_group_events(1, &ev);



	if(!pix.x && !pix.y)
	{

		printf("NB CAM: %i\n", scene->n_cams);
		printf("%.2f %.2f %.2f\n", cameras->pitch, cameras->yaw, cameras->roll);
		printf("%.2f %.2f %.2f\n", cameras->pos.x, cameras->pos.y, cameras->pos.z);
	}

	scene->cameras = cameras;
	scene->lights = lights;
	scene->u_time = u_time;
	scene->mem_obj = mem_obj;
	scene->mem_size_obj = mem_size_obj;

	cam_ray = 0;
	ratio = 1024 / 720;
	cam_ray.x = ((2 * ((pix.x + 0.5) / scene->win_w)) - 1) * ratio * (tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.y = ((1 - (2 * ((pix.y + 0.5) / scene->win_h))) * tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.z = 1;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	prim_ray = fast_normalize(cam_ray);
	/*if (pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target_obj = ray_hit(scene, ACTIVECAM.pos, prim_ray);*/
	final_color = get_pixel_color(scene, prim_ray,  pix.x, pix.y);
	/*if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);*/
	((__global unsigned int *)output)[id] = final_color;

}
