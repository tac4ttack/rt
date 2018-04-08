#include <cuda.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>

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

__host__ __device__ float dot(const float3 a, const float3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

__host__ __device__ float sqrt_magnitude(const float3 a)
{
	return (sqrt(fabs(a.x * a.x) + fabs(a.y * a.y) + fabs(a.z * a.z)));
}

__host__ __device__ float3 normalize(const float3 a)
{
	float3		newv;
	float		ret_magnitude;

	ret_magnitude = sqrt_magnitude(a);
	if (fabs(ret_magnitude) < EPSILONF)
		return (a);
	newv.x = a.x / ret_magnitude;
	newv.y = a.y / ret_magnitude;
	newv.z = a.z / ret_magnitude;
	return (newv);
}

__host__ __device__ float length(const float3 a)
{
	return (fabs((a.x * a.x)) + fabs((a.y * a.y)) + fabs((a.z * a.z)));
}

inline __host__ __device__ float radians(double degree) {
    return (degree * M_PI / 180.0);
}

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

__host__ __device__ float3	get_sphere_abc(const float radius, const float3 ray, const float3 origin)
{
	float3		abc = make_float3(0);

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (radius * radius);
	return (abc);
}


__host__ __device__ t_ret	inter_sphere(const t_sphere *sphere, const float3 ray, const float3 origin)
{
	float3		abc = make_float3(0);
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = make_float3(0);
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	//if (sphere->flags & OBJ_FLAG_PLANE_LIMIT)
	//	return (object_limited((t_object  *)sphere, res1, res2, ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);

}

__host__ __device__ t_hit			ray_hit(const t_scene *scene, const float3 origin, const float3 ray, float lightdist)
{
	t_hit						hit;
	t_object 					*obj;
	int							mem_index_obj;
	t_ret						ret;

	hit = hit_init();
	mem_index_obj = 0;
	obj = 0;
	if (lightdist == 0)
		hit.opacity = 1;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = (t_object *)((char *)scene->mem_obj + mem_index_obj);
		if (obj->type == OBJ_SPHERE)
		 	ret = inter_sphere((struct s_sphere *)obj, ray, origin);
		/*else if (obj->type == OBJ_CYLINDER)
		 	ret = inter_cylinder(( struct s_cylinder *)obj, ray, origin);
		else if (obj->type == OBJ_PLANE)
		 	ret = inter_plan(( struct s_plane *)obj, ray, origin);
		else if (obj->type == OBJ_CONE)
		 	ret = inter_cone(( struct s_cone *)obj, ray, origin);
		else if (obj->type == OBJ_ELLIPSOID)
		   	ret = inter_ellipsoid(( struct s_ellipsoid *)obj, ray, origin);
		else if (obj->type == OBJ_THOR)
			ret = inter_thor(( struct s_thor *)obj, ray, origin);
		if (lightdist > 0 && ret.dist < lightdist && ret.dist > EPSILONF)
			hit.opacity += obj->opacity;*/
		if ((ret.dist < hit.dist || hit.dist == 0) && ret.dist > EPSILONF)
		{
			hit.dist = ret.dist;
			hit.normal = ret.normal;
			hit.wall = ret.wall;
			hit.obj = obj;
			hit.mem_index = mem_index_obj;
/*
			printf("Sphere\nType:%i\nFlags%i\nColor %x\nPos %.2f %.2f %.2f\n\
								Dir %.2f %.2f %.2f\n \
								DIff %.2f %.2f %.2f\n \
								SPec %.2f %.2f %.2f\n \
								",
						obj->type, obj->flags, obj->color,
						obj->pos.x, obj->pos.y, obj->pos.z,
						obj->dir.x, obj->dir.y, obj->dir.z,
						obj->diff.x, obj->diff.y, obj->diff.z,
						obj->spec.x, obj->spec.y, obj->spec.z
						);
						*/
		}
		mem_index_obj += obj->size;
	}
	return (hit);
}

__host__ __device__ float3			get_hit_normal(const t_scene *scene, float3 ray, t_hit hit)
{
	float3				res, save;
	t_object 			*object;

	object = hit.obj;
	res = make_float3(0.f);
	if (hit.wall)
		res = hit.normal;
	else
	{
		if (hit.obj->type == OBJ_SPHERE)
		{
		 	res = hit.pos - hit.obj->pos;
		}
		/*else if (hit.obj->type == OBJ_CYLINDER)
			res = get_cylinder_normal(( t_cylinder *)hit.obj, hit);
		else if (hit.obj->type == OBJ_CONE)
			res = get_cone_normal(( t_cone *)hit.obj, hit);
		else if (hit.obj->type == OBJ_ELLIPSOID)
			res = get_ellipsoid_normal(( t_ellipsoid *)hit.obj, &hit);
		else if (hit.obj->type == OBJ_THOR)
			res = get_thor_normal(( t_thor *)hit.obj, hit.pos);*/
		else if (hit.obj->type == OBJ_PLANE)
		{
			save = ray * -1;
			if (dot(hit.obj->dir, save) < 0)
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

__host__ __device__  unsigned int			phong(const  t_scene *scene, const t_hit hit, const float3 ray)
{
	float3					reflect, diffuse, speculos;
	float					tmp, brightness, pow_of_spec;
	unsigned int  			col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g, hue_light, hue, res_color;
	int						mem_index_lights, light_color;
	t_object 				*obj;
	t_light 				*light;
	t_light_ray				light_ray;
	t_hit					light_hit;


	tmp = 0;
	reflect = make_float3(0.f);
	speculos = make_float3(0.f);
	diffuse = make_float3(0.f);
	brightness = 0;
	hue_light = 0;
	pow_of_spec = 0;
	light_color = 0;
	mem_index_lights = 0;

	obj = hit.obj;
	/*if ((hit.obj->flags & OBJ_FLAG_CHECKERED) || hit.obj->flags & OBJ_FLAG_DIFF_MAP)
		hue = hit.color;
	else*/
		hue = obj->color;
//	printf("%x\n", hue);
//	return (obj->color);

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
			if (tmp > EPSILONF)
			{
				brightness = (float )light->brightness;
				diffuse = (float3 )obj->diff;
				hue_light = light->color;
				//printf("%.f %.2f %.2f %.2f %x\n", brightness, diffuse.x, diffuse.y, diffuse.z, hue_light);
				col_r = (res_color & 0xFF0000) >> 16;
				col_g = (res_color & 0x00FF00) >> 8;
				col_b = (res_color & 0x0000FF);
				obj_r = (hue & 0xFF0000) >> 16;
				obj_g = (hue & 0x00FF00) >> 8;
				obj_b = (hue & 0x00000FF);
				//printf("%x = %x | %x | %x\n", hue, col_r, col_g, col_b);
				l_r = (hue_light & 0xFF0000) >> 16;
				l_g = (hue_light & 0x00FF00) >> 8;
				l_b = (hue_light & 0x0000FF);
				col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				//printf("%x\n", hue);
/*
				printf("%x == l_r ([%x] * [%.2f] + %x) * [%.2f] * %.2f\n%x == l_g ([%x] * [%.2f] + %x) * [%.2f] * %.2f\n%x == l_b ([%x] * [%.2f] + %x) * [%.2f] * %.2f\n",
								col_r, l_r, brightness, obj_r, tmp, diffuse.x,
								col_g, l_g, brightness, obj_g, tmp, diffuse.y,
								col_b, l_b, brightness, obj_b, tmp, diffuse.z
							);
*/
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
				printf("%x\n", ((col_r << 16) + (col_g << 8) + col_b));
				return (res_color);
			}
/*
			// specular part
			reflect = normalize(((float)(2.0f * dot(hit.normal, light_ray.dir)) * hit.normal) - light_ray.dir);
			float3 tmp2;
			tmp2.x = -ray.x;
			tmp2.y = -ray.y;
			tmp2.z = -ray.z;
			tmp = dot(reflect, tmp2);
			if (tmp > EPSILONF)
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
	*/
	/*		res_color = blend_factor(res_color, ((light_hit.opacity - 1) * -1));
			if (scene->flag & OPTION_CARTOON_FOUR)
			 	res_color = cartoonize_four(col_r, col_g, col_b);
			else if (scene->flag & OPTION_CARTOON_TWO)
			 	res_color = cartoonize_two(col_r, col_g, col_b);
		*/
		}
		mem_index_lights += light->size;
	}
	return (res_color);
}

__host__ __device__ unsigned int	get_pixel_color(const t_scene *scene, float3 ray, int *target, bool isHim)
{
	t_hit			hit;
	int				depth;
	unsigned int	color;
	unsigned int	bounce_color;

	hit = hit_init();
	hit.dist = MAX_DIST;
	depth = scene->depth;
	color = 0x00FF0F0F;
	bounce_color = 0;
	hit = ray_hit(scene, (ACTIVECAM.pos), ray, 0);
	if ((isHim == 1) && (hit.obj != NULL))
		*target = hit.mem_index;
	if (hit.dist > EPSILON && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normal = get_hit_normal(scene, ray, hit);
		hit.pos = hit.pos + (0.001f * hit.normal);
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
		//if (((hit.obj->refract != 0 && hit.obj->opacity < 1) || hit.obj->reflex > 0) && depth > 0)
		//	return (fresnel(scene, ray, hit, depth + 1, color));
		//printf("%x\n", color);
		return (color  + 0xFF000000);
		//return (blend_add(color, bounce_color));
	}
	//return (get_ambient(scene, BACKCOLOR));
	return (0xFF0000FF);
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
	final_color = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && x == scene->mou_x && y == scene->mou_y));

/*	if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);
	if (scene->flag & OPTION_INVERT)
		final_color = invert(final_color);*/
/*

	// ALPHA INSERT and RGB SWAP
	int4 swap;
	swap.w = 255;
	swap.x = (final_color & 0x00FF0000) >> 16;
	swap.y = (final_color & 0x0000FF00) >> 8;
	swap.z = (final_color & 0x000000FF);
	final_color = ((swap.w << 24) + (swap.z << 16) + (swap.y << 8) + swap.x);
	((__global unsigned int *)output)[id] = final_color;*/
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
