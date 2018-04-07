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
#define MAX_DIST 10000000.0
#define SHADOW_BIAS 1000

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

#define OBJ_FLAG_WAVES				(1 << 1)
#define OBJ_FLAG_CHECKERED			(1 << 2)
#define OBJ_FLAG_DIFF_MAP			(1 << 3)
#define OBJ_FLAG_BUMP_MAP			(1 << 4)
#define OBJ_FLAG_PLANE_LIMIT		(1 << 5)
#define OBJ_FLAG_PLANE_LIMIT_FIX	(1 << 6)

# define OBJ_CAM					1
# define OBJ_LIGHT					2
# define OBJ_CONE					3
# define OBJ_CYLINDER				4
# define OBJ_PLANE					5
# define OBJ_SPHERE					6
# define OBJ_ELLIPSOID				7
# define OBJ_THOR					8
# define OBJ_BOX					9

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
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;
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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	float3				limit_pos;
	float3				limit_dir;
	float3				waves_p1;
	float3				waves_p2;
	float2				check_size;
	int					diff_map_id;
	float2				diff_offset;
	float2				diff_ratio;
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	float2				test_var1;
	float2				test_var2;
	float2				test_var3;

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
	int					wall; // WIP
}						t_hit;

typedef struct			s_tex
{
	unsigned int		pixel_array[12076155];
	int					width;
	int					height;
}						t_tex;

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

	hit.wall = 0;
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
** LIMIT WITH A PLANE FUNCTIONS ////////////////////////////////////////////////
*/
static float	inter_plan_private(const t_plane *plane, const float3 ray, const float3 origin)
{
	float		t;

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
	float		dist_plan;

	ret.dist = 0;
	ret.wall = 0;
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

////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////




/*
** CYLINDER FUNCTIONS //////////////////////////////////////////////////////////
*/
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
	float		doty;

	res = 0;
	v = 0;
	project = 0;
	doty = 0;
	v = hit.pos - cylinder->pos;
	doty = dot(v, cylinder->dir);
	project = doty * cylinder->dir;
	res = v - project;
	return (fast_normalize(res));
}

static t_ret	inter_cylinder(const __local t_cylinder *cylinder, const float3 ray, const float3 origin)
{
	float3		abc;
	float3		pos;
	float		res1;
	float		res2;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
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
** CONES FUNCTIONS /////////////////////////////////////////////////////////////
*/
static float3	get_cone_normal(const __local t_cone *cone, const t_hit hit)
{
	float3		res;
	float3		final;
	float3		v;
	float3		project;
	float		doty;
	float		m;
	float		r;	// UNUSED
	float		k;

	v = hit.pos - cone->pos;
	doty = dot(v, cone->dir);
	project = doty * cone->dir;
	m = fast_length(project);
	res = v - project;
	final = res;

	//  ABORT DAMNED
	r = fast_length(res);
	if (m < 0)
		m = -m;
	k = r / m;
	k = m * k * k;
	float3 dir = k * dir;
	final.x = v.x - dir.x;
	final.y = v.y - dir.y;
	final.z = v.z - dir.z;
	// res = v - res;
	return (fast_normalize(final));
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
	pos = origin - cone->pos;
	abc = get_cone_abc(cone, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	//if (cone->flags & OBJ_FLAG_PLANE_LIMIT)
	//	return (object_limited_cone((t_object __local *)cone, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}
////////////////////////////////////////////////////////////////////////////////



static t_hit			ray_hit(const __local t_scene *scene, const float3 origin, const float3 ray, float lightdist)
{
	t_hit						hit;
	float						dist;
	t_object 		__local		*obj;
	uint						mem_index_obj;
	t_ret						ret;

	dist = 0;
	hit = hit_init();
	mem_index_obj = 0;
	obj = 0;
	if (lightdist == 0)
		hit.opacity = 1;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = scene->mem_obj + mem_index_obj;
		if (obj->type == OBJ_CYLINDER)
		 	ret = inter_cylinder((__local struct s_cylinder *)obj, ray, origin);
		if (obj->type == OBJ_CONE)
		 	ret = inter_cone((__local struct s_cone *)obj, ray, origin);
		if (lightdist > 0 && ret.dist < lightdist && ret.dist > EPSILONF)
			hit.opacity += obj->opacity;
		if ((ret.dist < hit.dist || hit.dist == 0) && ret.dist > EPSILONF)
		{
			hit.dist = ret.dist;
			hit.normal = ret.normal;
			hit.wall = ret.wall;
			hit.obj = obj;
			hit.mem_index = mem_index_obj;
		}
		mem_index_obj += obj->size;
	}
	return (hit);
}

static float3			get_hit_normal(const __local t_scene *scene, float3 ray, t_hit hit)
{
	float3				res, save;
	t_object __local	*object;

	object = hit.obj;
	res = 0;
	if (hit.wall)
		res = hit.normal;
	else
	{
		if (hit.obj->type == OBJ_CYLINDER)
			res = get_cylinder_normal((__local t_cylinder *)hit.obj, hit);
		if (hit.obj->type == OBJ_CONE)
			res = get_cone_normal((__local t_cone *)hit.obj, hit);
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

	while (mem_index_lights < scene->mem_size_lights)
	{
		tmp = 0;
		light = scene->mem_lights + mem_index_lights;
		light_ray.dir = light->pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir, light_ray.dist);
		if (!(light_hit.dist < light_ray.dist && light_hit.dist > EPSILONF) || light_hit.opacity < 1)
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

				// if (scene->flag & OPTION_CARTOON_FOUR)
				// 	res_color = cartoonize_four(col_r, col_g, col_b);
				// else if (scene->flag & OPTION_CARTOON_TWO)
				//  	res_color = cartoonize_two(col_r, col_g, col_b);
				// else
					res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}

			// specular part
			reflect = fast_normalize(((float)(2.0 * dot(hit.normal, light_ray.dir)) * hit.normal) - light_ray.dir);
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
			//	col_r = (col_r > 255 ? col_r / (col_r + 1) : col_r);
				(col_g > 255 ? col_g = 255 : 0);
			//	col_g = (col_g > 255 ? col_g / (col_g + 1) : col_g);
				(col_b > 255 ? col_b = 255 : 0);
			//	col_b = (col_b > 255 ? col_b / (col_b + 1) : col_b);

				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			res_color = blend_factor(res_color, ((light_hit.opacity - 1) * -1));
			if (scene->flag & OPTION_CARTOON_FOUR)
			 	res_color = cartoonize_four(col_r, col_g, col_b);
			else if (scene->flag & OPTION_CARTOON_TWO)
			 	res_color = cartoonize_two(col_r, col_g, col_b);
		}
		mem_index_lights += light->size;
	}
	return (res_color);
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

		color = phong(scene, hit, ray);
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

	// int boo = get_global_id(0) + get_global_id(1); // unused, remove?

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
	scene->texture_earth = texture_earth;
	scene->texture_earth_cloud = texture_earth_cloud;
	scene->texture_moon = texture_moon;
	scene->texture_star = texture_star;
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


	// ALPHA INSERT and RGB SWAP
	int4 swap;
	swap.w = 255;
	swap.x = (final_color & 0x00FF0000) >> 16;
	swap.y = (final_color & 0x0000FF00) >> 8;
	swap.z = (final_color & 0x000000FF);
	final_color = ((swap.w << 24) + (swap.z << 16) + (swap.y << 8) + swap.x);
	((__global unsigned int *)output)[id] = final_color;
}
