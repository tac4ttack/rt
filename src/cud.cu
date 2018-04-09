#include <cuda.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include "../includes/help_math.h"
extern "C" {

}


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


typedef struct			s_gen
{
	size_t				mem_size;
	size_t				length;
	void				*mem;
	bool				(*add)(struct s_gen *, void *);
	bool				(*remove_mem_index)(struct s_gen *, size_t);
	bool				(*remove_index)(struct s_gen *, size_t);
	void				(*print)(struct s_gen *, \
								void (*)(struct s_gen *, void *));
}						t_gen;

/*
** CAM AND LIGHT STRUCTS ///////////////////////////////////////////////////////
*/

typedef struct			s_float3
{
	float				x;
	float				y;
	float				z;
}						t_float3;
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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;
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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	float3				check_size;
	int					diff_map_id;
	float3				diff_offset;
	float3				diff_ratio;
	float3				test_var1;
	float3				test_var2;
	float3				test_var3;

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
	int				mem_index;
	int					id;
	int					type;
	float				dist;
	float				fr;
	float				ft;
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
	t_object 			*obj;
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
	t_cam				*cameras;
//	void				*dummy_pedro;
	void				*mem_lights;  //repassé en void à cause de l'erreur compilation, sinon pour oclgrind foutre char
//	void				*dummy_gomez;
	void				*mem_obj; //repassé en void à cause de l'erreur compilation, sinon pour oclgrind foutre char
//	void				*dummy_ramon;
	unsigned int		*texture_earth;
	unsigned int		*texture_moon;
	unsigned int		*texture_earth_cloud;
	unsigned int		*texture_star;
}						t_scene;
/*
__host__ __device__ float dot(const float3 a, const float3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

__host__ __device__ float sqrt_magnitude(const float3 a)
{
	return (sqrtf(fabs(a.x * a.x) + fabs(a.y * a.y) + fabs(a.z * a.z)));
}

__host__ __device__ float length(const float3 a)
{
	return sqrtf(dot(a, a));
}

__host__ __device__ float3 normalize(const float3 a)
{
	float3		newv;
	float		ret_magnitude;

	ret_magnitude = length(a);
	if (fabs(ret_magnitude) < EPSILONF)
		return (a);
	newv.x = a.x / ret_magnitude;
	newv.y = a.y / ret_magnitude;
	newv.z = a.z / ret_magnitude;
	return (newv);
}
*/
inline __host__ __device__ float radians(double degree) {
    return (degree * M_PI / 180.0f);
}
/*
// additional constructors
inline __host__ __device__ float3 make_float3(float s)
{
    return make_float3(s, s, s);
}
inline __host__ __device__ float3 make_float3(float2 a)
{
    return make_float3(a.x, a.y, 0.0f);
}
inline __host__ __device__ float3 make_float3(float2 a, float s)
{
    return make_float3(a.x, a.y, s);
}
inline __host__ __device__ float3 make_float3(float4 a)
{
    return make_float3(a.x, a.y, a.z);  // discards w
}
inline __host__ __device__ float3 make_float3(int3 a)
{
    return make_float3(float(a.x), float(a.y), float(a.z));
}

// addition
inline __host__ __device__ float3 operator+(float3 a, float3 b)
{
    return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline __host__ __device__ float3 operator+(float3 a, float b)
{
    return make_float3(a.x + b, a.y + b, a.z + b);
}
inline __host__ __device__ void operator+=(float3 &a, float3 b)
{
    a.x += b.x; a.y += b.y; a.z += b.z;
}

// subtract
inline __host__ __device__ float3 operator-(float3 a, float3 b)
{
    return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline __host__ __device__ float3 operator-(float3 a, float b)
{
    return make_float3(a.x - b, a.y - b, a.z - b);
}
inline __host__ __device__ void operator-=(float3 &a, float3 b)
{
    a.x -= b.x; a.y -= b.y; a.z -= b.z;
}

// multiply
inline __host__ __device__ float3 operator*(float3 a, float3 b)
{
    return make_float3(a.x * b.x, a.y * b.y, a.z * b.z);
}
inline __host__ __device__ float3 operator*(float3 a, float s)
{
    return make_float3(a.x * s, a.y * s, a.z * s);
}
inline __host__ __device__ float3 operator*(float s, float3 a)
{
    return make_float3(a.x * s, a.y * s, a.z * s);
}
inline __host__ __device__ void operator*=(float3 &a, float s)
{
    a.x *= s; a.y *= s; a.z *= s;
}

// divide
inline __host__ __device__ float3 operator/(float3 a, float3 b)
{
    return make_float3(a.x / b.x, a.y / b.y, a.z / b.z);
}
inline __host__ __device__ float3 operator/(float3 a, float s)
{
    float inv = 1.0f / s;
    return a * inv;
}
inline __host__ __device__ float3 operator/(float s, float3 a)
{
    float inv = 1.0f / s;
    return a * inv;
}
inline __host__ __device__ void operator/=(float3 &a, float s)
{
    float inv = 1.0f / s;
    a *= inv;
}
*/
__host__ __device__ float3	vector_get_rotate(const float3 *me, const float3 *rot)
{
	float3		n;
	float		tmp;

	n = *me;
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

__host__ __device__ float3	vector_get_inverse(const float3 *me, const float3 *rot)
{
	float3		n;
	float		tmp;

	n = *me;
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

__host__ __device__ t_hit	hit_init(void)
{
	t_hit		hit;

	hit.dist = 0.f;
	hit.normal = make_float3(0.0f);

	hit.obj = NULL; // dangling dangerouss!

	hit.wall = 0;
	hit.color = 0;
	hit.pos = make_float3(0.0f);
	hit.mem_index = 0;
	hit.opacity = 0;
	return (hit);
}

__host__ __device__ float3	rotat_zyx(const float3 vect, const float pitch, const float yaw, const float roll)
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

__host__ __device__ unsigned int	blend_multiply(const unsigned int c1, const unsigned int c2)
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

__host__ __device__ unsigned int	blend_med(const unsigned int c1, const unsigned int c2)
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

__host__ __device__ unsigned int	blend_add(const unsigned int c1, const unsigned int c2)
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

__host__ __device__ unsigned int	blend_factor(const unsigned int c1, const float factor)
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

__host__ __device__ unsigned int	get_ambient(const t_scene *scene, const unsigned int obj_color)
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

__host__ __device__ unsigned int cartoonize_four(unsigned int col_r, unsigned int col_g, unsigned int col_b)
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

__host__ __device__ unsigned int cartoonize_two(unsigned int col_r, unsigned int col_g, unsigned int col_b)
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

__host__ __device__  bool		solve_quadratic(const float a, const float b, const float c, float *inter0, float *inter1)
{
	float 		discr;
	float 		tmp;
	float 		q;

	q = 0;
	discr = b * b - 4.f * a * c;
	tmp = 0;
	if (discr < EPSILONF)
		return (false);
	else if (discr < EPSILONF)
	{
		*inter0 = -0.5 * b / a;
		*inter1 = *inter0;
	}
	else
	{
		q = (b > 0) ? (-0.5f * (b + sqrtf(discr))): (-0.5 * (b - sqrtf(discr)));
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

__host__ __device__ float3	get_sphere_abc(const float radius, const float3 ray, const float3 origin)
{
	float3		abc = make_float3(0.f);

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (radius * radius);
	return (abc);
}

__host__ __device__ t_ret	inter_sphere(const  t_sphere *sphere, const float3 ray, const float3 origin)
{
	float3		abc = make_float3(0.f);
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = make_float3(0.f);
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
//	if (sphere->flags & OBJ_FLAG_PLANE_LIMIT)
//		return (object_limited((t_object  *)sphere, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
/*
float3		abc = make_float3(0.f);
float3		pos = make_float3(0.f);
float		d = 0;
float		res1 = 0;
float		res2 = 0;
t_ret		ret;

ret.wall = 0;
ret.dist = 0;
pos = origin - sphere->pos;
abc = get_sphere_abc(sphere->radius, ray, pos);
d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
if (d < 0)
	return (ret);
if (d == 0)
{
	ret.dist =  ((-abc.y) / (2 * abc.x));
	return (ret);
}
res1 = (((-abc.y) + sqrt(d)) / (2 * abc.x));
res2 = (((-abc.y) - sqrt(d)) / (2 * abc.x));
if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
{
	ret.dist = res1;
	return (ret);
}
ret.dist = res2;
return (ret);*/
}

__host__ __device__ float3	get_cylinder_normal(const  t_cylinder *cylinder, t_hit hit)
{
	float3		res;
	float3		v;
	float3		project;
	float		doty;

	res = make_float3(0.f);
	project = make_float3(0.f);
	v = make_float3(0.f);
	doty = 0;
	v = hit.pos - cylinder->pos;
	doty = dot(v, cylinder->dir);
	project = doty * cylinder->dir;
	res = v - project;
	return (normalize(res));
}

__host__ __device__ float3	get_cylinder_abc(const float radius, const float3 dir, const float3 ray, const float3 origin)
{
	float3		abc;

	// SEMBLE OK
	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

__host__ __device__ t_ret	inter_cylinder(const  t_cylinder *cylinder, const float3 ray, const float3 origin)
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
	//if (cylinder->flags & OBJ_FLAG_PLANE_LIMIT)
	//	return (object_limited((t_object  *)cylinder, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}

__host__ __device__ t_ret	inter_plan(const  t_plane *plane, const float3 ray, const float3 origin)
{
	float		t;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	t = dot(normalize(ray), plane->normal);
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
	//if (plane->flags & OBJ_FLAG_PLANE_LIMIT)
	//	return (object_limited((t_object  *)plane, t, t, ray, origin));
	ret.dist = t;
	return (ret);
}

__host__ __device__ float3		get_ellipsoid_normal(const  t_ellipsoid *ellipsoid, const t_hit *hit)
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

__host__ __device__ t_ret	inter_ellipsoid(const  t_ellipsoid *ellipsoid, float3 ray, float3 origin)
{
	float3		abc;
	float		res1, res2;
	float3		pos;
	float3		save_ray;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	abc = make_float3(0.f);
	pos = make_float3(0.f);
	save_ray = ray;
	pos = origin - ellipsoid->pos;
	pos = vector_get_rotate(&pos, &ellipsoid->dir);
	ray = vector_get_rotate(&ray, &ellipsoid->dir);
	ray = ray / ellipsoid->axis_size;
	pos = pos / ellipsoid->axis_size;

	abc.x = (ray.x * ray.x +
	 	ray.y * ray.y +
	 	ray.z * ray.z);
	abc.y = (2 * pos.x * ray.x +
		 2 * pos.y * ray.y +
		 2 * pos.z * ray.z);
	abc.z = (pos.x * pos.x +
		 pos.y * pos.y +
		 pos.z * pos.z) - (ellipsoid->radius * ellipsoid->radius);

	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	//if (ellipsoid->flags & OBJ_FLAG_PLANE_LIMIT)
	//	return (object_limited((t_object  *)ellipsoid, res1, res2, save_ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}

__host__ __device__ float3	get_cone_normal(const  t_cone *cone, const t_hit hit)
{
	float3		res;
	float3		v;
	float3		project;
	float		doty;
	float		m;

	v = hit.pos - cone->pos;
	doty = dot(v, cone->dir);
	project = doty * cone->dir;
	m = length(project);
	res = v - project;

	return (normalize(res));
}

__host__ __device__ float3	get_cone_abc(const  t_cone *cone, const float3 ray, const float3 origin)
{
	float3		abc = make_float3(0.f);
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

__host__ __device__ t_ret	inter_cone(const  t_cone *cone, const float3 ray, const float3 origin)
{
	float3		abc;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	pos = make_float3(0.f);
	abc = make_float3(0.f);
	pos = origin - cone->pos;
	abc = get_cone_abc(cone, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	//if (cone->flags & OBJ_FLAG_PLANE_LIMIT)
	//	return (object_limited_cone((t_object  *)cone, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}

__host__ __device__ t_hit			ray_hit(const  t_scene *scene, const float3 origin, const float3 ray, float lightdist)
{
	t_hit						hit;
	float						dist;
	t_object 				*obj;
	unsigned int						mem_index_obj;
	t_ret						ret;

	dist = 0;
	hit = hit_init();
	mem_index_obj = 0;
	obj = 0;
	if (lightdist == 0)
		hit.opacity = 1;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = (t_object *)((char *)scene->mem_obj + mem_index_obj);
		if (obj->type == OBJ_SPHERE)
		 	ret = inter_sphere(( struct s_sphere *)obj, ray, origin);
		else if (obj->type == OBJ_CYLINDER)
		 	ret = inter_cylinder(( struct s_cylinder *)obj, ray, origin);
		else if (obj->type == OBJ_PLANE)
		 	ret = inter_plan(( struct s_plane *)obj, ray, origin);
		else if (obj->type == OBJ_CONE)
		 	ret = inter_cone(( struct s_cone *)obj, ray, origin);
		else if (obj->type == OBJ_ELLIPSOID)
		   	ret = inter_ellipsoid(( struct s_ellipsoid *)obj, ray, origin);
		//else if (obj->type == OBJ_THOR)
		//	ret = inter_thor(( struct s_thor *)obj, ray, origin);
		if (lightdist > 0 && ret.dist < lightdist && ret.dist > EPSILON)
			hit.opacity += obj->opacity;
		if ((ret.dist < hit.dist || hit.dist == 0) && ret.dist > EPSILON)
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


__host__ __device__ float3			get_hit_normal(const  t_scene *scene, float3 ray, t_hit hit)
{
	float3				res, save;
	t_object 	*object;

	object = hit.obj;
	res = make_float3(0.f);
	if (hit.wall)
		res = hit.normal;
	else
	{
		if (hit.obj->type == OBJ_SPHERE)
		 	res = hit.pos - hit.obj->pos;
		else if (hit.obj->type == OBJ_CYLINDER)
			res = get_cylinder_normal(( t_cylinder *)hit.obj, hit);
		else if (hit.obj->type == OBJ_CONE)
			res = get_cone_normal(( t_cone *)hit.obj, hit);
		else if (hit.obj->type == OBJ_ELLIPSOID)
			res = get_ellipsoid_normal(( t_ellipsoid *)hit.obj, &hit);
		//else if (hit.obj->type == OBJ_THOR)
		//	res = get_thor_normal(( t_thor *)hit.obj, hit);
		else if (hit.obj->type == OBJ_PLANE)
		{
			if (dot(hit.obj->dir, ray * -1) < 0)
				res = hit.obj->dir * -1;
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

	return (normalize(save));
}

__host__ __device__ unsigned int			phong(const  t_scene *scene, const t_hit hit, const float3 ray)
{
	t_object 		*obj;
	t_light 			*light;
	unsigned int					mem_index_lights;

	unsigned int			res_color;
	float					tmp;
	float3					reflect;
	float3 		diffuse;
	float 			brightness;
	unsigned int  	hue;
	unsigned int 	hue_light;
	unsigned int  	col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	t_light_ray				light_ray;
	t_hit					light_hit;
	float  		pow_of_spec;
	int  			light_color;
	float3  		speculos;

	tmp = 0;
	reflect = make_float3(0.f);
	diffuse = make_float3(0.f);
	speculos = make_float3(0.f);
	brightness = 0;
	hue_light = 0;
	pow_of_spec = 0;
	light_color = 0;
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
		light = (t_light *)((char *)scene->mem_lights + mem_index_lights);
		light_ray.dir = light->pos - hit.pos;
		light_ray.dist = length(light_ray.dir);
		light_ray.dir = normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir, light_ray.dist);
		if (!(light_hit.dist < light_ray.dist && light_hit.dist > EPSILON) || (light_hit.opacity < 1 && scene->depth != 0))
		{
			// diffuse part
			tmp = (dot(hit.normal, light_ray.dir));
			if (tmp > EPSILON)
			{
				brightness = (float )light->brightness;
				diffuse = (float3 )obj->diff;
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

				if (scene->flag & OPTION_CARTOON_FOUR)
					res_color = cartoonize_four(col_r, col_g, col_b);
				else if (scene->flag & OPTION_CARTOON_TWO)
				 	res_color = cartoonize_two(col_r, col_g, col_b);
				else
					res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}

			// specular part
			reflect = normalize(((float)(2.0f * dot(hit.normal, light_ray.dir)) * hit.normal) - light_ray.dir);
			tmp = dot(reflect, ray * -1);
			if (tmp > EPSILON)
			{
				speculos = obj->spec;
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = pow(tmp, (light->shrink));
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

__host__ __device__ float		reflect_ratio(float n1, float n2, float cos1, float sint)
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


__host__ __device__ float3		refract_ray(const  t_scene *scene, const float3 ray, float3 normale, float tra) // pour le plan, indice de refraction (pour tout objet non plein)
{
	float3			refract = make_float3(0.f);
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
	refract = normalize((eta * ray) + ((eta * c1) - c2) * normale);
	////////////////////////////////////////////////////////////////////////////////
	return (refract);
}

__host__ __device__ float3		bounce_ray(const  t_scene *scene, const float3 ray, t_tor tor)
{
	float3			reflex;
	float			reflex_coef;

	reflex = make_float3(0.f);
	reflex_coef = 0;
	// PREMIÈRE LOI DE SNELL-DESCARTES ///////////////////////////////////////////////////////////
	reflex = normalize(ray - (2 * (float)dot(tor.normale, ray) * tor.normale));
	//////////////////////////////////////////////////////////////////////////////////////////////
	return (reflex);
}

__host__ __device__ int			tor_height(int i)
{
	int				h = 0;

	while ((i = (i - 1) / 2) >= 0)
		h++;
	return (h);
}

__host__ __device__ unsigned int	tor_final_color(t_tor *tor)
{
	int				i = 31;
	unsigned int	color = 0;

	while (i > 0 && tor[i].activate == 0)
		i = i - 1;
	if (i != 0)
	{
		if (i % 2 == 0)
			i = (i / 2) - 1;
		else
			i = (i - 1) / 2;
	}
	while (i > 0)
	{
		if (tor[i].activate == 0 && (tor[i * 2 + 1].activate == 0 && tor[(i + 1) * 2].activate == 0))
			;
		else
		{
			color = blend_add(blend_factor(tor[(i + 1) * 2].color, tor[(i + 1) * 2].fr), blend_factor(tor[i * 2 + 1].color, tor[i * 2 + 1].ft));
			if (tor[i].coef_tra != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
			else if (tor[i].coef_ref != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
			// else
			// tor[i].color = blend_add(color, tor[i].color);
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

__host__ __device__ t_tor		tor_push(float3 ray, float3 normale, float3 pos, float coef_ref, float coef_tra, float opacity, unsigned int color, uint mem_index, int id, int type, float fr, float ft)
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
	tor.fr = fr;
	tor.ft = ft;
	return (tor);
}


__host__ __device__ unsigned int	fresnel(const  t_scene *scene, float3 ray, t_hit old_hit, int depth, unsigned int color)
{
	t_hit			new_hit;
	unsigned int	ncolor = 0;
	float3			refract = make_float3(0.f);
	float3			bounce = make_float3(0.f);
	float			fr = 0;
	float			ft = 0;
	float			eta = 0;
	float			cos1 = 0;
	float			sint = 0;
	t_tor			tor[64];
	int				i = 0;

	depth = (int)pow(2.f, (float)depth) - 1;
	i = 0;
	while (i < 64)
	{
		tor[i].activate = 0;
		tor[i].prim = make_float3(0.f);
		tor[i].normale = make_float3(0.f);
		tor[i].pos = make_float3(0.f);
		tor[i].coef_ref = 0;
		tor[i].coef_tra = 0;
		tor[i].color = 0;
		tor[i].opacity = 0;
		tor[i].mem_index = 0;
		tor[i].id = 0;
		tor[i].type = 0;
		tor[i].dist = 0;
		i++;
	}
	i = 0;
	tor[i] = tor_push(ray, old_hit.normal, old_hit.pos, old_hit.obj->reflex, old_hit.obj->refract, old_hit.obj->opacity, color, old_hit.mem_index, old_hit.obj->id, old_hit.obj->type, 0, 0);
	while (i < 31 && i < depth)
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
			else if (cos1 < 0)
				fr = reflect_ratio(1, tor[i].coef_tra, cos1, sint);
			else
				fr = reflect_ratio(tor[i].coef_tra, 1, cos1, sint);
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
					new_hit = ray_hit(scene, tor[i].pos + (0.001f * (2.f * -tor[i].normale)), refract, 0);
				else
					new_hit = ray_hit(scene, tor[i].pos, refract, 0);
				if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
				{
					if (cos1 < 0)
					 	new_hit.pos = (new_hit.dist * refract) + tor[i].pos + (0.001f * (2.f * -tor[i].normale));
					else
						new_hit.pos = (new_hit.dist * refract) + tor[i].pos;
					new_hit.normal = get_hit_normal(scene, refract, new_hit);
					new_hit.pos = new_hit.pos + (0.001f * new_hit.normal);


					/*if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						new_hit.color = sphere_texture(normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, (( t_sphere *)new_hit.obj)->diff_ratio, (( t_sphere *)new_hit.obj)->diff_offset);
					if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
						new_hit.color = sphere_checkerboard(normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

					if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						new_hit.color = plane_texture(new_hit.normal, new_hit.pos, (( t_plane *)new_hit.obj)->u_axis, (( t_plane *)new_hit.obj)->diff_ratio, (( t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
					if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
						new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

					if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, ( t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

					if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
						new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, (( t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, (( t_cone *)new_hit.obj)->diff_ratio, (( t_cone *)new_hit.obj)->diff_offset);
*/

					ncolor = phong(scene, new_hit, refract);
					tor[i * 2 + 1] = tor_push(refract, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, new_hit.obj->id, old_hit.obj->type, 0, ft);
				}
			}
		}
		else if (tor[i].coef_ref != 0)
			fr = 1;
		else
			fr = 0;
		if (fr > 0)
		{
			cos1 = dot(tor[i].normale, tor[i].prim);
			bounce = bounce_ray(scene, tor[i].prim, tor[i]);
			if (cos1 >= 0)
				new_hit = ray_hit(scene, tor[i].pos + (0.001f * (2.f * -tor[i].normale)), bounce, 0);
			else
				new_hit = ray_hit(scene, tor[i].pos, bounce, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				if (cos1 >= 0)
					new_hit.pos = (new_hit.dist * bounce) + tor[i].pos + (0.001f * (2.f * -tor[i].normale));
				else
					new_hit.pos = (new_hit.dist * bounce) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, bounce, new_hit);
				new_hit.pos = new_hit.pos + (0.001f * new_hit.normal);
/*

				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = sphere_texture(normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, (( t_sphere *)new_hit.obj)->diff_ratio, (( t_sphere *)new_hit.obj)->diff_offset);
				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = sphere_checkerboard(normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

				if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = plane_texture(new_hit.normal, new_hit.pos, (( t_plane *)new_hit.obj)->u_axis, (( t_plane *)new_hit.obj)->diff_ratio, (( t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
				if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

				if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, ( t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

				if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, (( t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, (( t_cone *)new_hit.obj)->diff_ratio, (( t_cone *)new_hit.obj)->diff_offset);
*/


				ncolor = phong(scene, new_hit, bounce);
				tor[i * 2 + 2] = tor_push(bounce, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, new_hit.obj->id, old_hit.obj->type, fr, 0);
			}
		}
		i = i + 1;
		while (i < 31 && tor[i].activate == 0)
			i = i + 1;
	}
	return (tor_final_color(tor));
}

__host__ __device__ unsigned int	get_pixel_color(const  t_scene *scene, float3 ray,  int *target, bool isHim, int index)
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
	if ((isHim == 1) && (hit.obj != NULL))
		*target = hit.mem_index;
	if (hit.dist > EPSILON && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		/*if (index == 1024*500 + 900)
			printf("%.2f * %.2f %.2f %.2f + %.2f %.2f %.2f == %.2f %.2f %.2f\n",
				hit.dist, ray.x, ray.y, ray.z, ACTIVECAM.pos.x, ACTIVECAM.pos.y, ACTIVECAM.pos.z,
				hit.pos.x, hit.pos.y, hit.pos.z);*/
		hit.normal = get_hit_normal(scene, ray, hit);
		//hit.pos = hit.pos + (0.001f * hit.normal);
		hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * hit.normal);
/*
		if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = sphere_texture(normalize(hit.obj->pos - hit.pos), scene->texture_earth, 4915, 2457, (( t_sphere *)hit.obj)->diff_ratio, (( t_sphere *)hit.obj)->diff_offset);
		if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
			hit.color = sphere_checkerboard(normalize(hit.obj->pos - hit.pos), hit.obj->color, hit.obj->check_size);

		if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = plane_texture(hit.normal, hit.pos, (( t_plane *)hit.obj)->u_axis, (( t_plane *)hit.obj)->diff_ratio, (( t_plane *)hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
		if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
			hit.color = plane_checkerboard(hit.normal, hit.pos, hit.obj->color, hit.obj->check_size);

		if ((hit.obj->type == OBJ_CYLINDER) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = cylinder_texture(hit.pos - hit.obj->pos, ( t_cylinder *)hit.obj, scene->texture_star, 1500, 1500);

		if ((hit.obj->type == OBJ_CONE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = cone_texture(hit.pos - hit.obj->pos, hit.obj->dir, (( t_cone *)hit.obj)->u_axis, scene->texture_star, 1500, 1500, (( t_cone *)hit.obj)->diff_ratio, (( t_cone *)hit.obj)->diff_offset);
*/
		color = phong(scene, hit, ray);
		if (((hit.obj->refract != 0 && hit.obj->opacity < 1) || hit.obj->reflex > 0) && depth > 0)
			return (fresnel(scene, ray, hit, depth + 1, color));

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

__host__ __device__ float3		get_ray_cam(t_scene *scene, const int x, const int y, const int width, const int height)
{
	float3			cam_ray = make_float3(0.f);
	float			ratio = ((float)width) / ((float)height);

	cam_ray.x = ((2.f * (((float)x + 0.5f) / (float)width)) - 1.f) * ratio * (tanf(radians(ACTIVECAM.fov / 2.f)));
	cam_ray.y = ((1.f - (2 * (((float)y + 0.5f) / (float)height))) * tanf(radians(ACTIVECAM.fov / 2.f)));
	cam_ray.z = 1.f;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(normalize(cam_ray));
}

__host__ __device__ unsigned int	ray_trace(	int				index,
												char			*mem_objects,
												int				mem_size_objects,
												float			u_time,

												t_scene			*scene,
												t_cam			*cameras,

												char			*mem_lights,
												int				mem_size_lights,

												int				*target,
												unsigned int	*texture_earth,
												unsigned int	*texture_moon,
												unsigned int	*texture_earth_cloud,
												unsigned int	*texture_star)
{
	unsigned int	final_color;

	float3			prim_ray;
//	unsigned int	final_color_o[32];
	int				x;
	int				y;

	x = index % scene->win_w;
	y = index / scene->win_w;

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
	if (scene->flag & OPTION_RUN && scene->mou_x + scene->win_h * scene->mou_y == index)
		*target = -1;
	final_color = 0;

	//v2 need oversampling
	prim_ray = get_ray_cam(scene, x, y, scene->win_w, scene->win_h);
	final_color = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && x == scene->mou_x && y == scene->mou_y), index);

/*	if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);
	if (scene->flag & OPTION_INVERT)
		final_color = invert(final_color);*/


	// ALPHA INSERT and RGB SWAP
	int nw, nx, ny, nz;
	nw = 255;
	nx = (final_color & 0x00FF0000) >> 16;
	ny = (final_color & 0x0000FF00) >> 8;
	nz = (final_color & 0x000000FF);
	final_color = ((nw << 24) + (nz << 16) + (ny << 8) + nx);
	return (final_color);
}

__global__ void test(unsigned int *output, unsigned int width, unsigned int height,
							char *mem_objects, int mem_size_objects,
							float u_time,
							t_scene *scene_data, t_cam *cameras_data,
							char *mem_lights, int mem_size_lights)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int index = row * width + col;
	output[index] = ray_trace(index, mem_objects, mem_size_objects,
								u_time,
							scene_data, cameras_data,
							mem_lights, mem_size_lights, 0, NULL, NULL, NULL, NULL);
}

extern "C" void render_cuda(unsigned int width, unsigned int height,
							int 		*pixel_data,
							t_gen		*gen_objects,
							t_gen		*gen_lights,
							float		u_time,
							t_scene			*scene_data,
							t_cam			*cameras_data)
{
	dim3					threads_per_block(8, 8);
	dim3					grid_size(width / threads_per_block.x, height / threads_per_block.y);

	/*printf("GPU\n");
	printf("t_cam %zu\n", sizeof(t_cam));
	printf("t_scene %zu\n", sizeof(t_scene));
	printf("t_object %zu\n", sizeof(t_object));
	printf("t_gen %zu\n", sizeof(t_gen));
	printf("t_sphere %zu\n", sizeof(t_sphere));
	printf("t_light %zu\n", sizeof(t_light));
	printf("\n");*/
	//printf("\n{[(%.2f)]}\n\n", cameras_data[0].fov);

	unsigned int *output = NULL;
	cudaMalloc(&output, width * height * sizeof(int));
	char *mem_objects = NULL;
	cudaMalloc(&mem_objects, gen_objects->mem_size);
	cudaMemcpy(mem_objects, gen_objects->mem, gen_objects->mem_size, cudaMemcpyHostToDevice);
	char *mem_lights = NULL;
	cudaMalloc(&mem_lights, gen_lights->mem_size);
	cudaMemcpy(mem_lights, gen_lights->mem, gen_lights->mem_size, cudaMemcpyHostToDevice);
	t_scene *scene = NULL;
	cudaMalloc(&scene, sizeof(t_scene));
	cudaMemcpy(scene, scene_data, sizeof(t_scene), cudaMemcpyHostToDevice);
	t_cam *cameras = NULL;
	cudaMalloc(&cameras, sizeof(t_cam) * scene_data->n_cams); /////////////////*******************
	cudaMemcpy(cameras, cameras_data, sizeof(t_cam), cudaMemcpyHostToDevice);

	test <<< grid_size, threads_per_block >>> (output, width, height,
												mem_objects, gen_objects->mem_size,
												u_time,
												scene, cameras,
												mem_lights, gen_lights->mem_size);
	cudaDeviceSynchronize();

	// check for errors
	cudaError_t error = cudaGetLastError();
	if (error != cudaSuccess) {
	  fprintf(stderr, "ERROR: %s \n", cudaGetErrorString(error));
	}
	cudaMemcpy(pixel_data, output, width * height * sizeof(int), cudaMemcpyDeviceToHost);
	if (output != NULL)
		cudaFree(output);
	if (mem_objects != NULL)
		cudaFree(mem_objects);
	if (mem_lights != NULL)
		cudaFree(mem_lights);
}
