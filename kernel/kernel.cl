// CONTROL

#define BACKCOLOR 0x00999999

# define EPSILON 0.00005f
#define MAX_DIST 10000000.0
#define SHADOW_BIAS 1000

#define CAM scene->cameras
#define CONES scene->cones
#define CYLIND scene->cylinders
#define LIGHT scene->lights
#define PLANE scene->planes
#define SPHERE scene->spheres
#define ACTIVECAM scene->cameras[scene->active_cam]

#define OUTPUTE ((__global unsigned int *)output)[id]

#define OPTION_WAVE 	(1 << 1)
#define OPTION_SEPIA	(1 << 2)
#define OPTION_BW		(1 << 3)
#define OPTION_RUN		(1 << 4)

#define FLAG_DEBUG		(1 << 2)

# define OBJ_CONE			1
# define OBJ_CYLINDER		2
# define OBJ_PLANE			3
# define OBJ_SPHERE			4

typedef struct			s_object
{
	int					size;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
}						t_object;

typedef struct			s_light_ray
{
	float3				dir;
	float				dist;
}						t_light_ray;

typedef struct			s_hit
{
	float				dist;
	float3				normal;
	float3				pos;
	t_object __local	*obj;
	void				*void1;
	int					mem_index;
}						t_hit;

typedef struct			s_cam
{
	float3				pos;
	float3				dir;
	float				fov;
	float				pitch;
	float				yaw;
	float				roll;
}						t_cam;

typedef struct			s_light
{
	int					size;
	int					type;
	float3				pos;
	float3				dir;
	int					shrink;
	float				brightness;
	int					color;
}						t_light;

typedef struct			s_cone
{
	int					size;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;

	float				angle;

}						t_cone;

typedef struct			s_cylinder
{
	int					size;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;

	float				height;
	float3				base_dir;
	float				radius;
}						t_cylinder;

typedef struct			s_plane
{
	int					size;
	int					id;
	float3				pos;
	float3				normal;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
}						t_plane;

typedef struct			s_sphere
{
	int					size;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;

	float				radius;
}						t_sphere;

typedef	struct			s_tor
{
	float3				prim;
	//float3				refl;
	//float3				refr;
	unsigned int		hit_type;
	unsigned int		hit_id;
	//float				coef_refl;
	//float				coef_refr;
	unsigned int		color;
	char				check_g;
	char				check_d;
}						t_tor;

typedef struct			s_scene
{
	t_cam				__local *cameras;
//	void				*void1;
	void				__local *mem_lights;
//	void				*void4;
	void				__local *mem_obj;
//cd ..	void				*void7;
	unsigned int		n_cams;
	unsigned int		n_cones;
	unsigned int		n_cylinders;
	unsigned int		n_lights;
	unsigned int		n_planes;
	unsigned int		n_spheres;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	float3				ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
	float				u_time;
	int					flag;
	int					tor_count;
	size_t				mem_size_obj;
	size_t				mem_size_lights;
}						t_scene;

unsigned int	sepiarize(const unsigned int color)
{
	uint3	base, cooking_pot = 0;
	base.x = (color & 0x00FF0000) >> 16;
	base.y = (color & 0x0000FF00) >> 8;
	base.z = (color & 0x000000FF);
	cooking_pot.x = (base.x * 0.393) + (base.y * 0.769) + (base.z * 0.189);
	cooking_pot.y = (base.x * 0.349) + (base.y * 0.686) + (base.z * 0.168);
	cooking_pot.z = (base.x * 0.272) + (base.y * 0.534) + (base.z * 0.131);
	(cooking_pot.x > 255 ? cooking_pot.x = 255 : 0);
	(cooking_pot.y > 255 ? cooking_pot.y = 255 : 0);
	(cooking_pot.z > 255 ? cooking_pot.z = 255 : 0);
	return (((uint)cooking_pot.x << 16) + ((uint)cooking_pot.y << 8) + (uint)cooking_pot.z);
}

static unsigned int	cartoonize(const unsigned int color)
{
	uint3	base, cooking_pot = 0;
	base.x = (color & 0x00FF0000) >> 16;
	base.y = (color & 0x0000FF00) >> 8;
	base.z = (color & 0x000000FF);
	if ((base.x = base.x - base.x % 30) < 0)
		base.x = 0;
	if ((base.y = base.y - base.y % 30) < 0)
		base.y = 0;
	if ((base.z = base.z - base.z % 30) < 0)
		base.z = 0;
	return (((uint)base.x << 16) + ((uint)base.y << 8) + (uint)base.z);
}

static unsigned int	desaturate(const unsigned int color)
{
	uint3	rgb = 0;
	rgb.x = (color & 0x00FF0000) >> 16;
	rgb.y = (color & 0x0000FF00) >> 8;
	rgb.z = (color & 0x000000FF);
	float 	average = (rgb.x + rgb.y + rgb.z) / 3;
	return (((uint)average << 16) + ((uint)average << 8) + (uint)average);
}

static unsigned int	blend_multiply(const unsigned int c1, const unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	r = (r1 * r2 > 255 ? 255 : r1 * r2);
	g = (g1 * g2 > 255 ? 255 : g1 * g2);
	b = (b1 * b2 > 255 ? 255 : b1 * b2);

	return ((r << 16) + (g << 8) + b);
}

static unsigned int	blend_add(const unsigned int c1, const unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	r = (r1 + r2 > 255 ? 255 : r1 + r2);
	g = (g1 + g2 > 255 ? 255 : g1 + g2);
	b = (b1 + b2 > 255 ? 255 : b1 + b2);
	return ((r << 16) + (g << 8) + b);
}

static unsigned int	blend_factor(const unsigned int c1, const float factor)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);

	r = r1 * factor;
	g = g1 * factor;
	b = b1 * factor;
	return ((r << 16) + (g << 8) + b);
}

static unsigned int	get_ambient(const __local t_scene *scene, const unsigned int obj_color)
{
	unsigned int r, g, b;

	r = (obj_color & 0x00FF0000) >> 16;
	g = (obj_color & 0x0000FF00) >> 8;
	b = (obj_color & 0x000000FF);
	r = (0.01 + r * scene->ambient.x > 255 ? 255 : 0.01 + r * scene->ambient.x);
	g = (0.01 + g * scene->ambient.y > 255 ? 255 : 0.01 + g * scene->ambient.y);
	b = (0.01 + b * scene->ambient.z > 255 ? 255 : 0.01 + b * scene->ambient.z);
	return ((r << 16) + (g << 8) + b);
}


static float3						rotat_zyx(const float3 vect, const float pitch, const float yaw, const float roll)
{
	float3					res;
	float					rad_pitch = radians(pitch);
	float					rad_yaw = radians(yaw);
	float					rad_roll = radians(roll);

	res.x = vect.x * cos(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_pitch) * -sin(rad_roll) + cos(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) + vect.z * (-sin(rad_roll) * -sin(rad_pitch) + cos(rad_roll) * sin(rad_yaw) * cos(rad_pitch));
	res.y = vect.x * sin(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_roll) * cos(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) + vect.z * (cos(rad_roll) * -sin(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * cos(rad_pitch));
	res.z = vect.x * -sin(rad_yaw) + vect.y * cos(rad_yaw) * sin(rad_pitch) + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (res);
}

static float3						rotat_xyz(const float3 vect, const float pitch, const float yaw, const float roll)
{
	float3					res;
	float					rad_pitch = radians(pitch);
	float					rad_yaw = radians(yaw);
	float					rad_roll = radians(roll);

	res.x = vect.x * cos(rad_yaw) * cos(rad_roll) + vect.y * cos(rad_yaw) * -sin(rad_roll) + vect.z * sin(rad_yaw);
	res.y = vect.x * (-sin(rad_pitch) * -sin(rad_yaw) * cos(rad_roll) + cos(rad_pitch) * sin(rad_roll)) + vect.y * (-sin(rad_pitch) * -sin(rad_yaw) * -sin(rad_roll) + cos(rad_pitch) * cos(rad_roll)) + vect.z * cos(rad_yaw) * -sin(rad_pitch);
	res.z = vect.x * (cos(rad_pitch) * -sin(rad_yaw) * cos(rad_roll) + sin(rad_pitch) * sin(rad_roll)) + vect.y * (cos(rad_pitch) * -sin(rad_yaw) * -sin(rad_roll) + sin(rad_pitch) * cos(rad_roll)) + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (res);
}

static float3						rotat_x(const float3 vect, const float angle)
{
	float3 					res = 0;
	float					teta = radians(angle);

	res.x = (vect.x * 1) + (vect.y * 0) + (vect.z * 0);
	res.y = (vect.x * 0) + (vect.y * cos(teta)) + (vect.z * -sin(teta));
	res.z = (vect.x * 0) + (vect.y * sin(teta)) + (vect.z * cos(teta));
	return (res);
}

static float3						rotat_y(const float3 vect, const float angle)
{
	float3 					res = 0;
	float					teta = radians(angle);

	res.x = (vect.x * cos(teta)) + (vect.y * 0) + (vect.z * sin(teta));
	res.y = (vect.x * 0) + (vect.y * 1) + (vect.z * 0);
	res.z = (vect.x * -sin(teta)) + (vect.y * 0) + (vect.z * cos(teta));
	return (res);
}

static float3						rotat_z(const float3 vect, const float angle)
{
	float3 					res = 0;
	float					teta = radians(angle);

	res.x = (vect.x * cos(teta)) + (vect.y * -sin(teta)) + (vect.z * 0);
	res.y = (vect.x * sin(teta)) + (vect.y * cos(teta)) + (vect.z * 0);
	res.z = (vect.x * 0) + (vect.y * 0) + (vect.z * 1);
	return (res);
}

static t_hit			hit_init(void)
{
	t_hit		hit;

	hit.dist = 0.f;
	hit.normal = 0.f;
	hit.obj = 0;
	hit.pos = 0.f;
	hit.mem_index = 0;
	return (hit);
}

static float		inter_plan(const __local t_plane *plane, const float3 ray, const float3 origin)
{
	float	t;

	t = dot(fast_normalize(ray), fast_normalize(plane->normal));
	if (fabs(t) < 0.0005)
		return (0);
	t = (dot(plane->pos - origin, fast_normalize(plane->normal))) / t;
		if (t < 0.001)
		return (0);
	return (t);
}

static float3	get_cylinder_abc(const float radius, const float3 dir, const float3 ray, const float3 origin)
{
	float3		abc;

	// SEMBLE OK
	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

static float					inter_cylinder(const __local t_cylinder *cylinder, const float3 ray, const float3 origin)
{
	float3				abc;
	float3				pos;
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
	{
		if (cylinder->height == 0 || (dot(ray, fast_normalize(cylinder->dir) * res1 +
			dot(origin, fast_normalize(cylinder->dir))) < cylinder->height && dot(ray, fast_normalize(cylinder->dir) * res1 +
			dot(origin, fast_normalize(cylinder->dir))) > 0))
			return (res1);
	}
	if (cylinder->height ==  0 || (dot(ray, fast_normalize(cylinder->dir) * res2 +
			dot(origin, fast_normalize(cylinder->dir))) < cylinder->height && dot(ray, fast_normalize(cylinder->dir) * res2 +
			dot(origin, fast_normalize(cylinder->dir))) > 0))
		return (res2);
	else
		return (0);
}

static float3			get_cylinder_normal(const __local t_cylinder *cylinder, t_hit hit)
{
	float3 res = 0;
	float3 v = 0;
	float3 project = 0;
	float doty = 0;

	v = hit.pos - cylinder->pos;
	doty = dot(v, fast_normalize(cylinder->dir));

	project = doty * fast_normalize(cylinder->dir);
	res = v - project;
	return (fast_normalize(res));
}

static float3	get_sphere_abc(const float radius, const float3 ray, const float3 origin)
{
	float3		abc = 0;

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (radius * radius);
	return (abc);
}

static float3	get_cone_abc(const __local t_cone *cone, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		k = radians(cone->angle);

	k = tan(k);
	k = 1 + k * k;
	abc.x = dot(ray, ray) - (k * (dot(ray, cone->dir) * dot(ray, cone->dir)));
	abc.y = 2 * (dot(ray, origin) - (k * \
			(dot(ray, cone->dir) * dot(origin, cone->dir))));
	abc.z = (dot(origin, origin) - \
			(k * (dot(origin, cone->dir) * dot(origin, cone->dir))));
	return (abc);
}

static void			print_mem(__local t_cone *cone)
{
	printf("dir : x = %f, y = %f, z = %f\npos : x = %f, y = %f, z = %f\nangle = %f\n\n", cone->dir.x, cone->dir.y, cone->dir.z, cone->pos.x, cone->pos.y, cone->pos.z, cone->angle);
}

static void			print_vect(float3 v)
{
	printf("ray : x = %f, y = %f, z = %f\n\n", v.x, v.y, v.z);
}

static float			inter_cone(const __local t_cone *cone, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;

	pos = origin - cone->pos;
	abc = get_cone_abc(cone, ray, pos);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return (-abc[1]) / (2 * abc[0]);
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return (res1);
	return (res2);
}

static float3			get_cone_normal(const __local t_cone *cone, const t_hit hit)
{
	float3 res = 0;
	float3 v = 0;
	float3 project = 0;
	float doty = 0;

	v = hit.pos - cone->pos;
	doty = dot(v, cone->dir);
	project = doty * fast_normalize(cone->dir);
	res = v - project;
	return (fast_normalize(res));
}


static float			inter_sphere(const __local t_sphere *sphere, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;

	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
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



static t_hit			ray_hit(const __local t_scene *scene, const float3 origin, const float3 ray)
{
	t_hit						hit;
	float						dist;
	t_object 		__local		*obj;
	size_t						mem_index_obj;

	dist = 0;
	hit = hit_init();
	mem_index_obj = 0;
	obj = 0;

	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = scene->mem_obj + mem_index_obj;
		if (obj->id == OBJ_SPHERE)
			dist = inter_sphere(obj, ray, origin);
		else if (obj->id == OBJ_CYLINDER)
			dist = inter_cylinder(obj, ray, origin);
		else if (obj->id == OBJ_PLANE)
			dist = inter_plan(obj, ray, origin);
		else if (obj->id == OBJ_CONE)
			dist = inter_cone(obj, ray, origin);
		if ((dist < hit.dist || hit.dist == 0) && dist > EPSILON)
		{
			hit.dist = dist;
			hit.obj = obj;
			hit.mem_index = mem_index_obj;
		}
		mem_index_obj += obj->size;
	}
	return (hit);
}

static float3			get_hit_normal(const __local t_scene *scene, float3 ray, t_hit hit)
{
	float3		res, save;

	if (hit.obj->id == OBJ_SPHERE)
		res = hit.pos - hit.obj->pos;
	else if (hit.obj->id == OBJ_CYLINDER)
		res = get_cylinder_normal(hit.obj, hit);
	else if (hit.obj->id == OBJ_CONE)
		res = get_cone_normal(hit.obj, hit);
	else if (hit.obj->id == OBJ_PLANE)
	{
		if (dot(hit.obj->dir, -ray) < 0)
			res = -hit.obj->dir;
		else
			res = hit.obj->dir;

		if (scene->flag & OPTION_WAVE)
		{
			/*					VAGUELETTE						*/
			save = res;
			save.y = res.y + 0.8 * sin((hit.pos.x + scene->u_time));
			return (fast_normalize(save));
		}
	}
	save = res;
//	if (scene->flag & OPTION_WAVE)
	if (1)
	{
		/*						VAGUELETTE							*/
		save.x = res.x + 0.8 * sin(res.y * 10 + scene->u_time);
		//save.z = res.z + 0.8 * sin(res.x * 10 + scene->u_time);
		save.z = res.z + 0.8 * sin(save.x * 10 + scene->u_time);
		save.y = res.y + 0.8 * sin(res.x * 10 + scene->u_time);
	}

	return (fast_normalize(save));
}

static unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	t_object __local		*obj;
	t_light __local		*light;
	size_t				mem_index_lights;

	unsigned int		res_color;
	float				tmp;
	float3				reflect;
	float3 __private	diffuse;
	float __private	brightness;
	int __private hue;
	int __private hue_light;
	unsigned int __private col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	t_light_ray			light_ray;
	t_hit					light_hit;
	float __private pow_of_spec;
	int __private light_color;
	float3 __private speculos;

	tmp = 0;
	reflect = 0;
	diffuse = 0;
	brightness = 0;
	hue = 0;
	hue_light = 0;

	obj = hit.obj;
	hue = obj->color;

	col_r = (hue & 0x00FF0000) >> 16;
	col_g = (hue & 0x0000FF00) >> 8;
	col_b = (hue & 0x000000FF);
	col_r = (0.01 + col_r * scene->ambient.x > 255 ? 255 : 0.01 + col_r * scene->ambient.x);
	col_g = (0.01 + col_g * scene->ambient.y > 255 ? 255 : 0.01 + col_g * scene->ambient.y);
	col_b = (0.01 + col_b * scene->ambient.z > 255 ? 255 : 0.01 + col_b * scene->ambient.z);
	res_color = ((col_r << 16) + (col_g << 8) + col_b);
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
	speculos = 0;
	mem_index_lights = 0;
	while (mem_index_lights < scene->mem_size_lights)
	{
		light = scene->mem_lights + mem_index_lights;

		tmp = 0;
		light_ray.dir = light->pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		if (!(light_hit.dist < light_ray.dist && light_hit.dist > EPSILON))
		{
			tmp = (dot(hit.normal, light_ray.dir));
			if (tmp > EPSILON)
			{
				brightness = (float __private)light->brightness;
				diffuse = (float3 __private)obj->diff;
				hue = (int __private)obj->color;
				hue_light = light->color;

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

			reflect = fast_normalize(((float)(2.0 * dot(hit.normal, light_ray.dir)) * hit.normal) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > EPSILON)
			{
				speculos = obj->spec;
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = native_powr(tmp, (light->shrink));
				light_color = light->color;
				col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
				col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
		}
		mem_index_lights += light->size;
	}
	return (res_color);
}

static unsigned int		bounce(const __local t_scene *scene, const float3 ray, t_hit old_hit, int depth)
{
	unsigned int	color;
	float3			reflex;
	t_hit			new_hit;
	float			reflex_coef;

	reflex = ray;
	new_hit = hit_init();
	color = 0;
	reflex_coef = 0;
	while (depth > 0)
	{
		// PREMIÈRE LOI DE SNELL-DESCARTES ///////////////////////////////////////////////////////////
		reflex = fast_normalize(reflex - (2 * (float)dot(old_hit.normal, reflex) * old_hit.normal));
		//////////////////////////////////////////////////////////////////////////////////////////////
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(scene, old_hit.pos, reflex);
		reflex_coef = old_hit.obj->reflex;
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * reflex) + old_hit.pos;
			new_hit.normal = get_hit_normal(scene, reflex, new_hit);
			new_hit.pos = new_hit.pos + ((new_hit.dist / 100) * new_hit.normal);
			color = blend_factor(blend_add(color, phong(scene, new_hit, reflex)), reflex_coef);
		}
		if (new_hit.obj->reflex == 0)
			return (color);
		old_hit = new_hit;
		--depth;
	}
	return (color);
}

static unsigned int		refract(const __local t_scene *scene, const float3 ray, t_hit old_hit) // pour le plan, indice de refraction (pour tout objet non plein)
{
	float3			refract = ray;
	t_hit			new_hit;
	float			c1 = 0;
	float			c2 = 0;
	float			eta = 0;
	float			base = 1;
	int				i = 0;
	while (old_hit.obj->refract != 0 && ++i < 50)
	{
		c1 = dot(old_hit.normal, refract);
		eta = base / old_hit.obj->refract;
		if (c1 < 0)
			c1 = -c1;
		else
		{
			old_hit.normal = -old_hit.normal;
			eta = old_hit.obj->refract / base;
		}
		c2 = sqrt(1 - ((eta * eta) * (1 - (c1 * c1))));
		// DEUXIEME LOIS DE SNELL-DECARTES /////////////////////////////////////////////
		refract = fast_normalize((eta * refract) + ((eta * c1) - c2) * old_hit.normal);
		////////////////////////////////////////////////////////////////////////////////
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(scene, old_hit.pos, refract);
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * refract) + old_hit.pos;
			new_hit.normal = get_hit_normal(scene, refract, new_hit);
			if (new_hit.mem_index != old_hit.mem_index && new_hit.obj->refract != 0)
				new_hit.pos = new_hit.pos + ((new_hit.dist / 10000) * -new_hit.normal);//pour refract en chaine, inverser la normale pour le decalage de la position
			else
				new_hit.pos = new_hit.pos + ((new_hit.dist / 10000) * new_hit.normal);
			if (new_hit.obj->refract == 0)
				return (phong(scene, new_hit, refract));
		}
		else
			return (0);
		old_hit = new_hit;
	}
	return (phong(scene, new_hit, refract));
}

static unsigned int	get_pixel_color(const __local t_scene *scene, float3 ray, __global int *target, bool isHim)
{
	t_hit			hit;
	int				depth;
	unsigned int	color;
	unsigned int	bounce_color;

	hit = hit_init();
	hit.dist = MAX_DIST;
	depth = scene->depth;
	color = 0;
	bounce_color = 0;
	hit.dist = MAX_DIST;
	hit = ray_hit(scene, (ACTIVECAM.pos), ray);
	if (isHim)
		*target = hit.mem_index;
	if (hit.dist > EPSILON && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normal = get_hit_normal(scene, ray, hit);
		if (hit.obj->refract != 0)
			hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * -hit.normal); //pour refract, inverser le decalage de la position
		else
			hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * hit.normal);
		color = phong(scene, hit, ray);
		if (depth > 0 && hit.obj->reflex > 0)
			bounce_color = bounce(scene, ray, hit, depth);
		if (hit.obj->refract != 0)
			return (bounce_color = refract(scene, ray, hit));
		return (blend_add(color, bounce_color));
	}
	return (get_ambient(scene, BACKCOLOR));
}

static float3						get_ray_cam(__local t_scene *scene, const uint2 pix)
{
	float3					cam_ray = 0;
	float					ratio = (float)scene->win_w / (float)scene->win_h;

	cam_ray.x = ((2 * ((pix.x + 0.5) / scene->win_w)) - 1) * ratio * (tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.y = ((1 - (2 * ((pix.y + 0.5) / scene->win_h))) * tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.z = 1;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(fast_normalize(cam_ray));
}

__kernel void	ray_trace(	__global	char		*output,

							__global	char		*global_mem_objects,
							__local		char		*mem_objects,
							__private	size_t		mem_size_objects,

							__private	float		u_time,

							__global	t_scene		*scene_data,
							__global	t_cam		*cameras_data,

							__local		t_scene		*scene,
							__local		t_cam		*cameras,

							__global	char		*global_mem_lights,
							__local		char		*mem_lights,
							__private	size_t		mem_size_lights,

							__global	int		*target
									)
{

 	event_t			ev;
	int				id;
	uint2			pix;
	float3			prim_ray;
	unsigned int	final_color;
	float			ratio;
	float3			cam_ray;

	final_color = 0;

	ev = async_work_group_copy((__local char *)mem_objects, (__global char *)global_mem_objects, mem_size_objects, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)mem_lights, (__global char *)global_mem_lights, mem_size_lights, 0);
	wait_group_events(1, &ev);

	pix.x = get_global_id(0);// % scene->win_w;
	pix.y = get_global_id(1);// / scene->win_w;
	id = pix.x + (scene->win_w * pix.y);

	scene->cameras = cameras;
	scene->mem_lights = mem_lights;
	scene->u_time = u_time;
	scene->mem_obj = mem_objects;
	scene->mem_size_obj = mem_size_objects;
	scene->mem_size_lights = mem_size_lights;

	prim_ray = get_ray_cam(scene, pix);
	final_color = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y));
	if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);

	// ALPHA INSERT and RGB SWAP
	int4 swap;
	swap.w = 255;
	swap.x = (final_color & 0x00FF0000) >> 16;
	swap.y = (final_color & 0x0000FF00) >> 8;
	swap.z = (final_color & 0x000000FF);
	final_color = ((swap.w << 24) + (swap.z << 16) + (swap.y << 8) + swap.x);
	((__global unsigned int *)output)[id] = final_color;
}
