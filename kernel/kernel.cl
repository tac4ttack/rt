#ifdef cl_khr_fp64
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
#error "Double precision floating point not supported by OpenCL implementation."
#endif

#define BACKCOLOR 0x00999999

#define EPSILON 0.00000000000000000000005
#define EPSILONF 0.0000000005F
#define MAX_DIST 1000000000.0
#define SHADOW_BIAS 10000.0F

#define CAM scene->cameras
#define CONES scene->cones
#define CYLIND scene->cylinders
#define LIGHT scene->lights
#define PLANE scene->planes
#define SPHERE scene->spheres
#define ACTIVECAM scene->cameras[scene->active_cam]

#define OPTION_WAVE 				(1 << 1)
#define OPTION_SEPIA				(1 << 2)
#define OPTION_BW					(1 << 3)
#define OPTION_RUN					(1 << 4)
#define OPTION_INVERT				(1 << 7)
#define OPTION_CARTOON_FOUR			(1 << 8)
#define OPTION_STEREO				(1 << 9)
#define OPTION_CARTOON_TWO			(1 << 10)
#define OPTION_SKYBOX				(1 << 11)

#define OBJ_FLAG_WAVES				(1 << 1)
#define OBJ_FLAG_CHECKERED			(1 << 2)
#define OBJ_FLAG_DIFF_MAP			(1 << 3)
#define OBJ_FLAG_BUMP_MAP			(1 << 4)
#define OBJ_FLAG_PLANE_LIMIT		(1 << 5)
#define OBJ_FLAG_PLANE_LIMIT_FIX	(1 << 6)
#define OBJ_FLAG_CUT				(1 << 7)

# define OBJ_CAM					1
# define OBJ_LIGHT					2
# define OBJ_CONE					3
# define OBJ_CYLINDER				4
# define OBJ_PLANE					5
# define OBJ_SPHERE					6
# define OBJ_ELLIPSOID				7
# define OBJ_THOR					8

/*
** CAM AND LIGHT STRUCTS ///////////////////////////////////////////////////////
*/
typedef struct			s_cam
{
	unsigned int		id;
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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;
}						t_object;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float3				cut_min;
	float3				cut_max;

	double				lil_radius;
	double				big_radius;
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
	uint				mem_index;
	int					type;
	float				dist;
}						t_tor;
// typedef	struct			s_tor
// {
// 	int					activate;
// 	float3				pos;
// 	float3				prim;
// 	float3				normale;
// 	float				coef_ref;
// 	float				coef_tra;
// 	float				opacity;
// 	unsigned int		color;
// 	int					mem_index;
// 	int					type;
// 	float				fr;
// 	float				ft;
// }						t_tor;
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
	int					wall; // WIP
	int					lock; // WIP
}						t_hit;

typedef struct			s_ret
{
	int					wall;
	float				dist;
	float3				normal;
}						t_ret;

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
	unsigned int		__global *texture_skybox;
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
	hit.obj = 0;
	hit.wall = 0;
	hit.color = 0;
	hit.pos = 0.f;
	hit.mem_index = 0;
	hit.opacity = 0;
	hit.lock = 0;
	return (hit);
}

static unsigned int		skybox(const float3 dir, unsigned int __global *texture, int t_width, int t_height)
{
	unsigned int	color = 0;
	int2			uv = 0;

	uv.x = (int)floor((0.5 + (atan2(dir.z, dir.x) / (2 * M_PI))) * t_width);
	uv.y = (int)floor((0.5 - (asin(dir.y) / M_PI)) * t_height);
	if (uv.x < 0)
		uv.x = -uv.x;
	if (uv.y < 0)
		uv.y = -uv.y;
	if (uv.x >= t_width)
		uv.x %= (t_width - 1);
	if (uv.y >= t_height)
		uv.y %= (t_height - 1);
	color = texture[uv.x + uv.y * t_width];
	return (color);
}
////////////////////////////////////////////////////////////////////////////////


/*
** COLOR FUNCTIONS /////////////////////////////////////////////////////////////
*/
static unsigned int cartoonize_four(unsigned int col_r, unsigned int col_g, unsigned int col_b)
{
		if (col_r > 0 && col_r <= 50)
			col_r = 32;
		else if (col_r > 50 && col_r <= 100)
			col_r = 96;
		else if (col_r > 100 && col_r <= 200)
			col_r = 160;
		else if (col_r > 200 && col_r < 250)
			col_r = 224;
		else if (col_r >= 255)
			col_r = 255;

		if (col_g > 0 && col_g <= 50)
			col_g = 32;
		else if (col_g > 50 && col_g <= 100)
			col_g = 96;
		else if (col_g > 100 && col_g <= 200)
			col_g = 160;
		else if (col_g > 200 && col_g < 250)
			col_g = 224;
		else if (col_g >= 255)
			col_g = 255;

		if (col_b > 0 && col_b <= 50)
			col_b = 32;
		else if (col_b > 50 && col_b <= 100)
			col_b = 96;
		else if (col_b > 100 && col_b <= 200)
			col_b = 160;
		else if (col_b > 200 && col_b < 250)
			col_b = 224;
		else if (col_b >= 255)
			col_b = 255;

	return (((col_r << 16) + (col_g << 8) + col_b));
}

static unsigned int cartoonize_two(unsigned int col_r, unsigned int col_g, unsigned int col_b)
{
		if (col_r > 0 && col_r <= 128)
			col_r = 64;
		else if (col_r > 128 && col_r <= 255)
			col_r = 192;
		else if (col_r >= 255)
			col_r = 255;

		if (col_g > 0 && col_g <= 128)
			col_g = 64;
		else if (col_g > 128 && col_g <= 255)
			col_g = 192;
		else if (col_g >= 255)
			col_g = 255;

		if (col_b > 0 && col_r <= 128)
			col_b = 64;
		else if (col_b > 128 && col_b <= 255)
			col_b = 192;
		else if (col_b >= 255)
			col_b = 255;

	return (((col_r << 16) + (col_g << 8) + col_b));
}

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
	unsigned int r, g, b = 0;
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
	unsigned int r, g, b = 0;
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
	unsigned int r, g, b = 0;
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
	unsigned int r, g, b = 0;
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
	// maybe unstable
	unsigned int r, g, b = 0;

	r = (obj_color & 0x00FF0000) >> 16;
	g = (obj_color & 0x0000FF00) >> 8;
	b = (obj_color & 0x000000FF);
	r = (0.01f + r * scene->ambient.x > 255 ? 255 : 0.01f + r * scene->ambient.x);
	g = (0.01f + g * scene->ambient.y > 255 ? 255 : 0.01f + g * scene->ambient.y);
	b = (0.01f + b * scene->ambient.z > 255 ? 255 : 0.01f + b * scene->ambient.z);
	return ((r << 16) + (g << 8) + b);
}
////////////////////////////////////////////////////////////////////////////////



/*
** ROTATION AND MATRIX SHIT FUNCTIONS //////////////////////////////////////////
*/
static float3	rotat_zyx(const float3 vect, const float pitch, const float yaw, const float roll)
{
	float3		res = 0;
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
	float3		res = 0;
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
** LIMIT WITH A PLANE FUNCTIONS ////////////////////////////////////////////////
*/
static float	inter_plan_private(const t_plane *plane, const float3 ray, const float3 origin)
{
	float		t = 0;

	t = dot(fast_normalize(ray), plane->normal);
	if (fabs(t) < EPSILONF|| (plane->radius && t > plane->radius))
		return (0);
	t = (dot(plane->pos - origin, plane->normal)) / t;
	if (t < EPSILONF)
		return (0);
	return (t);
}

static t_ret	object_limited(t_object __local *object,
							const float res1, const float res2,
							const float3 ray, const float3 origin)
{
	t_ret		ret;
	t_plane		t;
	float		dist_plan = 0;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	t.pos = object->limit_pos;
	t.normal = object->limit_dir;
	t.radius = 0;
	dist_plan = inter_plan_private(&t, ray, origin);

	// IN OBJECT
	if (res1 < 0)
	{
		if (dot(t.normal, ray) > EPSILONF)
		{
			if (!dist_plan && res2 > EPSILONF)
				ret.dist = res2;
			else if (res2 < dist_plan)
				return (ret);
			else
			{
				ret.dist = dist_plan;
				ret.normal = -t.normal;
				ret.wall = 1;
			}
		}
		else
		{
			if (dist_plan > res2)
				ret.dist = res2;
			else if (dist_plan < MAX_DIST)
			{
				ret.dist = dist_plan;
				ret.normal = -t.normal;
				ret.wall = 1;
			}
		}
		return (ret);
	}

	if (dot(t.normal, ray) > EPSILONF)
	{
		if (res2 < dist_plan || dist_plan > MAX_DIST)
			return (ret);
		else if (res1 > dist_plan)
			ret.dist = res1;
		else if (dist_plan < MAX_DIST)
		{
			ret.dist = dist_plan;
			ret.normal = -t.normal;
			ret.wall = 1;
		}
	}
	else
	{
		if (dist_plan < res1)
			return (ret);
		ret.dist = res1;
	}
	return (ret);
}
////////////////////////////////////////////////////////////////////////////////

/*
** 2 LONELY VECTOR FUNCTIONS
*/
static float3	vector_get_rotate(const float3 *that, const __local float3 *rot)
{
	float3		n = 0;
	float		tmp = 0;

	n = *that;
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

static float3	vector_get_inverse(const float3 *that, const __local float3 *rot)
{
	float3		n = 0;
	float		tmp = 0;

	n = *that;
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
////////////////////////////////////////////////////////////////////////////////



/*
** ELLIPSOID FUNCTIONS
*/

static bool		solve_quadratic(const float a, const float b, const float c, float *inter0, float *inter1)
{
	float 		discr = 0;
	float 		tmp = 0;
	float 		q = 0;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (false);
	else if (discr < EPSILONF)
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
	float3 pos = 0;
	float3 res = 0;

	pos = hit->pos - ellipsoid->pos;
	pos = vector_get_rotate(&pos, &ellipsoid->dir);

	res.x = (pos.x) / (ellipsoid->axis_size.x * ellipsoid->axis_size.x);
	res.y = (pos.y) / (ellipsoid->axis_size.y * ellipsoid->axis_size.y);
	res.z = (pos.z) / (ellipsoid->axis_size.z * ellipsoid->axis_size.z);
	res = vector_get_inverse(&res, &ellipsoid->dir);
	return (res);
}

static t_ret	inter_ellipsoid(const __local t_ellipsoid *ellipsoid, float3 ray, float3 origin)
{
	float3		abc = 0;
	float		res1, res2 = 0;
	float3		pos = 0;
	float3		save_ray = 0;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	save_ray = ray;

	pos = origin - ellipsoid->pos;
	pos = vector_get_rotate(&pos, &ellipsoid->dir);
	ray = vector_get_rotate(&ray, &ellipsoid->dir);
	ray /= ellipsoid->axis_size;
	pos /= ellipsoid->axis_size;

	abc.x = (ray.x * ray.x + \
	 		ray.y * ray.y + \
	 		ray.z * ray.z);
	abc.y = (2 * pos.x * ray.x + \
		 	2 * pos.y * ray.y + \
		 	2 * pos.z * ray.z);
	abc.z = (pos.x * pos.x + \
		 	pos.y * pos.y + \
		 	pos.z * pos.z) - \
			(ellipsoid->radius * ellipsoid->radius);

	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	if (ellipsoid->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object __local *)ellipsoid, res1, res2, save_ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}
////////////////////////////////////////////////////////////////////////////////



/*
** PLANES FUNCTIONS ////////////////////////////////////////////////////////////
*/
static unsigned int		plane_checkerboard(const float3 normale, const float3 pos, const unsigned int color, const float2 check_size)
{
	float3			u_axis = 0;
	float3			v_axis = 0;
	int2			uv = 0;

	u_axis.x = normale.y;
	u_axis.y = normale.z;
	u_axis.z = -normale.x;
	v_axis = cross(u_axis, normale);
	uv.x = convert_int(floor(dot(pos, u_axis) / check_size.x));
	uv.y = convert_int(floor(dot(pos, v_axis) / check_size.y));
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

static unsigned int		plane_texture(float3 normale, float3 pos, float3 u_axis, float2 ratio, float2 offset, unsigned int __global *texture, int width, int height)
{
	float3			v_axis = 0;
	int2			uv = 0;

	v_axis = cross(u_axis, normale);
	uv.x = convert_int(floor(dot(pos, u_axis) * ratio.x + offset.x));
	uv.y = convert_int(floor(dot(pos, v_axis) * ratio.y + offset.y));
	// if (uv.x < 0)
	// {
	// 	uv.x %= width;
	// 	uv.x = (uv.x - width) * -1;
	// }
	// uv.x %= width;
	// if (uv.y < 0)
	// 	uv.y %= height;
	// else
	// {
	// 	uv.y %= height;
	// 	uv.y = (uv.y - height) * -1;
	// }
	uv.x %= width - 1;
	uv.y %= height - 1;
	if (uv.x < 0)
		uv.x = (uv.x + width - 1);
	if (uv.y < 0)
		uv.y = (uv.y + height - 1);
	// else
	// 	uv.y = -uv.y;
	//if (uv.x < 0 || uv.y < 0)
	//printf("agrougrou");
	return (texture[uv.y + uv.x * width]);
}

static t_ret	inter_plan(const __local t_plane *plane, const float3 ray, const float3 origin)
{
	float		t = 0;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	t = dot(fast_normalize(ray), plane->normal);
	if (fabs(t) < EPSILONF || (plane->radius && t > plane->radius))
		return (ret);
	t = (dot(plane->pos - origin, plane->normal)) / t;
	if (t < EPSILONF)
		return (ret);
	if (plane->radius)
	{
		float3 p = origin + ray * t;
		float3 v = p - plane->pos;
		float d2 = dot(v, v);
		if (sqrt(d2) > plane->radius)
			return (ret);
	}
	if (plane->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object __local *)plane, t, t, ray, origin));
	ret.dist = t;
	return (ret);
}
////////////////////////////////////////////////////////////////////////////////




/*
** CYLINDER FUNCTIONS //////////////////////////////////////////////////////////
*/
static unsigned int		cylinder_texture(float3 pos, __local t_cylinder *cyl, unsigned int __global *texture, int t_width, int t_height)
{
	unsigned int	color = 0;
	float3			v_axis = 0;
	float			npos = 0;
	float			vpos = 0;
	int2			uv = 0;

	v_axis = cross(cyl->u_axis, cyl->dir);
	npos = fast_length(dot(pos, cyl->dir) * cyl->dir);
	while (npos > 10)
		npos -= 10;
	if (dot(pos, cyl->dir) < 0)
		npos = (npos - 10) * -1;
	uv.y = convert_int(floor((npos / 10) * t_height * cyl->diff_ratio.y + cyl->diff_offset.y));
	npos = dot(pos, cyl->u_axis);
	vpos = dot(pos, v_axis);
	uv.x = convert_int(floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * t_width * cyl->diff_ratio.x + cyl->diff_offset.x));
	uv.x %= t_width - 1;
	uv.y %= t_height - 1;
	if (uv.x < 0)
		uv.x = uv.x + t_width - 1;
	if (uv.y < 0)
		uv.y = -uv.y;
	else
		uv.y = (uv.y - t_height - 1) * -1;
	uv.x %= t_width - 1;
	uv.y %= t_height - 1;
	color = (unsigned int)texture[uv.x + (uv.y * t_width)];
	return (color);
}

static float3	get_cylinder_abc(const float radius, const float3 dir, const float3 ray, const float3 origin)
{
	float3		abc = 0;

	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

static float3	get_cylinder_normal(const __local t_cylinder *cylinder, t_hit hit)
{
	float3		res = 0;
	float3		v = 0;
	float3		project = 0;
	float		doty = 0;

	v = hit.pos - cylinder->pos;
	doty = dot(v, cylinder->dir);
	project = doty * cylinder->dir;
	res = v - project;
	return (fast_normalize(res));
}

static t_ret	inter_cylinder(const __local t_cylinder *cylinder, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float3		pos = 0;
	float		res1 = 0;
	float		res2 = 0;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	pos = origin - cylinder->pos;
	abc = get_cylinder_abc(cylinder->radius, cylinder->dir, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	if (cylinder->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object __local *)cylinder, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}
////////////////////////////////////////////////////////////////////////////////



/*
** TORUS FUNCTIONS /////////////////////////////////////////////////////////////
*/
static double3	thor_get_rotate(const double3 *that, const __local float3 *rot)
{
	double3		n = 0;
	float		tmp = 0;

	n = *that;
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

static double	ft_ret(double *tab)
{
	double		ret = -1.0;
	int			i = 0;
	
	while(i < 4)
	{
		if(tab[i] > EPSILON && ret == -1)
			ret = tab[i];
			if (tab[i] < ret && tab[i] > EPSILON )
			ret = tab[i];
		i++;
	}
	if (ret == -1.0)
		ret = 0.0;
	return (ret);
}

static double3	ft_solve_3(double a, double b, double c, double d)
{
	double		a1 = 0;
	double		a2 = 0;
	double		a3 = 0;
	double3		Result = 0;
	double		theta = 0;
	double		sqrtQ = 0;
	double		e = 0;
	double		Q = 0;
	double		R = 0;
	double		Qcubed = 0;

	a1 = c / d;
	a2 = b / d;	
	a3 = a / d;

	Q = (a1 * a1 - 3.0f * a2) / 9.0f;
	R = (2.0f * a1 * a1 * a1 - 9.0f * a1 * a2 + 27.0f * a3) / 54.0f;
	Qcubed = Q * Q * Q;
	d = Qcubed - R * R;
	if ( d >= EPSILON )
	{
		if ( Q < EPSILON )
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
		e = pow(sqrt((double)-d) + fabs((double)R), (double)1.0f/ (double)3.0f);
		if ( R > EPSILON )
			e = -e;
		Result.x = Result.y = Result.z = (e + Q / e) - a1 / 3.0f;
	}
	return (Result);
}

static double	ft_solve_4(double t[5])
{
	double		Result[4] = {0};
	double3		Roots = 0;
	double		Rsquare = 0;
	double		Rrec = 0;
	double		D = 0;
	double		E = 0;
	double3		b = 0;
	double		a0 = 0;
	double		a1 = 0;
	double		a2 = 0;
	double		a3 = 0;
	double		R = 0;
	double		y = 0;

	a0 = t[0] / t[4];
	a1 = t[1] / t[4];
	a2 = t[2] / t[4];
	a3 = t[3] / t[4];

	b.x = 4.0f * a2 * a0 - a1 * a1 - a3 * a3 * a0;
	b.y = a1 * a3 - 4.0f * a0;
	b.z = -a2;
	Roots = ft_solve_3(b.x, b.y, b.z, 1.0f);
	y = fmax(Roots.x, fmax(Roots.y, Roots.z));
	R = 0.25f * a3 * a3 - a2 + y;

	if (R < EPSILON)
		return (0.0f);
	R = sqrt(R);
	if ( R == EPSILON )
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

static t_ret		inter_thor(const __local t_thor *thor, const float3 ray, const float3 origin)
{
	t_ret			ret;
	ret.dist = 0;
	ret.normal = 0;
	ret.wall = 0;

	double 		big_radius = thor->big_radius * thor->big_radius;
	double		lil_radius = thor->lil_radius * thor->lil_radius;

	double3		d_ray;
	d_ray.x = (double)ray.x;
	d_ray.y = (double)ray.y;
	d_ray.z = (double)ray.z;
	d_ray = thor_get_rotate(&d_ray, &thor->dir);

	double3		d_dir;
	d_dir.x = (double)origin.x - (double)thor->pos.x;
	d_dir.y = (double)origin.y - (double)thor->pos.y;
	d_dir.z = (double)origin.z - (double)thor->pos.z;
	d_dir = thor_get_rotate(&d_dir, &thor->dir);

	double3		k;
	k.x = (d_ray.x * d_ray.x) + (d_ray.y * d_ray.y) + (d_ray.z * d_ray.z);
	k.y = 4.0f * big_radius;
	k.z = (d_dir.x) * d_ray.x \
		+ (d_dir.y) * d_ray.y \
		+ (d_dir.z) * d_ray.z;

	double		e;
	e =	(d_dir.x) * (d_dir.x) + \
		(d_dir.y) * (d_dir.y) + \
		(d_dir.z) * (d_dir.z) - \
		big_radius - lil_radius;

	double		c[5];
	c[0] = e * e - k.y * (lil_radius - (d_dir.y) * (d_dir.y));
	c[1] = 4.0f * k.z * e + 2.0f * k.y * (d_dir.y) * d_ray.y;
	c[2] = 2.0f * k.x * e + 4.0f * k.z * k.z + k.y * d_ray.y * d_ray.y;
	c[3] = 4.0f * k.x * k.z;
	c[4] = k.x * k.x;

	ret.dist = ft_solve_4(c);
	return (ret);
}

static float3 get_thor_normal(const __local t_thor *thor, const float3 hitpos)
{
	float3	res = 0;
	float	c = 0;

	float	R = convert_float((thor->lil_radius * thor->lil_radius));
	float	r = convert_float((thor->big_radius * thor->big_radius));

	float3 pos = hitpos - thor->pos;
	pos = vector_get_rotate(&pos, &thor->dir);

	c = ((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z) - r - R);

	res.x = 4.0f * c * pos.x;
	res.y = 4.0f * pos.y * (c + 2 * r);
	res.z = 4.0f * c * pos.z;

	res = vector_get_inverse(&res, &thor->dir);
	return (res);
}
////////////////////////////////////////////////////////////////////////////////



/*
** SPHERES FUNCTIONS ///////////////////////////////////////////////////////////
*/
static t_ret			sphere_cut(const __local t_sphere *sphere, float2 tmp, const float3 ray, const float3 origin)
{
	t_ret		ret;
	float 		pt_y;
	float 		pt_ys;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;

	sphere->cut_max.x = sphere->radius;
	sphere->cut_min.x = sphere->radius;
	sphere->cut_max.y = sphere->radius;
	sphere->cut_min.y = sphere->radius;
	sphere->cut_max.z = sphere->radius;
	sphere->cut_min.z = sphere->radius;

	pt_y = origin.y + ray.y * tmp.x;
	pt_ys = origin.y + ray.y * tmp.y;
	if (pt_y <= sphere->pos.y + 2 )
	{
		ret.dist = tmp.x;
		return (ret);
	}
	else if (pt_ys <= sphere->pos.y +2)
	{
		ret.dist = tmp.y;
		return (ret);
	}
	ret.dist = 0;
	return (ret);
}

static unsigned int		sphere_checkerboard(const float3 dir, const unsigned int color, const float2 check_size)
{
	int2	uv = 0;

	uv.x = convert_int(floor((0.5 + (atan2(dir.z, dir.x) / (2 * 3.1415))) * check_size.x));
	uv.y = convert_int(floor((0.5 - (asin(dir.y) / 3.1415)) * check_size.y));
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

static unsigned int		sphere_texture(float3 pos, unsigned int __global *texture, int t_width, int t_height, float2 ratio, float2 offset)
{
	unsigned int	color = 0;
	int2			uv = 0;
	int2			size = 0;

	size.x = convert_int(floor(t_width * ratio.x));
	size.y = convert_int(floor(t_height * ratio.y));
	uv.x = convert_int(floor((0.5 + (atan2(pos.z, pos.x) / (2 * M_PI))) * size.x + offset.x));
	uv.y = convert_int(floor((0.5 - (asin(pos.y) / M_PI)) * size.y + offset.y));
	if (uv.x < 0)
	{
		uv.x %= (t_width - 1);
		uv.x = (uv.x + t_width - 1);
	}
	else
		uv.x %= (t_width - 1);
	if (uv.y < 0)
		uv.y %= (t_height - 1);
	else
	{
		uv.y %= (t_height - 1);
		uv.y = (uv.y - (t_height - 1)) * -1;
	}
	color = texture[uv.x + uv.y * t_width];
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


// ACTUAL ONE
static t_ret	inter_sphere(const __local t_sphere *sphere, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
	
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	if (sphere->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object __local *)sphere, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);

}

// ANROCHE ONE
// static t_ret	inter_sphere(const __local t_sphere *sphere, const float3 ray, const float3 origin)
// {
// 	float3		abc = 0;
// 	float		res1 = 0;
// 	float		res2 = 0;
// 	float3		pos = 0;
	
// 	float       d = 0;
// 	float2      tmp = 0;

// 	pos = origin - sphere->pos;
// 	abc = get_sphere_abc(sphere->radius, ray, pos);
// 	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
// 	// if (d < 0)
		
// 	if (d == 0)
// 	{
// 		tmp.x =  ((-abc[1]) / (2 * abc[0]));
// 		tmp.y =  ((-abc[1]) / (2 * abc[0]));
// 	}
// 	else
// 	{
// 		res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
// 		res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
// 		if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
// 		{
// 			tmp.x =(res1);
// 			tmp.y =(res2);
// 		}
// 		else
// 		{
// 			tmp.x =  (res2);
// 			tmp.y = (res1);
// 		}
// 	}
	
// 	return (sphere_cut(sphere, tmp, ray, origin));
// }
////////////////////////////////////////////////////////////////////////////////



/*
** CONES FUNCTIONS /////////////////////////////////////////////////////////////
*/
static unsigned int		cone_texture(float3 pos, float3 dir, float3 u_axis, unsigned int __global *texture, int t_width, int t_height, float2 ratio, float2 offset)
{
	unsigned int	color = 0;
	float3			v_axis = 0;
	float			npos = 0;
	float			vpos = 0;
	float			radius = 0;
	int2			uv = 0;

	v_axis = cross(u_axis, dir);
	npos = dot(pos, dir);
	radius = fast_length(pos - (npos * dir));
	while (npos > 10)
		npos -= 10;
	while (npos < 0)
		npos += 10;
	uv.y = convert_int(floor((fast_length(npos * dir) / 10) * ratio.y * (t_height - 1) + offset.y));
	npos = dot(pos, u_axis);
	vpos = dot(pos, v_axis);
	uv.x = convert_int(floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * ratio.x * (t_width - 1) + offset.x));
	uv.x %= t_width - 1;
	uv.y %= t_height - 1;
	if (uv.x < 0)
		uv.x = uv.x + t_width - 1;
	if (uv.y < 0)
		uv.y = -uv.y;
	else
		uv.y = (uv.y - t_height - 1) * -1;
	uv.x %= t_width - 1;
	uv.y %= t_height - 1;
	 color = (unsigned int)texture[uv.x + (uv.y * t_width)];
	return (color);
}

static float3	get_cone_normal(const __local t_cone *cone, const t_hit hit)
{
	float3		res = 0;
	float3		v = 0;
	float3		project = 0;
	float		doty = 0;
	float		m = 0;

	v = hit.pos - cone->pos;
	doty = dot(v, cone->dir);
	project = doty * cone->dir;
	m = fast_length(project);
	res = v - project;

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

static t_ret	inter_cone(const __local t_cone *cone, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	pos = origin - cone->pos;
	abc = get_cone_abc(cone, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	// BUGGY NEED TO BE FIXED!!!!!!!!
	if (cone->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object __local *)cone, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}
////////////////////////////////////////////////////////////////////////////////



static t_hit			ray_hit(const __local t_scene *scene, const float3 origin, const float3 ray, float lightdist)
{
	t_hit				hit;
	t_object __local	*obj;
	uint				mem_index_obj = 0;
	t_ret				ret;

	hit = hit_init();
	ret.dist = 0;
	ret.wall = 0;
	ret.normal = 0;
	obj = 0;
	if (lightdist == 0)
		hit.opacity = 1;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = scene->mem_obj + mem_index_obj;
		if (obj->type == OBJ_SPHERE)
		 	ret = inter_sphere((__local struct s_sphere *)obj, ray, origin);
		else if (obj->type == OBJ_CYLINDER)
		 	ret = inter_cylinder((__local struct s_cylinder *)obj, ray, origin);
		else if (obj->type == OBJ_PLANE)
		 	ret = inter_plan((__local struct s_plane *)obj, ray, origin);
		else if (obj->type == OBJ_CONE)
		 	ret = inter_cone((__local struct s_cone *)obj, ray, origin);
		else if (obj->type == OBJ_ELLIPSOID)
		   	ret = inter_ellipsoid((__local struct s_ellipsoid *)obj, ray, origin);
		else if (obj->type == OBJ_THOR)
			ret = inter_thor((__local struct s_thor *)obj, ray, origin);
		if (lightdist > 0 && ret.dist < lightdist && ret.dist > EPSILONF)
			hit.opacity += obj->opacity;
		if ((ret.dist < hit.dist || hit.dist == 0) && ret.dist > EPSILONF)
		{
			hit.dist = ret.dist;
			hit.normal = ret.normal;
			hit.wall = ret.wall;
			hit.obj = obj;
			hit.lock = 1;
			hit.mem_index = mem_index_obj;
		}
		mem_index_obj += obj->size;
	}
	return (hit);
}

static float3			get_hit_normal(const __local t_scene *scene, float3 ray, t_hit hit)
{
	float3				res = 0;
	float3				save = 0;
	t_object __local	*object;

	object = hit.obj;
	if (hit.wall)
		res = hit.normal;
	else
	{
		if (hit.obj->type == OBJ_SPHERE)
		 	res = hit.pos - hit.obj->pos;
		else if (hit.obj->type == OBJ_CYLINDER)
			res = get_cylinder_normal((__local t_cylinder *)hit.obj, hit);
		else if (hit.obj->type == OBJ_CONE)
			res = get_cone_normal((__local t_cone *)hit.obj, hit);
		else if (hit.obj->type == OBJ_ELLIPSOID)
			res = get_ellipsoid_normal((__local t_ellipsoid *)hit.obj, &hit);
		else if (hit.obj->type == OBJ_THOR)
			res = get_thor_normal((__local t_thor *)hit.obj, hit.pos);
		else if (hit.obj->type == OBJ_PLANE)
		{
			if (dot(hit.obj->dir, -ray) < 0)
				res = -hit.obj->dir;
			else
				res = hit.obj->dir;
		}
	}
	save = res;
	if (object->flags & OBJ_FLAG_WAVES)
	{
		if (object->type == OBJ_PLANE)
			save.y = res.y + object->waves_p1.x * sin((hit.pos.x + scene->u_time));
		else
		{
			save.x = res.x + object->waves_p1.x * sin(res.y * object->waves_p2.x + scene->u_time);
			save.z = res.z + object->waves_p1.y * sin(res.x * object->waves_p2.y + scene->u_time);
			save.y = res.y + object->waves_p1.z * sin(res.x * object->waves_p2.z + scene->u_time);
		}
	}

	return (fast_normalize(save));
}

static unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	t_object __local		*obj;
	t_light __local			*light;
	t_light_ray				light_ray;
	t_hit					light_hit;
	uint					mem_index_lights = 0;
	unsigned int			res_color = 0;
	float					tmp = 0;
	float3					reflect = 0;
	float3 					diffuse = 0;
	float 					brightness = 0;
	unsigned int 		 	hue = 0;
	unsigned int 			hue_light = 0;
	unsigned int 		 	col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g = 0;
	float 			 		pow_of_spec = 0;
	int 					light_color = 0;
	float3 			 		speculos = 0;

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

	while (mem_index_lights < scene->mem_size_lights)
	{
		tmp = 0;
		light = scene->mem_lights + mem_index_lights;
		light_ray.dir = light->pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir, light_ray.dist);
		if (!(light_hit.dist < light_ray.dist && light_hit.dist > EPSILONF) || (light_hit.opacity < 1 && scene->depth != 0))
		{
			// diffuse part
			tmp = (dot(hit.normal, light_ray.dir));
			if (tmp > EPSILONF)
			{
				brightness = (float __private)light->brightness;
				diffuse = (float3 __private)obj->diff;
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

				// col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				// col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				// col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				col_r += (((l_r * brightness) * obj_r) * tmp * diffuse.x) / 255.0;
				col_g += (((l_g * brightness) * obj_g) * tmp * diffuse.y) / 255.0;
				col_b += (((l_b * brightness) * obj_b) * tmp * diffuse.z) / 255.0;

				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
			
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}

			// specular part
			reflect = fast_normalize(((convert_float(2.0 * dot(hit.normal, light_ray.dir)) * hit.normal)) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > EPSILONF)
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
			// if (light_hit.opacity != 0)
			// {
			// 	light_hit.opacity = 1 - light_hit.opacity;
			// 	if (light_hit.opacity > scene->ambient.x)
			// 		col_r = (0.01 + col_r * light_hit.opacity > 255 ? 255 : 0.01 + col_r * light_hit.opacity);
			// 	else
			// 		col_r = (0.01 + col_r * scene->ambient.x > 255 ? 255 : 0.01 + col_r * scene->ambient.x);
			// 	if (light_hit.opacity > scene->ambient.y)
			// 		col_g = (0.01 + col_g * light_hit.opacity > 255 ? 255 : 0.01 + col_g * light_hit.opacity);
			// 	else
			// 		col_g = (0.01 + col_g * scene->ambient.y > 255 ? 255 : 0.01 + col_g * scene->ambient.y);
			// 	if (light_hit.opacity > scene->ambient.z)
			// 		col_b = (0.01 + col_b * light_hit.opacity > 255 ? 255 : 0.01 + col_b * light_hit.opacity);					
			// 	else
			// 		col_b = (0.01 + col_b * scene->ambient.z > 255 ? 255 : 0.01 + col_b * scene->ambient.z);
			// 	res_color = ((col_r << 16) + (col_g << 8) + col_b);
			// }
			

			if (scene->flag & OPTION_CARTOON_FOUR)
			 	res_color = cartoonize_four(col_r, col_g, col_b);
			else if (scene->flag & OPTION_CARTOON_TWO)
			 	res_color = cartoonize_two(col_r, col_g, col_b);
		}
		mem_index_lights += light->size;
	}
	return (res_color);
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

static float3		bounce_ray(const __local t_scene *scene, const float3 ray, float3 normal)
{
	float3			reflex = 0;

	// PREMIÈRE LOI DE SNELL-DESCARTES ///////////////////////////////////////////////////////////
	reflex = fast_normalize(ray - (2 * convert_float(dot(normal, ray)) * normal));
	//////////////////////////////////////////////////////////////////////////////////////////////
	return (reflex);
}
/*
static float		reflect_ratio(float n1, float n2, float cos1, float sint)
{
	float			fr1 = 0;
	float			fr2 = 0;
	float			cos2 = 0;
	
	cos2 = sqrt(1 - sint * sint);
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
*/
static t_tor		tor_push(const float3 ray, const float3 normale, const float3 pos, \
							const float coef_ref, const float coef_tra, const float opacity, \
							const unsigned int color, const uint mem_index, const int type)
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
	tor.type = type;
	return (tor);
}
/*
static int			tor_height(int i)
{
	int				h = 0;

	while ((i = (i - 1) / 2) >= 0)
		h++;
	return (h);
}

static unsigned int	tor_final_color(t_tor *tor)
{
	int				i = 31;
	unsigned int	color = 0;

	while (i > 0)
	{
		if (tor[i].activate == 0 || (tor[(2 * i) + 2].activate == 0 && tor[(2 * i) + 1].activate == 0))
			;
		else
		{
			// color = blend_add(tor[(2 * i) + 2].color, tor[(2 * i) + 1].color);
			color = blend_add(blend_factor(tor[(2 * i) + 2].color, tor[(2 * i) + 2].fr), blend_factor(tor[(2 * i) + 1].color, tor[(2 * i) + 1].ft));
			// if (tor[i].coef_tra != 0 && tor[(i * 2) + 1].mem_index == tor[i].mem_index)
			// 	tor[i].color = color;
			if (tor[i].coef_tra != 0 && color != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
			else if (tor[i].coef_ref != 0 && color != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
			// else
			// 	tor[i].color = blend_add(color, tor[i].color);
		}
		i = i - 1;
		while (i > 0 && tor[i].activate == 0)
			i = i - 1;
	}
	// color = blend_add(tor[(2 * i) + 2].color, tor[(2 * i) + 1].color);
	color = blend_add(blend_factor(tor[(2 * i) + 2].color, tor[(2 * i) + 2].fr), blend_factor(tor[(2 * i) + 1].color, tor[(2 * i) + 1].ft));
	if (tor[i].coef_tra != 0 && color != 0)
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
	//t_tor			tor[64];
	t_tor			tor[63];
	int				i = 0;
	unsigned int	tor_depth = 0;

	tor_depth = convert_uint(pow(2.f, convert_float(depth))) - 1;
	i = 0;
	// while (i < 64)
	while (i < 63)
	{
		tor[i].activate = 0;
		tor[i].prim = 0;
		tor[i].normale = 0;
		tor[i].pos = 0;
		tor[i].coef_ref = 0;
		tor[i].coef_tra = 0;
		tor[i].color = 0;
		tor[i].opacity = 0;
		tor[i].mem_index = 0;
		tor[i].type = 0;
		tor[i].fr = 0;
		tor[i].ft = 0;
		i++;
	}
	i = 0;
	tor[i] = tor_push(ray, old_hit.normal, old_hit.pos, old_hit.obj->reflex, \
						old_hit.obj->refract, old_hit.obj->opacity, color, \
						old_hit.mem_index, old_hit.obj->type, 0, 0);
	while (i < 31 && i < tor_depth)
	{
		if (tor[i].coef_tra != 0)
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
			// if (fr > 0.99)
			// 	fr = 1;
			// if (fr < 0.01)
			// 	fr = 0;
			ft = 1 - fr;
			if (fr < 1)
			{
				if (tor[i].type != OBJ_PLANE)
					refract = refract_ray(scene, tor[i].prim, tor[i].normale, tor[i].coef_tra);
				else
					refract = tor[i].prim;
				if (cos1 < 0)
					new_hit = ray_hit(scene, tor[i].pos + (0.0001f * (2.f * -tor[i].normale)), refract, 0);
				else
					new_hit = ray_hit(scene, tor[i].pos, refract, 0);
				if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
				{
					if (cos1 < 0)
					 	new_hit.pos = (new_hit.dist * refract) + tor[i].pos + (0.0001f * (2.f * -tor[i].normale));
					else
						new_hit.pos = (new_hit.dist * refract) + tor[i].pos;
					new_hit.normal = get_hit_normal(scene, refract, new_hit);
					new_hit.pos = new_hit.pos + (new_hit.dist / 10000.f * new_hit.normal);


					// if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						// new_hit.color = sphere_texture(fast_normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, ((__local t_sphere *)new_hit.obj)->diff_ratio, ((__local t_sphere *)new_hit.obj)->diff_offset);
					if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					 	new_hit.color = sphere_checkerboard(fast_normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

					// else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						// new_hit.color = plane_texture(new_hit.normal, new_hit.pos, ((__local t_plane *)new_hit.obj)->u_axis, ((__local t_plane *)new_hit.obj)->diff_ratio, ((__local t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
					else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					 	new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

					// else if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					// 	new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, (__local t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

					// else if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					// 	new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, ((__local t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((__local t_cone *)new_hit.obj)->diff_ratio, ((__local t_cone *)new_hit.obj)->diff_offset);
					else
						new_hit.color = new_hit.obj->color;
	
					ncolor = phong(scene, new_hit, refract);
					if (new_hit.mem_index == tor[i].mem_index)
						ncolor = 0;
				}
				else
				{
					if (scene->flag & OPTION_SKYBOX)
						ncolor = skybox(refract, scene->texture_skybox, 4096, 2048);
					else
						ncolor = get_ambient(scene, BACKCOLOR);
				}
				tor[(i * 2) + 1] = tor_push(refract, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, old_hit.obj->type, 0, ft);
			}
		}
		else if (tor[i].coef_ref != 0)
			fr = 1;
		else
			fr = 0;
		if (fr > 0)
		{
			cos1 = dot(tor[i].normale, tor[i].prim);
			if (cos1 >= 0)
				bounce = bounce_ray(scene, tor[i].prim, -tor[i].normale);
			else
				bounce = bounce_ray(scene, tor[i].prim, tor[i].normale);
			if (cos1 >= 0)
				new_hit = ray_hit(scene, tor[i].pos + ((tor[i].dist / 1000.f) * (2.f * -tor[i].normale)), bounce, 0);
			else
				new_hit = ray_hit(scene, tor[i].pos, bounce, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				if (cos1 >= 0)
					new_hit.pos = (new_hit.dist * bounce) + tor[i].pos + ((tor[i].dist / 1000.f) * (2.f * -tor[i].normale));
				else
					new_hit.pos = (new_hit.dist * bounce) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, bounce, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000.f * new_hit.normal);

				// if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
				// 	new_hit.color = sphere_texture(fast_normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, ((__local t_sphere *)new_hit.obj)->diff_ratio, ((__local t_sphere *)new_hit.obj)->diff_offset);
				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = sphere_checkerboard(fast_normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

				// else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
				// 	new_hit.color = plane_texture(new_hit.normal, new_hit.pos, ((__local t_plane *)new_hit.obj)->u_axis, ((__local t_plane *)new_hit.obj)->diff_ratio, ((__local t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
				else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

				// else if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
				// 	new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, (__local t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

				// else if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
				// 	new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, ((__local t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((__local t_cone *)new_hit.obj)->diff_ratio, ((__local t_cone *)new_hit.obj)->diff_offset);

				else
					new_hit.color = new_hit.obj->color;

				ncolor = phong(scene, new_hit, bounce);
				if (new_hit.mem_index == tor[i].mem_index)
					ncolor = 0;
			}
			else
			{
				if (scene->flag & OPTION_SKYBOX)
					ncolor = skybox(bounce, scene->texture_skybox, 4096, 2048);
				else
					ncolor = get_ambient(scene, BACKCOLOR);
			}
			tor[(2 * i) + 2] = tor_push(bounce, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, old_hit.obj->type, fr, 0);
		}
		i = i + 1;
		while (i < 31 && tor[i].activate == 0)
			i = i + 1;
	}
	return (tor_final_color(tor));
}*/

static unsigned int	rip_tor_final_color(t_tor *tor)
{
	int				i = 8;

	while (i >= 0)
	{
		if (tor[i].activate == 1 && tor[i + 1].activate == 1)
		{
			if (tor[i].coef_tra != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(tor[i + 1].color, 1 - tor[i].opacity));
			else if (tor[i].coef_ref != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(tor[i + 1].color, tor[i].coef_ref));
		}
		i = i - 1;
	}
	return (tor[0].color);
}

static unsigned int	rip_fresnel(const __local t_scene *scene, float3 ray, t_hit old_hit, int depth, unsigned int color)
{
	t_tor			tor[10];
	int				i = 0;
	float			cos1;
	float3			new_ray;
	t_hit			new_hit;
	unsigned int	ncolor;

	new_hit = hit_init();
	while (i < 10)
	{
		tor[i].activate = 0;
		tor[i].prim = 0;
		tor[i].normale = 0;
		tor[i].pos = 0;
		tor[i].coef_ref = 0;
		tor[i].coef_tra = 0;
		tor[i].color = 0;
		tor[i].opacity = 0;
		tor[i].mem_index = 0;
		tor[i].type = 0;
		i++;
	}
	i = 0;
	tor[i] = tor_push(ray, old_hit.normal, old_hit.pos, old_hit.obj->reflex, \
						old_hit.obj->refract, old_hit.obj->opacity, color, \
						old_hit.mem_index, old_hit.obj->type);
	while (i < 9 && tor[i].activate == 1 && i < depth * 3)
	{
		if (tor[i].opacity != 1 && tor[i].coef_tra != 0)
		{
			cos1 = dot(tor[i].normale, tor[i].prim);
			if (tor[i].type != OBJ_PLANE)
				new_ray = refract_ray(scene, tor[i].prim, tor[i].normale, tor[i].coef_tra);
			else
				new_ray = tor[i].prim;
			if (cos1 < 0)
				new_hit = ray_hit(scene, tor[i].pos + (0.0001f * (2.f * -tor[i].normale)), new_ray, 0);
			else
				new_hit = ray_hit(scene, tor[i].pos, new_ray, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				if (cos1 < 0)
					new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos + (0.0001f * (2.f * -tor[i].normale));
				else
					new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, new_ray, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000.f * new_hit.normal);
				new_hit.color = new_hit.obj->color;
			
				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						new_hit.color = sphere_texture(fast_normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, ((__local t_sphere *)new_hit.obj)->diff_ratio, ((__local t_sphere *)new_hit.obj)->diff_offset);
				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
				 	new_hit.color = sphere_checkerboard(fast_normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);
				
				if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = plane_texture(new_hit.normal, new_hit.pos, ((__local t_plane *)new_hit.obj)->u_axis, ((__local t_plane *)new_hit.obj)->diff_ratio, ((__local t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);		
				if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
				 	new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);
				
				if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, (__local t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);
				
				if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, ((__local t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((__local t_cone *)new_hit.obj)->diff_ratio, ((__local t_cone *)new_hit.obj)->diff_offset);
	
				ncolor = phong(scene, new_hit, new_ray);
				tor[i + 1] = tor_push(new_ray, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, old_hit.obj->type);
			}
			// else
			// {
			// 	ncolor = (scene->flag & OPTION_SKYBOX) ? skybox(new_ray, scene->texture_skybox, 4096, 2048) : get_ambient(scene, BACKCOLOR);
			// 	tor[i + 1] = tor_push(new_ray, 0, 0, 0, 0, 1, ncolor, 0, 0);
			// }
		}
		else if (tor[i].coef_ref != 0)
		{
			cos1 = dot(tor[i].normale, tor[i].prim);
			new_ray = bounce_ray(scene, tor[i].prim, tor[i].normale);
			new_hit = ray_hit(scene, tor[i].pos, new_ray, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, new_ray, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000.f * new_hit.normal);
				new_hit.color = new_hit.obj->color;

				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = sphere_texture(fast_normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, ((__local t_sphere *)new_hit.obj)->diff_ratio, ((__local t_sphere *)new_hit.obj)->diff_offset);
				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = sphere_checkerboard(fast_normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

				if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = plane_texture(new_hit.normal, new_hit.pos, ((__local t_plane *)new_hit.obj)->u_axis, ((__local t_plane *)new_hit.obj)->diff_ratio, ((__local t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
				if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

				if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, (__local t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

				if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, ((__local t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((__local t_cone *)new_hit.obj)->diff_ratio, ((__local t_cone *)new_hit.obj)->diff_offset);

				ncolor = phong(scene, new_hit, new_ray);
				tor[i + 1] = tor_push(new_ray, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, old_hit.obj->type);
			}
			else
			{
				ncolor = (scene->flag & OPTION_SKYBOX) ? skybox(new_ray, scene->texture_skybox, 4096, 2048) : get_ambient(scene, BACKCOLOR);
				tor[i + 1] = tor_push(new_ray, 0, 0, 0, 0, 1, ncolor, 0, 0);
			}
		}
		i = i + 1;
	}
	return (rip_tor_final_color(tor));
}

static unsigned int	get_pixel_color(const __local t_scene *scene, float3 ray, __global int *target, bool isHim)
{
	t_hit			hit;
	int				depth = 0;
	unsigned int	color = 0;
	unsigned int	bounce_color = 0;

	hit = hit_init();
	hit.dist = MAX_DIST;
	depth = scene->depth;
	
	// DEBUG
	if (depth < 0)
		printf("!WARNING!\nget_pixel_color | depth < 0 !!!!\n");

	hit = ray_hit(scene, (ACTIVECAM.pos), ray, 0);
	if ((isHim == 1) && (hit.lock == 1))
		*target = hit.mem_index;
	if (hit.dist > EPSILON && hit.dist < MAX_DIST)
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normal = get_hit_normal(scene, ray, hit);
		hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * hit.normal);


		if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			 hit.color = sphere_texture(fast_normalize(hit.obj->pos - hit.pos), scene->texture_earth, 4915, 2457, ((__local t_sphere *)hit.obj)->diff_ratio, ((__local t_sphere *)hit.obj)->diff_offset);
		if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
			hit.color = sphere_checkerboard(fast_normalize(hit.obj->pos - hit.pos), hit.obj->color, hit.obj->check_size);

		if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = plane_texture(hit.normal, hit.pos, ((__local t_plane *)hit.obj)->u_axis, ((__local t_plane *)hit.obj)->diff_ratio, ((__local t_plane *)hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
		if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
			hit.color = plane_checkerboard(hit.normal, hit.pos, hit.obj->color, hit.obj->check_size);

		if ((hit.obj->type == OBJ_CYLINDER) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = cylinder_texture(hit.pos - hit.obj->pos, (__local t_cylinder *)hit.obj, scene->texture_star, 1500, 1500);

		if ((hit.obj->type == OBJ_CONE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = cone_texture(hit.pos - hit.obj->pos, hit.obj->dir, ((__local t_cone *)hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((__local t_cone *)hit.obj)->diff_ratio, ((__local t_cone *)hit.obj)->diff_offset);

		color = phong(scene, hit, ray);
		if (((hit.obj->refract != 0 && hit.obj->opacity < 1) || hit.obj->reflex > 0) && depth > 0)
			return (rip_fresnel(scene, ray, hit, depth, color));
			// return (fresnel(scene, ray, hit, depth + 1, color));

		return (blend_add(color, bounce_color));
	}
	
	if (scene->flag & OPTION_SKYBOX)
	{
		color = skybox(ray, scene->texture_skybox, 4096, 2048);
		return (color);
	}
	else
		return (get_ambient(scene, BACKCOLOR));
}

static float3		get_ray_cam(__local t_scene *scene, const uint2 pix, const uint width, const uint height)
{
	float3			cam_ray = 0;
	float			ratio = (convert_float(width)) / (convert_float(height));

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
								__global	unsigned int *texture_skybox,
								__global	unsigned int *texture_star)
{

 	event_t			ev;
	unsigned int	id = 0;
	uint2			pix = 0;
	float3			prim_ray = 0;
	unsigned int	final_color_o[32] = {0};
	unsigned int	final_color = 0;
	uint3			rgb = 0;

	ev = async_work_group_copy((__local char *)mem_objects, (__global char *)global_mem_objects, mem_size_objects, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)mem_lights, (__global char *)global_mem_lights, mem_size_lights, 0);
	wait_group_events(1, &ev);

	// OLD ID SHIT WITH THE TABLEAU DE SIZET COTE HOTE
	// pix.x = get_global_id(0);
	// pix.y = get_global_id(1);
	// id = pix.x + (scene->win_w * pix.y);

	// ID SHIT FOR CUSTOM WORKSIZES
	id = get_global_id(0);
	pix.x = id % scene->win_w;
	pix.y = id / scene->win_w;

	//DEBUG
	if (id >= (scene->win_w * scene->win_h))
	{
		printf("!WARNING!\n ray_trace | id is out of bound!\n");
		return;
	}

	scene->cameras = cameras;
	scene->mem_lights = mem_lights;
	scene->u_time = u_time;
	scene->mem_obj = mem_objects;
	scene->mem_size_obj = mem_size_objects;
	scene->mem_size_lights = mem_size_lights;
	scene->texture_earth = texture_earth;
	scene->texture_skybox = texture_skybox;
	scene->texture_moon = texture_moon;
	scene->texture_star = texture_star;

	if (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target = -1;

	final_color = 0;
	if (scene->over_sampling > 1)
	{
		uint2 true_pix = pix;
		unsigned int lap = 0;
		pix.x *= scene->over_sampling;
		pix.y *= scene->over_sampling;

		while (lap < scene->over_sampling * 2)
		{
			pix.x += (lap % 2);
			pix.y += !(lap % 2);
			prim_ray = get_ray_cam(scene, pix, scene->win_w * scene->over_sampling, scene->win_h * scene->over_sampling);
			final_color_o[lap] = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && true_pix.x == scene->mou_x && true_pix.y == scene->mou_y));
			rgb.x += (final_color_o[lap] & 0x00FF0000);
			rgb.y += (final_color_o[lap] & 0x0000FF00);
			rgb.z += (final_color_o[lap] & 0x000000FF);
			lap++;
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

	// ALPHA INSERT and RGB SWAP
	int4 swap;
	swap.w = 255;
	swap.x = (final_color & 0x00FF0000) >> 16;
	swap.y = (final_color & 0x0000FF00) >> 8;
	swap.z = (final_color & 0x000000FF);
	final_color = ((swap.w << 24) + (swap.z << 16) + (swap.y << 8) + swap.x);
	((__global unsigned int *)output)[id] = final_color;
}
