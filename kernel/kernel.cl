#ifdef cl_khr_fp64
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
#error "Double precision floating point not supported by OpenCL implementation."
#endif

#define BACKCOLOR 0x00999999

#define EPSILON 0.00005f
#define MAX_DIST 10000000.0
#define SHADOW_BIAS 1000

#define CAM scene->cameras
#define CONES scene->cones
#define CYLIND scene->cylinders
#define LIGHT scene->lights
#define PLANE scene->planes
#define SPHERE scene->spheres
#define ACTIVECAM scene->cameras[scene->active_cam]

#define OPTION_WAVE 	(1 << 1)
#define OPTION_SEPIA	(1 << 2)
#define OPTION_BW		(1 << 3)
#define OPTION_RUN		(1 << 4)
#define OPTION_INVERT	(1 << 7)
#define OPTION_CARTOON	(1 << 8)
#define OPTION_STEREO	(1 << 9)

#define OBJ_FLAG_WAVES			(1 << 1)
#define OBJ_FLAG_CHECKERED		(1 << 2)
#define OBJ_FLAG_DIFF_MAP		(1 << 3)
#define OBJ_FLAG_BUMP_MAP		(1 << 4)

# define OBJ_CAM			1
# define OBJ_LIGHT			2
# define OBJ_CONE			3
# define OBJ_CYLINDER		4
# define OBJ_PLANE			5
# define OBJ_SPHERE			6
# define OBJ_ELLIPSOID		7
# define OBJ_THOR			8
# define OBJ_BOX			9

/*
** CAM AND LIGHT STRUCTS ///////////////////////////////////////////////////////
*/
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
////////////////////////////////////////////////////////////////////////////////

/*
** OBJECTS STRUCTURES //////////////////////////////////////////////////////////
*/
typedef struct			s_object
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
}						t_object;

typedef struct			s_box
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float3				min;
	float3				max;
}						t_box;

typedef struct			s_cone
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float				angle;
	float3				u_axis;
}						t_cone;

typedef struct			s_cylinder
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float				height;
	float3				base_dir;
	float				radius;
	float3				u_axis;
}						t_cylinder;

typedef struct			s_plane
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				normal;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float				radius;
	float3				u_axis;
}						t_plane;

typedef struct			s_sphere
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float				radius;
}						t_sphere;

typedef struct			s_ellipsoid
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float				radius;
	float3				axis_size;
}						t_ellipsoid;

typedef struct			s_thor
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float3				dir;
	float3				diff;
	float3				spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;

	float				lil_radius;
	float				big_radius;
}						t_thor;
////////////////////////////////////////////////////////////////////////////////

/*
** TREE OF RAYS STRUCT /////////////////////////////////////////////////////////
*/
typedef	struct			s_tor
{
	int					activate;
	float3				pos;
	float3				prim;
	float3				normale;
	float				coef_ref;
	float				coef_tra;
	float				opacity;
	unsigned int		color;
	int					check_g;  //?
	int					check_d;  //?
	uint				mem_index;
	int					id;
	int					type;
}						t_tor;
////////////////////////////////////////////////////////////////////////////////

/*
** CORE STRUCTS ////////////////////////////////////////////////////////////////
*/
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
	int					mem_index;
	float				opacity;
	unsigned int		color;
}						t_hit;

typedef struct			s_tex
{
	unsigned int		pixel_array[12076155];
	int					width;
	int					height;
}						t_tex;

typedef struct			s_scene
{
	t_cam				__local *cameras;
//	void				*dummy_pedro;
	void				__local *mem_lights;  //repassé en void à cause de l'erreur compilation, sinon pour oclgrind foutre char
//	void				*dummy_gomez;
	void				__local *mem_obj; //repassé en void à cause de l'erreur compilation, sinon pour oclgrind foutre char
//	void				*dummy_ramon;
	unsigned int		__global *texture_earth;
	unsigned int		__global *texture_moon;
	unsigned int		__global *texture_earth_cloud;
	unsigned int		__global *texture_star;
	unsigned int		n_cams;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	float3				ambient;
	unsigned int		mou_x;
	unsigned int		mou_y;
	unsigned int		depth;
	float				u_time;
	int					flag;
	unsigned int		over_sampling;
	unsigned int		mem_size_obj;
	unsigned int		mem_size_lights;
	float3				check_p1;
	float3				check_p2;
	float3				waves_p1;
	float3				waves_p2;
}						t_scene;
////////////////////////////////////////////////////////////////////////////////



/*
** UNCLASSIFIED FUNCTIONS
*/
static t_hit	hit_init(void)
{
	t_hit		hit;

	hit.dist = 0.f;
	hit.normal = 0.f;
	
	hit.obj = -1; // dangling dangerouss!
	
	hit.color = 0;
	hit.pos = 0.f;
	hit.mem_index = 0;
	hit.opacity = 0;
	return (hit);
}
////////////////////////////////////////////////////////////////////////////////



/*
** PRINT FUNCTIONS /////////////////////////////////////////////////////////////
*/
static void			print_mem(__local t_cone *cone)
{
	printf("dir : x = %f, y = %f, z = %f\npos : x = %f, y = %f, z = %f\nangle = %f\n\n", cone->dir.x, cone->dir.y, cone->dir.z, cone->pos.x, cone->pos.y, cone->pos.z, cone->angle);
}

static void			print_vect(float3 v)
{
	printf("ray : x = %f, y = %f, z = %f\n\n", v.x, v.y, v.z);
}
////////////////////////////////////////////////////////////////////////////////



/*
** COLOR FUNCTIONS /////////////////////////////////////////////////////////////
*/
static unsigned int	sepiarize(const unsigned int color)
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

static unsigned int	invert(const unsigned int color)
{
	uint3	base = 0;
	base.x = (color & 0x00FF0000) >> 16;
	base.y = (color & 0x0000FF00) >> 8;
	base.z = (color & 0x000000FF);
	base.x = 255 - base.x;
	base.y = 255 - base.y;
	base.z = 255 - base.z;
	return (((uint)base.x << 16) + ((uint)base.y << 8) + (uint)base.z);
}

// not working
static unsigned int	cartoonize(const unsigned int color)
{
	uint3	base;
	base.x = (color & 0x00FF0000) >> 16;
	base.y = (color & 0x0000FF00) >> 8;
	base.z = (color & 0x000000FF);
	base.x = base.x - base.x % 90;
	base.y = base.y - base.y % 90;
	base.z = base.z - base.z % 90;
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

static unsigned int	blend_med(const unsigned int c1, const unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	r =  (r1 + r2) / 2;
	g =  (g1 + g2) / 2;
	b =  (b1 + b2) / 2;
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
////////////////////////////////////////////////////////////////////////////////



/*
** ROTATION AND MATRIX SHIT FUNCTIONS //////////////////////////////////////////
*/
static float3	rotat_zyx(const float3 vect, const float pitch, const float yaw, const float roll)
{
	float3		res;
	float		rad_pitch = radians(pitch);
	float		rad_yaw = radians(yaw);
	float		rad_roll = radians(roll);

	res.x = vect.x * cos(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_pitch) * -sin(rad_roll) + cos(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) + vect.z * (-sin(rad_roll) * -sin(rad_pitch) + cos(rad_roll) * sin(rad_yaw) * cos(rad_pitch));
	res.y = vect.x * sin(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_roll) * cos(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) + vect.z * (cos(rad_roll) * -sin(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * cos(rad_pitch));
	res.z = vect.x * -sin(rad_yaw) + vect.y * cos(rad_yaw) * sin(rad_pitch) + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (res);
}

static float3	rotat_xyz(const float3 vect, const float pitch, const float yaw, const float roll)
{
	float3		res;
	float		rad_pitch = radians(pitch);
	float		rad_yaw = radians(yaw);
	float		rad_roll = radians(roll);

	res.x = vect.x * cos(rad_yaw) * cos(rad_roll) + vect.y * cos(rad_yaw) * -sin(rad_roll) + vect.z * sin(rad_yaw);
	res.y = vect.x * (-sin(rad_pitch) * -sin(rad_yaw) * cos(rad_roll) + cos(rad_pitch) * sin(rad_roll)) + vect.y * (-sin(rad_pitch) * -sin(rad_yaw) * -sin(rad_roll) + cos(rad_pitch) * cos(rad_roll)) + vect.z * cos(rad_yaw) * -sin(rad_pitch);
	res.z = vect.x * (cos(rad_pitch) * -sin(rad_yaw) * cos(rad_roll) + sin(rad_pitch) * sin(rad_roll)) + vect.y * (cos(rad_pitch) * -sin(rad_yaw) * -sin(rad_roll) + sin(rad_pitch) * cos(rad_roll)) + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (res);
}

static float3	rotat_x(const float3 vect, const float angle)
{
	float3 		res = 0;
	float		teta = radians(angle);

	res.x = (vect.x * 1) + (vect.y * 0) + (vect.z * 0);
	res.y = (vect.x * 0) + (vect.y * cos(teta)) + (vect.z * -sin(teta));
	res.z = (vect.x * 0) + (vect.y * sin(teta)) + (vect.z * cos(teta));
	return (res);
}

static float3	rotat_y(const float3 vect, const float angle)
{
	float3 		res = 0;
	float		teta = radians(angle);

	res.x = (vect.x * cos(teta)) + (vect.y * 0) + (vect.z * sin(teta));
	res.y = (vect.x * 0) + (vect.y * 1) + (vect.z * 0);
	res.z = (vect.x * -sin(teta)) + (vect.y * 0) + (vect.z * cos(teta));
	return (res);
}

static float3	rotat_z(const float3 vect, const float angle)
{
	float3 		res = 0;
	float		teta = radians(angle);

	res.x = (vect.x * cos(teta)) + (vect.y * -sin(teta)) + (vect.z * 0);
	res.y = (vect.x * sin(teta)) + (vect.y * cos(teta)) + (vect.z * 0);
	res.z = (vect.x * 0) + (vect.y * 0) + (vect.z * 1);
	return (res);
}
////////////////////////////////////////////////////////////////////////////////



/*
** ELLIPSOID FUNCTIONS
*/
static float3	vector_get_rotate(const float3 *this, const __local float3 *rot)
{
	float3		n;
	float		tmp;

	n = *this;
	if (rot->x)
	{
		tmp = n.y * cos(rot->x) - n.z * sin(rot->x);
		n.z = n.y * sin(rot->x) + n.z * cos(rot->x);
		n.y = tmp;
	}
	if (rot->y)
	{
		tmp = n.x * cos(rot->y) + n.z * sin(rot->y);
		n.z = n.x * -sin(rot->y) + n.z * cos(rot->y);
		n.x = tmp;
	}
	if (rot->z)
	{
		tmp = n.x * cos(rot->z) - n.y * sin(rot->z);
		n.y = n.x * sin(rot->z) + n.y * cos(rot->z);
		n.x = tmp;
	}
	return (n);
}

static float3	vector_get_inverse(const float3 *this, const __local float3 *rot)
{
	float3		n;
	float		tmp;

	n = *this;
	if (rot->z)
	{
		tmp = n.x * cos(rot->z) - n.y * -sin(rot->z);
		n.y = n.x * -sin(rot->z) + n.y * cos(rot->z);
		n.x = tmp;
	}
	if (rot->y)
	{
		tmp = n.x * cos(rot->y) + n.z * -sin(rot->y);
		n.z = n.x * sin(rot->y) + n.z * cos(rot->y);
		n.x = tmp;
	}
	if (rot->x)
	{
		tmp = n.y * cos(rot->x) - n.z * -sin(rot->x);
		n.z = n.y * -sin(rot->x) + n.z * cos(rot->x);
		n.y = tmp;
	}
	return (n);
}

static bool		solve_quadratic(const float a, const float b, const float c, float *inter0, float *inter1)
{
	float 		discr;
	float 		tmp;
	float 		q;

	q = 0;
	discr = b * b - 4 * a * c;
	tmp = 0;
	if (discr < 0)
		return (false);
	else if (discr < EPSILON)
	{
		*inter0 = -0.5 * b / a;
		*inter1 = *inter0;
	}
	else
	{
		q = (b > 0) ? (-0.5 * (b + sqrt(discr))): (-0.5 * (b - sqrt(discr)));
		*inter0 = q / a;
		*inter1 = c / q;
	}
	if (*inter0 > *inter1)
	{
		tmp = *inter0;
		*inter0 = *inter1;
		*inter1 = tmp;
	}
	if (*inter0 < 0)
	{
		if (*inter1 < 0)
			return (false);
	}
	return (true);
}

static float3		get_ellipsoid_normal(const __local t_ellipsoid *ellipsoid, const t_hit *hit)
{
	float3 pos = hit->pos - ellipsoid->pos;
	pos = vector_get_rotate(&pos, &ellipsoid->dir);

	float3 res;

	res.x = (pos.x) / (ellipsoid->axis_size.x * ellipsoid->axis_size.x);
	res.y = (pos.y) / (ellipsoid->axis_size.y * ellipsoid->axis_size.y);
	res.z = (pos.z) / (ellipsoid->axis_size.z * ellipsoid->axis_size.z);
	res = vector_get_inverse(&res, &ellipsoid->dir);
	return (res);
}

static float	inter_ellipsoid(const __local t_ellipsoid *ellipsoid, float3 ray, float3 origin)
{
	float3		abc = 0;
	float		inter0, inter1;
	float3		pos = 0;


	pos = origin - ellipsoid->pos;
	pos = vector_get_rotate(&pos, &ellipsoid->dir);
	ray = vector_get_rotate(&ray, &ellipsoid->dir);
	ray /= ellipsoid->axis_size;
	pos /= ellipsoid->axis_size;

	abc.x = (ray.x * ray.x +
	 	ray.y * ray.y +
	 	ray.z * ray.z);
	abc.y = (2 * pos.x * ray.x +
		 2 * pos.y * ray.y +
		 2 * pos.z * ray.z);
	abc.z = (pos.x * pos.x +
		 pos.y * pos.y +
		 pos.z * pos.z) - (ellipsoid->radius * ellipsoid->radius);

	 if (!solve_quadratic(abc.x, abc.y, abc.z, &inter0, &inter1))
		return (0);
	if (inter0 < 0)
		return (inter1);
	return (inter0);
}
////////////////////////////////////////////////////////////////////////////////



/*
** PLANES FUNCTIONS ////////////////////////////////////////////////////////////
*/
static unsigned int		plane_checkerboard(float3 normale, float3 pos)
{
	float3			u_axis;
	float3			v_axis;
	int2			uv;

	u_axis.x = normale.y;
	u_axis.y = normale.z;
	u_axis.z = -normale.x;
	v_axis = cross(u_axis, normale);
	uv.x = (int)floor(dot(pos, u_axis) / 4);
	uv.y = (int)floor(dot(pos, v_axis) / 4);
	if (uv.x % 2 == 0)
	{
		if (uv.y % 2 == 0)
			return (0);
		else
			return (0x00FFFFFF);
	}
	else if (uv.y % 2 == 0)
		return (0x00FFFFFF);
	return (0);
}

static unsigned int		plane_texture(float3 normale, float3 pos, float3 u_axis, unsigned int __global *texture, int width, int height)
{
	float3			v_axis;
	int2			uv;

	v_axis = cross(u_axis, normale);
	uv.x = (int)floor(dot(pos, u_axis) * 10 /* + decalage */);// * le ratio
	uv.y = (int)floor(dot(pos, v_axis) * 10 /* + decalage */);// idem
	uv.x %= width;
	uv.y %= height;
	if (uv.x < 0)
		uv.x += width;
	if (uv.y < 0)
		uv.y += height;
	uv.y = (uv.y - 1500) * -1;
	return (texture[uv.y + uv.x * width]);
}

static float	inter_plan(const __local t_plane *plane, const float3 ray, const float3 origin)
{
	float		t;

	t = dot(fast_normalize(ray), fast_normalize(plane->normal));
	if (fabs(t) < 0.0005)
		return (0);
	t = (dot(plane->pos - origin, fast_normalize(plane->normal))) / t;
		if (t < 0.001)
		return (0);
	return (t);
}
////////////////////////////////////////////////////////////////////////////////




/*
** CYLINDER FUNCTIONS //////////////////////////////////////////////////////////
*/
static unsigned int		cylinder_texture(float3 pos, float3 dir, float3 u_axis, float ratio, unsigned int __global *texture, int width, int height, float radius)
{
	unsigned int	color = 0;
	float3			v_axis;
	float			npos;
	float			vpos;
	int2			uv;

	v_axis = cross(u_axis, dir);
	npos = fast_length(dot(pos, dir) * dir);
	while (npos > ratio)
		npos -= ratio;
	if (dot(pos, dir) < 0)
		npos = (npos - ratio) * -1;
	uv.y = (int)floor((npos / ratio) * height);
	npos = dot(pos, u_axis);
	vpos = dot(pos, v_axis);
	uv.x = (int)floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * width);
	// uv.y = (uv.y - height) * -1;
	// if ((uv.x += decx) > width)   Decalage;
	// 	uv.x -= width;
	// if ((uv.y += decy) > height)
	// 	uv.y -= height;
	color = (unsigned int)texture[uv.x + (uv.y * width)];
	return (color);
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

static float3	get_cylinder_normal(const __local t_cylinder *cylinder, t_hit hit)
{
	float3		res;
	float3		v;
	float3		project;
	float3		cyl_dir;
	float		doty;

	res = 0;
	v = 0;
	project = 0;
	doty = 0;
	cyl_dir = fast_normalize(cylinder->dir);
	v = hit.pos - cylinder->pos;
	doty = dot(v, cyl_dir);
	project = doty * cyl_dir;
	res = v - project;
	return (fast_normalize(res));
}

static float	inter_cylinder(const __local t_cylinder *cylinder, const float3 ray, const float3 origin)
{
	float3		abc;
	float3		pos;
	float		d;
	float		res1;
	float		res2;

	res1 = 0;
	res2 = 0;
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
////////////////////////////////////////////////////////////////////////////////



/*
** TORUS FUNCTIONS /////////////////////////////////////////////////////////////
*/
// static double	ft_max(double u, double v)
// {
// 	if (u >= v)
// 		return (u);
// 	return (v);
// }

// static double	ft_ret(double4 tab)
// {
// 	double		ret;
// 	int			i;
	
// 	ret = -1.0;
// 	i = 0;
// 	while(i < 4)
// 	{
// 		if(tab[i] > 0.0001 && ret == -1)
// 			ret = tab[i];
// 		if (tab[i] < ret && tab[i] > 0.0001 )
// 			ret = tab[i];
// 		i++;
// 	}
// 	if (ret == -1.0)
// 		ret = 0.0;
// 	return (ret);
// }

// static double3	ft_solve_3(double a, double b, double c, double d)
// {
// 	double3 result;
	
// 	double3 abc;
// 	abc.x = c / d;
// 	abc.y = b / d;
// 	abc.z = a / d;
	
// 	double r = (2.0f * abc.x * abc.x * abc.x - 9.0f * abc.x * abc.y + 27.0f * abc.z) / 54.0f;
// 	double q = (abc.x * abc.x - 3.0f * abc.y) / 9.0f;
// 	double qcube = q * q * q;
// 	double theta;
// 	double sqrtq;
// 	double e;
	
// 	d = qcube - r * r;
// 	if (d >= 0.0001f)
// 	{	
// 		if (q < 0.0f)
// 		{
// 			result.x = 0.0f;
// 			result.y = 0.0f;
// 			result.z = 0.0f;
// 			return (result);
// 		}
// 		theta = acos(r / sqrt(qcube));
// 		sqrtq = sqrt(q);
// 		result.x = -2.0f * sqrtq * cos(theta / 3.0f) - abc.x / 3.0f;
// 		result.y = -2.0f * sqrtq * cos((theta + 2.0f * M_PI) / 3.0f ) - abc.x / 3.0f;
// 		result.z = -2.0f * sqrtq * cos((theta + 4.0f * M_PI) / 3.0f ) - abc.x / 3.0f;
// 	}
// 	else
// 	{	
// 		e = pow(sqrt((double)-d) + fabs((double)r), (double)(1.0f / 3.0f));		
// 		if (r > 0.0001f)
// 			e = -e;
// 		result.x = result.y = result.z = (e + q / e) - abc.x / 3.0f;
// 	}
// 	return (result);
// }

// static double	ft_solve_4(double4 t, double wut)
// {
// 	double4 res;

// 	double4 a;
// 	a.w = t.w / wut;
// 	a.x = t.x / wut;
// 	a.y = t.y / wut;
// 	a.z = t.z / wut;

// 	double3 b;
// 	b.x = 4.0f * a.y * a.w - a.x * a.x - a.z * a.z * a.w;
// 	b.y = a.x * a.z - 4.0f * a.w;
// 	b.z = -a.y;

// 	double3 roots;
// 	roots = ft_solve_3(b.x, b.y, b.z, 1.0f);

// 	double rsqrt;
// 	double rrec;
// 	double d;	
// 	double e;
// 	double y = ft_max(roots.x, ft_max(roots.y, roots.z));
// 	double r = 0.25f * a.z * a.z - a.y + y;	

// 	if (r < 0.0001f)
// 		return (0.0f);
// 	r = sqrt(r);
// 	if (r == 0.0001f)
// 	{
// 		d = sqrt(0.75f * a.z * a.z - 2.0f * a.y + 2.0f * sqrt(y * y - 4.0f * a.w));
// 		e = sqrt(0.75f * a.z * a.z - 2.0f * a.y - 2.0f * sqrt(y * y - 4.0f * a.w));
// 	}
// 	else
// 	{
// 		rsqrt = r * r;
// 		rrec = 1.0f / r;
// 		d = sqrt(0.75f * a.z * a.z - rsqrt - 2.0f * a.y + 0.25f * rrec * (4.0f * a.z * a.y - 8.0f * a.x - a.z * a.z * a.z));
// 		e = sqrt(0.75f * a.z * a.z - rsqrt - 2.0f * a.y - 0.25f * rrec * (4.0f * a.z * a.y - 8.0f * a.x - a.z * a.z * a.z));
// 	}

// 	res.w = -0.25f * a.z + 0.5f * r + 0.5f * d;
// 	res.x = -0.25f * a.z + 0.5f * r - 0.5f * d;
// 	res.y = -0.25f * a.z - 0.5f * r + 0.5f * e;
// 	res.z = -0.25f * a.z - 0.5f * r - 0.5f * e;

// 	return(ft_ret(res));
// }

// static float		inter_thor(const __local t_thor *thor, const float3 ray, const float3 origin)
// {
// 	double8 z;
// 	double4	res;
// 	double3	q;
// 	float	dist;

// 	double3	double_ray_origin;
// 	double_ray_origin.x = (double)origin.x;
// 	double_ray_origin.y = (double)origin.y;
// 	double_ray_origin.z = (double)origin.z;
// 	double3 double_ray_dir;
// 	double_ray_dir.x = (double)ray.x;
// 	double_ray_dir.y = (double)ray.y;
// 	double_ray_dir.z = (double)ray.z;

// 	double3 double_thor_dir;
// 	double_thor_dir.x = (double)thor->dir.x;
// 	double_thor_dir.y = (double)thor->dir.y;
// 	double_thor_dir.z = (double)thor->dir.z;
// 	double3 double_thor_pos;
// 	double_thor_pos.x = (double)thor->pos.x;
// 	double_thor_pos.y = (double)thor->pos.y;
// 	double_thor_pos.z = (double)thor->pos.z;

// 	q = double_ray_origin - double_thor_pos;

// 	z.s0 = dot(double_thor_dir, q);
// 	z.s1 = dot(double_thor_dir, double_ray_dir);
// 	z.s2 = 1. - pow(z.s1, 2.);
// 	z.s3 = 2. * (dot(q, double_ray_dir) - z.s0 * z.s1);
// 	z.s4 = dot(q, q) - pow(z.s0, 2.);
// 	z.s5 = dot(q, q) + pow((double)thor->big_radius, 2.) - pow((double)thor->lil_radius, 2.);

// 	res.w = 4. * dot(q, double_ray_dir);
// 	res.x = 2. * z.s5 + pow(res.w, 2.) / 4. - 4. * pow((double)thor->big_radius, 2.) * z.s2;
// 	res.y = res.w * z.s5 - 4. * pow((double)thor->big_radius, 2.) * z.s3;
// 	res.z = pow(z.s5, 2.) - 4. * pow((double)thor->big_radius, 2.) * z.s4 + 1e-3;
	
// 	double wut = double_ray_dir.x * double_ray_dir.x + double_ray_dir.y * double_ray_dir.y + double_ray_dir.z * double_ray_dir.z;
	
// 	dist = (float)ft_solve_4(res, wut);
// 	return (dist);
// }


// BACKUP
static float	ft_max(float u, float v)
{
	if (u >= v)
		return (u);
	return (v);
}

static float	ft_ret(float *tab)
{
	float		ret;
	int			i;
	ret = -1.0;
	i = 0;
	while(i < 4)
	{
		if(tab[i] > 0.0001 && ret == -1)
			ret = tab[i];
			if (tab[i] < ret && tab[i] > 0.0001 )
			ret = tab[i];
		i++;
	}
	if (ret == -1.0)
		ret = 0.0;
	return (ret);
}

static float3	ft_solve_3(float a, float b, float c, float d)
{
	float 	a1;
	a1 = c / d;
	float a2;
	a2 = b / d;
	float a3;
	a3 = a / d;
	float3 Result;
	float theta;
	float sqrtQ;
	float e;
	float Q = (a1 * a1 - 3.0f * a2) / 9.0f;
	float R = (2.0f * a1 * a1 * a1 - 9.0f * a1 * a2 + 27.0f * a3) / 54.0f;
	float Qcubed = Q * Q * Q;
	d = Qcubed - R * R;
	if ( d >= 0.0001f )
	{	
		if ( Q < 0.0f )
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
			Result.z = 0.0f;
				return (Result);
		}
		theta = acos(R / sqrt(Qcubed));
		sqrtQ = sqrt(Q);
		Result.x = -2.0f * sqrtQ * cos(theta / 3.0f) - a1 / 3.0f;
		Result.y = -2.0f * sqrtQ * cos((theta + 2.0f * M_PI) / 3.0f ) - a1 / 3.0f;
		Result.z = -2.0f * sqrtQ * cos((theta + 4.0f * M_PI) / 3.0f ) - a1 / 3.0f;
	}
	else
	{	
		e = pow(sqrt(-d) + fabs(R), 1.0f/ 3.0f);	
		if ( R > 0.0001f )
			e = -e;
		Result.x = Result.y = Result.z = (e + Q / e) - a1 / 3.0f;
	}
	return (Result);
}
static float	ft_solve_4(float t[5])
{
	float Result[4];
	float3 Roots;
	float Rsquare;
	float Rrec;
	float a0= t[0] / t[4];
	float a1 = t[1] / t[4];
	float a2 = t[2] / t[4];
	float  a3 = t[3] / t[4];
	float D;
	float E;
	float3 b;
	b.x = 4.0f * a2 * a0 - a1 * a1 - a3 * a3 * a0;
	b.y = a1 * a3 - 4.0f * a0;
	b.z = -a2;
	Roots = ft_solve_3(b.x, b.y, b.z, 1.0f);
	float	y = ft_max(Roots.x, ft_max(Roots.y, Roots.z));
	float R = 0.25f * a3 * a3 - a2 + y;
	if ( R < 0.0001f)
		return (0.0f);
	R = sqrt(R);
	if ( R == 0.0001f )
	{
		D = sqrt( 0.75f * a3 * a3 - 2.0f * a2 + 2.0f * sqrt( y * y - 4.0f * a0 ) );
		E = sqrt( 0.75f * a3 * a3 - 2.0f * a2 - 2.0f * sqrt( y * y - 4.0f * a0 ) );
	}
	else
	{
		Rsquare = R * R;
		Rrec = 1.0f / R;
		D = sqrt( 0.75f * a3 * a3 - Rsquare - 2.0f * a2 + 0.25f * Rrec * (4.0f * a3 * a2 - 8.0f * a1 - a3 * a3 * a3) );
		E = sqrt( 0.75f * a3 * a3 - Rsquare - 2.0f * a2 - 0.25f * Rrec * (4.0f * a3 * a2 - 8.0f * a1 - a3 * a3 * a3) );
	}
	Result[0] = -0.25f * a3 + 0.5f * R + 0.5f * D;
	Result[1] = -0.25f * a3 + 0.5f * R - 0.5f * D;
	Result[2] =  -0.25f * a3 - 0.5f * R + 0.5f * E;
	Result[3] = -0.25f * a3 - 0.5f * R - 0.5f * E;
	return(ft_ret(Result));
return (0.0f);
}

static float		inter_thor(const __local t_thor *thor, const float3 ray, const float3 origin)
{
	float		c[5];
	float3	k;
	float		e;
	float r = thor->big_radius;
	k.x = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	e = (origin.x - thor->pos.x) * (origin.x - thor->pos.x) + (origin.y - thor->pos.y) *
	(origin.y - thor->pos.y) + (origin.z - thor->pos.z) * (origin.z - thor->pos.z) -
	r * r - thor->lil_radius * thor->lil_radius;
	k.z = (origin.x - thor->pos.x) * ray.x + (origin.y - thor->pos.y) * ray.y +
	(origin.z - thor->pos.z) * ray.z;
	k.y = 4.0f * r * r;
	c[0] = e * e - k.y * (thor->lil_radius * thor->lil_radius - (origin.y - thor->pos.y) *
	(origin.y - thor->pos.y));
	c[1] = 4.0f * k.z * e + 2.0f * k.y * (origin.y - thor->pos.y) * ray.y;
	c[2] = 2.0f * k.x * e + 4.0f * k.z * k.z + k.y * ray.y * ray.y;
	c[3] = 4.0f * k.x * k.z;
	c[4] = k.x * k.x;
	return (ft_solve_4(c));
}

static float3 get_thor_normal(const __local t_thor *thor, const t_hit hit)
{
	float3	res;
	float		c;
	float R = thor->lil_radius;
	float r = thor->big_radius;

	c = ((hit.pos.x - thor->pos.x) * (hit.pos.x - thor->pos.x) + (hit.pos.y - thor->pos.y) * (hit.pos.y
				- thor->pos.y) + (hit.pos.z - thor->pos.z) * (hit.pos.z - thor->pos.z)
			- r * r - R * R);
	res.x = 4.0 * c * (hit.pos.x - thor->pos.x);
	res.y = 4.0 * (hit.pos.y - thor->pos.y) * (c + 2.0 * r * r);
	res.z = 4.0 * c * (hit.pos.z - thor->pos.z);
	return (res);
}

////////////////////////////////////////////////////////////////////////////////



/*
** SPHERES FUNCTIONS ///////////////////////////////////////////////////////////
*/
static unsigned int		sphere_checkerboard(float3 dir, unsigned int color)
{
	int2	uv;

	uv.x = (int)floor((0.5 + (atan2(dir.z, dir.x) / (2 * 3.1415))) * 20);
	uv.y = (int)floor((0.5 - (asin(dir.y) / 3.1415)) * 10);
	if (uv.x % 2 == 0)
	{
		if (uv.y % 2 == 0)
			return (0);
		else
			return (color);
	}
	else if (uv.y % 2 == 0)
			return (color);
	return (0);
}

static unsigned int		sphere_texture(float3 pos, unsigned int __global *texture, int width, int height, int i, float u_time)
{
	unsigned int	color = 0;
	int2			uv;

	uv.x = (int)floor((0.5 + (atan2(pos.z, pos.x) / (2 * M_PI))) * width);
	uv.y = (int)floor((0.5 - (asin(pos.y) / M_PI)) * height);
	uv.y = (uv.y - height) * -1;
	if (i == 1)					//deplacement gauche / droite
		uv.x += u_time * 100;
	if (i == 2)
		uv.x += u_time * 200;
	if (uv.x > width)
		uv.x -= width;
	// if ((uv.y += decy) > height) deplacement haut / bas
	// 	uv.y -= height;
	color = texture[uv.x + uv.y * width];
	return (color);
}

static float3	get_sphere_abc(const float radius, const float3 ray, const float3 origin)
{
	float3		abc = 0;

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (radius * radius);
	return (abc);
}

static float	inter_sphere(const __local t_sphere *sphere, const float3 ray, const float3 origin)
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
////////////////////////////////////////////////////////////////////////////////



/*
** CONES FUNCTIONS /////////////////////////////////////////////////////////////
*/
static unsigned int		cone_texture(float3 pos, float3 dir, float3 u_axis, float ratio, unsigned int __global *texture, int width, int height)
{
	unsigned int	color = 0;
	float3			v_axis;
	float			npos;
	float			vpos;
	float			radius;
	int2			uv;
	// ratio = echelle de la texture

	v_axis = cross(u_axis, dir);
	npos = dot(pos, dir);
	radius = fast_length(pos - (npos * dir));
	while (npos > ratio)
		npos -= ratio;
	while (npos < 0)
		npos += ratio;
	uv.y = (int)floor((fast_length(npos * dir) / ratio) * height);
	npos = dot(pos, u_axis);
	vpos = dot(pos, v_axis);
	uv.x = (int)floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * width);
	color = (unsigned int)texture[uv.x + (uv.y * width)];
	return (color);
}

static float3	get_cone_normal(const __local t_cone *cone, const t_hit hit)
{
	float3		res;
	float3		final;
	float3		v;
	float3		project;
	float		doty;
	float		m;
	float		r;
	float		k;
	float3		dir;

	dir =  fast_normalize(cone->dir);
	v = hit.pos - cone->pos;
	doty = dot(v, dir);
	project = doty * dir;
	m = fast_length(project);
	res = v - project;
	// final = res;
	// r = fast_length(res);
	// if (m = 0)
	// {
	// 	// printf("tcho");
	// 	return (fast_normalize(res));
	// }
	// if (m < 0)
	// 	m = -m;
	// k = r / m;
	// r = 1 + (k * k);
	// k = r * m;
	// final = v - (k * dir);
	// res = v - res;
	return (fast_normalize(res));
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

static float	inter_cone(const __local t_cone *cone, const float3 ray, const float3 origin)
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
////////////////////////////////////////////////////////////////////////////////



/*
** BOXES FUNCTIONS /////////////////////////////////////////////////////////////
*/
static void	fswap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static float			inter_box(const __local t_box *box, float3 ray, float3 origin, t_hit *hit)
{
	float tmin = (box->pos.x + box->min.x - origin.x) / ray.x;
	float tmax = (box->pos.x + box->max.x - origin.x) / ray.x;
	if (tmin > tmax)
		fswap(&tmin, &tmax);
	float tymin = (box->pos.y + box->min.y - origin.y) / ray.y;
	float tymax = (box->pos.y + box->max.y - origin.y) / ray.y;
	if (tymin > tymax)
		fswap(&tymin, &tymax);
	if ((tmin > tymax) || (tymin > tmax))
		return 0;
	if (tymin > tmin)
	{
		tmin = tymin;
	}
	if (tymax < tmax)
	{
		tmax = tymax;
	}

	float tzmin = (box->pos.z + box->min.z - origin.z) / ray.z;
	float tzmax = (box->pos.z + box->max.z - origin.z) / ray.z;
	if (tzmin > tzmax)
		fswap(&tzmin, &tzmax);
	if ((tmin > tzmax) || (tzmin > tmax))
		return 0;
	if (tzmin > tmin)
	{
		tmin = tzmin;
	}
	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	;

	/*float3 t;
	t = ray * tmin + (origin + box->min);
	return (fast_length(t));*/
	//return true;

	float3		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;

	pos = origin - box->pos;
	abc = get_sphere_abc(2, ray, pos);
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
////////////////////////////////////////////////////////////////////////////////



static t_hit			ray_hit(const __local t_scene *scene, const float3 origin, const float3 ray, float lightdist)
{
	t_hit						hit;
	float						dist;
	t_object 		__local		*obj;
	uint						mem_index_obj;

	dist = 0;
	hit = hit_init();
	mem_index_obj = 0;
	obj = 0;
	if (lightdist == 0)
		hit.opacity = 1;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = scene->mem_obj + mem_index_obj;
		if (obj->type == OBJ_SPHERE)
		 	dist = inter_sphere((__local struct s_sphere *)obj, ray, origin);
		//	ABORT
		// else if (obj->type == OBJ_BOX)
		//  	dist = inter_box(obj, ray, origin, &hit);
		else if (obj->type == OBJ_CYLINDER)
		 	dist = inter_cylinder((__local struct s_cylinder *)obj, ray, origin);
		else if (obj->type == OBJ_PLANE)
		 	dist = inter_plan((__local struct s_plane *)obj, ray, origin);
		else if (obj->type == OBJ_CONE)
		 	dist = inter_cone((__local struct s_cone *)obj, ray, origin);
		else if (obj->type == OBJ_ELLIPSOID)
		   	dist = inter_ellipsoid((__local struct s_ellipsoid *)obj, ray, origin);
		 else if (obj->type == OBJ_THOR)
		 	dist = inter_thor((__local struct s_thor *)obj, ray, origin);
		if (lightdist > 0 && dist < lightdist && dist > EPSILON)
			hit.opacity += obj->opacity;
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
	res = 0;
	if (hit.obj->type == OBJ_SPHERE)
	 	res = hit.pos - hit.obj->pos;
	if (hit.obj->type == OBJ_CYLINDER)
		res = get_cylinder_normal((__local t_cylinder *)hit.obj, hit);
	if (hit.obj->type == OBJ_CONE)
		res = get_cone_normal((__local t_cone *)hit.obj, hit);
	if (hit.obj->type == OBJ_ELLIPSOID)
		res = get_ellipsoid_normal((__local t_ellipsoid *)hit.obj, &hit);
//	ABORT
//	else if (hit.obj->type == OBJ_THOR)
//		res = get_thor_normal(hit.obj, hit);
	else if (hit.obj->type == OBJ_PLANE)
	{
		if (dot(hit.obj->dir, -ray) < 0)
			res = -hit.obj->dir;
		else
			res = hit.obj->dir;
	}

	save = res;
	if (hit.obj->flags & OBJ_FLAG_WAVES)
	{
		if (hit.obj->type == OBJ_PLANE)
			save.y = res.y + scene->waves_p1.x * sin((hit.pos.x + scene->u_time));
		else
		{
			save.x = res.x + scene->waves_p1.x * sin(res.y * scene->waves_p2.x + scene->u_time); //p1.x p2.x
			save.z = res.z + scene->waves_p1.y * sin(res.x * scene->waves_p2.y + scene->u_time);
			save.y = res.y + scene->waves_p1.z * sin(res.x * scene->waves_p2.z + scene->u_time);
		}
	}

	return (fast_normalize(save));
}

static unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	t_object __local		*obj;
	t_light __local			*light;
	uint					mem_index_lights;

	unsigned int			res_color;
	float					tmp;
	float3					reflect;
	float3 __private		diffuse;
	float __private			brightness;
	unsigned int __private 	hue;
	unsigned int __private	hue_light;
	unsigned int __private 	col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	t_light_ray				light_ray;
	t_hit					light_hit;
	float __private 		pow_of_spec;
	int __private 			light_color;
	float3 __private 		speculos;

	tmp = 0;
	reflect = 0;
	diffuse = 0;
	brightness = 0;
	hue_light = 0;
	pow_of_spec = 0;
	light_color = 0;
	speculos = 0;
	mem_index_lights = 0;

	obj = hit.obj;
	if ((hit.obj->flags & OBJ_FLAG_CHECKERED) || hit.obj->flags & OBJ_FLAG_DIFF_MAP)
		hue = hit.color;
	else
		hue = obj->color;

	col_r = (hue & 0x00FF0000) >> 16;
	col_g = (hue & 0x0000FF00) >> 8;
	col_b = (hue & 0x000000FF);
	col_r = (0.01 + col_r * scene->ambient.x > 255 ? 255 : 0.01 + col_r * scene->ambient.x);
	col_g = (0.01 + col_g * scene->ambient.y > 255 ? 255 : 0.01 + col_g * scene->ambient.y);
	col_b = (0.01 + col_b * scene->ambient.z > 255 ? 255 : 0.01 + col_b * scene->ambient.z);
	res_color = ((col_r << 16) + (col_g << 8) + col_b);
	
	// RESET NON UTILE?
	col_r = 0;
	col_g = 0;
	col_b = 0;
	obj_r = 0;
	obj_g = 0;
	obj_b = 0;
	l_r = 0;
	l_g = 0;
	l_b = 0;
	//
	
	while (mem_index_lights < scene->mem_size_lights)
	{
		tmp = 0;
		light = scene->mem_lights + mem_index_lights;		
		light_ray.dir = light->pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir, light_ray.dist);
		if (!(light_hit.dist < light_ray.dist && light_hit.dist > EPSILON) || light_hit.opacity < 1)
		{
			tmp = (dot(hit.normal, light_ray.dir));
			if (tmp > EPSILON)
			{
				brightness = (float __private)light->brightness;
				diffuse = (float3 __private)obj->diff;
				// hue = (int __private)obj->color; // marqué comme inutile dans branch texturegtk
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
				// commented lines are failed tonemaping test
			//	col_r = (col_r > 255 ? col_r / (col_r + 1) : col_r);
				(col_g > 255 ? col_g = 255 : 0);
			//	col_g = (col_g > 255 ? col_g / (col_g + 1) : col_g);
				(col_b > 255 ? col_b = 255 : 0);
			//	col_b = (col_b > 255 ? col_b / (col_b + 1) : col_b);
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
			//	col_r = (col_r > 255 ? col_r / (col_r + 1) : col_r);
				(col_g > 255 ? col_g = 255 : 0);
			//	col_g = (col_g > 255 ? col_g / (col_g + 1) : col_g);
				(col_b > 255 ? col_b = 255 : 0);
			//	col_b = (col_b > 255 ? col_b / (col_b + 1) : col_b);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			res_color = blend_factor(res_color, ((light_hit.opacity - 1) * -1));
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
		new_hit = ray_hit(scene, old_hit.pos, reflex, 0);
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

	old_hit.pos = old_hit.pos + ((old_hit.dist / SHADOW_BIAS) * -(old_hit.normal * 2)); //pour refract, inverser le decalage de la position
	while (old_hit.obj->refract != 0 && old_hit.obj->opacity < 1 && ++i < 50)
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
		new_hit = ray_hit(scene, old_hit.pos, refract, 0);
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * refract) + old_hit.pos;
			new_hit.normal = get_hit_normal(scene, refract, new_hit);
			if (new_hit.mem_index != old_hit.mem_index && new_hit.obj->refract != 0 && new_hit.obj->opacity < 1)
				new_hit.pos = new_hit.pos + ((new_hit.dist / 10000) * -new_hit.normal);	//pour refract en chaine, inverser la normale pour le decalage de la position
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

static float3		refract_ray(const __local t_scene *scene, const float3 ray, float3 normale, float tra) // pour le plan, indice de refraction (pour tout objet non plein)
{
	float3			refract = 0;
	float			c1 = 0;
	float			c2 = 0;
	float			eta = 0;

	c1 = dot(normale, ray);
	eta = 1 / tra;
	if (c1 < 0)
		c1 = -c1;
	else
	{
		normale = -normale;
		eta = tra;
	}
	c2 = sqrt(1 - ((eta * eta) * (1 - (c1 * c1))));
	// DEUXIEME LOIS DE SNELL-DECARTES /////////////////////////////////////////////
	refract = fast_normalize((eta * ray) + ((eta * c1) - c2) * normale);
	////////////////////////////////////////////////////////////////////////////////
	return (refract);
}

static float3		bounce_ray(const __local t_scene *scene, const float3 ray, t_tor tor)
{
	float3			reflex;
	float			reflex_coef;

	reflex = 0;
	reflex_coef = 0;
	// PREMIÈRE LOI DE SNELL-DESCARTES ///////////////////////////////////////////////////////////
	reflex = fast_normalize(ray - (2 * (float)dot(tor.normale, ray) * tor.normale));
	//////////////////////////////////////////////////////////////////////////////////////////////
	return (reflex);
}

static float		reflect_ratio(float n1, float n2, float cos1, float sint)
{
	float			fr1 = 0;
	float			fr2 = 0;
	float			cos2 = sqrt(1 - sint * sint);

	if (cos1 >= 0)
	{
		fr1 = n1;
		n1 = n2;
		n2 = fr1;
	}
	else
		cos1 = -cos1;
	if (n1 / n2 * sqrt(1 - cos1 * cos1) > 1)
		return (1);
	fr1 = (n2 * cos1 - n1 * cos2) / (n2 * cos1 + n1 * cos2);
	fr2 = (n1 * cos2 - n2 * cos1) / (n1 * cos2 + n2 * cos1);
	fr1 *= fr1;
	fr2 *= fr2;
	return ((fr1 + fr2) / 2);
}

static t_tor		tor_push(float3 ray, float3 normale, float3 pos, float coef_ref, float coef_tra, float opacity, unsigned int color, uint mem_index, int id, int type)
{
	t_tor			tor;

	tor.prim = ray;
	tor.pos = pos;
	tor.normale = normale;
	tor.coef_ref = coef_ref;
	tor.coef_tra = coef_tra;
	tor.opacity = opacity;
	tor.color = color;
	tor.mem_index = mem_index;
	tor.activate = 1;
	tor.id = id;
	tor.type = type;
	return (tor);
}

static int			tor_height(int i)
{
	int				h = 0;

	while ((i = (i - 1) / 2) >= 0)
		h++;
	return (h);
}

static unsigned int	tor_final_color(t_tor *tor)
{
	int				i = 63;
	unsigned int	color = 0;

	while (i > 0)
	{
		if (tor[i].activate == 0 && tor[i * 2 + 1].mem_index == tor[i].mem_index)
			;
		else
		{
			color = blend_add(tor[(i + 1) * 2].color, tor[i * 2 + 1].color);
			if (tor[i].coef_tra != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
			else if (tor[i].coef_ref != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
			else
			tor[i].color = blend_add(color, tor[i].color);
		}
		i = i - 1;
		while (i > 0 && tor[i].activate == 0)
			i = i - 1;
	}
	color = blend_add(tor[(i + 1) * 2].color, tor[i * 2 + 1].color);
	if (tor[0].coef_tra != 0)
		color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
	else
		color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
	return (color);
}

static unsigned int	fresnel(const __local t_scene *scene, float3 ray, t_hit old_hit, int depth, unsigned int color)
{
	t_hit			new_hit;
	unsigned int	ncolor = 0;
	float3			refract = 0;
	float3			bounce = 0;
	float			fr = 0;
	float			ft = 0;
	float			eta = 0;
	float			cos1 = 0;
	float			sint = 0;
	t_tor			tor[128];
	int				i = 0;

	depth = (int)pow(2.f, (float)depth) - 1;
	i = 0;
	while (i < 128)
	{
		tor[i].activate = 0;
		tor[i].prim = 0;
		tor[i].normale = 0;
		tor[i].pos = 0;
		tor[i].coef_ref = 0;
		tor[i].coef_tra = 0;
		tor[i].color = 0;
		tor[i].check_g = 0;		// ?
		tor[i].check_d = 0;		// ?
		tor[i].opacity = 0;
		tor[i].mem_index = 0;
		tor[i].id = 0;
		tor[i].type = 0;
		i++;
	}
	i = 0;
	tor[i] = tor_push(ray, old_hit.normal, old_hit.pos, old_hit.obj->reflex, old_hit.obj->refract, old_hit.obj->opacity, color, old_hit.mem_index, old_hit.obj->id, old_hit.obj->type);
	while (i < 63 && i < depth)
	{
		eta = 1 / tor[i].coef_tra;
		cos1 = dot(tor[i].normale, tor[i].prim);
		if (cos1 >= 0)
			eta = tor[i].coef_tra;
		if (cos1 >= 0)
			sint = tor[i].coef_tra * sqrt(1 - cos1 * cos1);
		else
			sint = 1 / tor[i].coef_tra * sqrt(1 - cos1 * cos1);
		if (sint >= 1)
			fr = 1;
		else
			fr = reflect_ratio(1, tor[i].coef_tra, cos1, sint);
		if (fr > 0.9)
			fr = 1;
		if (fr < 0.1)
			fr = 0;
		ft = 1 - fr;
		if (fr < 1)
		{
			tor[i].check_g = 1;
			if (tor[i].type != OBJ_PLANE)
				refract = refract_ray(scene, tor[i].prim, tor[i].normale, tor[i].coef_tra);
			else
				refract = tor[i].prim;
			if (cos1 < 0)
				new_hit = ray_hit(scene, tor[i].pos + (0.0001f * 2 * -tor[i].normale), refract, 0);
			else
				new_hit = ray_hit(scene, tor[i].pos, refract, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				if (cos1 < 0)
					new_hit.pos = (new_hit.dist * refract) + tor[i].pos + (0.0001f * 2 * -tor[i].normale);
				else
					new_hit.pos = (new_hit.dist * refract) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, refract, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000 * new_hit.normal);
				ncolor = blend_factor(phong(scene, new_hit, refract), ft);
				tor[i * 2 + 1] = tor_push(refract, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, new_hit.obj->id, old_hit.obj->type);
			}
		}
		else
			tor[i].check_g = 0;
		if ((tor[i].opacity < 1 && tor[i].coef_tra >= 1) || tor[i].coef_ref != 0)
		{
			tor[i].check_d = 1;
			bounce = bounce_ray(scene, tor[i].prim, tor[i]);
			new_hit = ray_hit(scene, tor[i].pos, bounce, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				new_hit.pos = (new_hit.dist * bounce) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, bounce, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000 * new_hit.normal);
				ncolor = blend_factor(phong(scene, new_hit, bounce), fr);
				tor[i * 2 + 2] = tor_push(bounce, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, new_hit.obj->id, old_hit.obj->type);
			}
		}
		i = i + 1;
		while (i < 63 && tor[i].activate == 0)
			i = i + 1;
	}
	return (tor_final_color(tor));
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
	hit = ray_hit(scene, (ACTIVECAM.pos), ray, 0);
	if ((isHim == 1) && ((int)hit.obj != -1))
		*target = hit.mem_index;
	if (hit.dist > EPSILON && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normal = get_hit_normal(scene, ray, hit);
			hit.pos = hit.pos + (0.001f * hit.normal);
		hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * hit.normal);
		
		// if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
		//  	hit.color = sphere_texture(fast_normalize(hit.obj->pos - hit.pos), scene->texture_moon, 8192, 4096, 0, 0);
		// if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
		// 	hit.color = sphere_checkerboard(fast_normalize(hit.obj->pos - hit.pos), hit.obj->color);
		
		// if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
		// 	hit.color = plane_texture(hit.normal, hit.pos, fast_normalize(((__local t_plane *)hit.obj)->u_axis), scene->texture_star, 1500, 1500);
		// if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
		// 	hit.color = plane_checkerboard(hit.normal, hit.pos);
		// if ((hit.obj->type == OBJ_CYLINDER) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
		// 	hit.color = cylinder_texture(hit.pos - hit.obj->pos, fast_normalize(hit.obj->dir), fast_normalize(((__local t_cylinder *)hit.obj)->u_axis), 10., scene->texture_star, 1500, 1500, ((__local t_cylinder *)hit.obj)->radius);
		// if ((hit.obj->type == OBJ_CONE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
		// 	hit.color = cone_texture(hit.pos - hit.obj->pos, fast_normalize(hit.obj->dir), fast_normalize(((__local t_cone *)hit.obj)->u_axis), 10., scene->texture_star, 1500, 1500);

		color = phong(scene, hit, ray);
		if (((hit.obj->refract != 0 && hit.obj->opacity < 1) || hit.obj->reflex > 0) && depth > 0)
			return (fresnel(scene, ray, hit, depth, color));

		// c'est quoi ce bloc commenté en dessous?
		/*else if (hit.obj->refract != 0 && hit.obj->opacity < 1)
		{
			bounce_color = refract(scene, ray, hit);
			if (bounce_color == 0)
				return (blend_med(bounce_color, blend_factor(color, ((hit.obj->opacity - 1) * -1))));
			bounce_color = blend_factor(bounce_color, ((hit.obj->opacity - 1) * -1));
		}
		else if (depth > 0 && hit.obj->reflex > 0)
			bounce_color = bounce(scene, ray, hit, depth);*/
		
		return (blend_add(color, bounce_color));
	}
	return (get_ambient(scene, BACKCOLOR));
}

static float3		get_ray_cam(__local t_scene *scene, const uint2 pix, const uint width, const uint height)
{
	float3			cam_ray = 0;
	float			ratio = ((float)width) / ((float)height);

	cam_ray.x = ((2 * ((pix.x + 0.5) / width)) - 1) * ratio * (tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.y = ((1 - (2 * ((pix.y + 0.5) / height))) * tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.z = 1;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(fast_normalize(cam_ray));
}

__kernel void		ray_trace(	__global	char		*output,

								__global	char		*global_mem_objects,
								__local		char		*mem_objects,
								__private	int			mem_size_objects,

								__private	float		u_time,

								__global	t_scene		*scene_data,
								__global	t_cam		*cameras_data,

								__local		t_scene		*scene,
								__local		t_cam		*cameras,

								__global	char		*global_mem_lights,
								__local		char		*mem_lights,
								__private	int			mem_size_lights,

								__global	int			*target,

								__global	unsigned int *texture_earth,
								__global	unsigned int *texture_moon,
								__global	unsigned int *texture_earth_cloud,
								__global	unsigned int *texture_star)
{

 	event_t			ev;
	int				id;
	uint2			pix;
	float3			prim_ray;
	unsigned int	final_color_o[32];
	unsigned int	final_color;
	uint3			rgb = 0;

	ev = async_work_group_copy((__local char *)mem_objects, (__global char *)global_mem_objects, mem_size_objects, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)mem_lights, (__global char *)global_mem_lights, mem_size_lights, 0);
	wait_group_events(1, &ev);

	int boo = get_global_id(0) + get_global_id(1);

	pix.x = get_global_id(0);// % scene->win_w;
	pix.y = get_global_id(1);// / scene->win_w;


	 // if (!pix.x && !pix.y) printf("%zu\n", sizeof(size_t));

	id = pix.x + (scene->win_w * pix.y);
	scene->cameras = cameras;
	scene->mem_lights = mem_lights;
	scene->u_time = u_time;
	scene->mem_obj = mem_objects;
	scene->mem_size_obj = mem_size_objects;
	scene->mem_size_lights = mem_size_lights;
<<<<<<< HEAD
	scene->texture_earth = texture_earth;
	scene->texture_earth_cloud = texture_earth_cloud;
	scene->texture_moon = texture_moon;
	scene->texture_star = texture_star;
=======
	
	scene->texture_earth = texture_earth;
	scene->texture_moon = texture_moon;
	scene->texture_earth_cloud = texture_earth_cloud;
	scene->texture_star = texture_star;

>>>>>>> 886fa93bab6e7b0402c114cfb6efc8887b956f46
	if (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target = -1;
	final_color = 0;
	if (scene->over_sampling > 1)
	{
		uint2 true_pix = pix;
		unsigned int i = 0;
		pix.x *= scene->over_sampling;
		pix.y *= scene->over_sampling;

		while (i < scene->over_sampling * 2)
		{
			pix.x += (i % 2);
			pix.y += !(i % 2);
			prim_ray = get_ray_cam(scene, pix, scene->win_w * scene->over_sampling, scene->win_h * scene->over_sampling);
			final_color_o[i] = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && true_pix.x == scene->mou_x && true_pix.y == scene->mou_y));
			rgb.x += (final_color_o[i] & 0x00FF0000);
			rgb.y += (final_color_o[i] & 0x0000FF00);
			rgb.z += (final_color_o[i] & 0x000000FF);
			i++;
		}
		final_color += ((rgb.x / (scene->over_sampling * 2)) & 0x00FF0000);
		final_color += ((rgb.y / (scene->over_sampling * 2)) & 0x0000FF00);
		final_color += ((rgb.z / (scene->over_sampling * 2)) & 0x000000FF);
	}
	else
	{
		prim_ray = get_ray_cam(scene, pix, scene->win_w, scene->win_h);
		final_color = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y));
	}

	if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);
	if (scene->flag & OPTION_INVERT)
		final_color = invert(final_color);
	if (scene->flag & OPTION_CARTOON)
		final_color = cartoonize(final_color);

	// ALPHA INSERT and RGB SWAP
	int4 swap;
	swap.w = 255;
	swap.x = (final_color & 0x00FF0000) >> 16;
	swap.y = (final_color & 0x0000FF00) >> 8;
	swap.z = (final_color & 0x000000FF);
	final_color = ((swap.w << 24) + (swap.z << 16) + (swap.y << 8) + swap.x);
	((__global unsigned int *)output)[id] = final_color;
}
