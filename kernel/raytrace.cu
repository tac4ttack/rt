#include <cuda.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include "ft_maths.hu"


static void HandleError(cudaError_t err, const char *file,	int line)
{
	if (err != cudaSuccess)
	{
		printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
		cudaDeviceReset();
		// exit( EXIT_FAILURE );
	}
}
#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__))


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
# define OBJ_KUBE					9

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


typedef struct			s_cam
{
	unsigned int		id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
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
	float				_align0;
	float3				dir;
	float				_align1;
	int					shrink;
	float				brightness;
	int					color;
}						t_light;

typedef struct			s_object
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;
}						t_object;

typedef struct			s_cone
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	float				angle;
	float3				u_axis;
	float				_align13;
}						t_cone;

typedef struct			s_cylinder
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	float3				base_dir;
	float				_align13;
	float				radius;
	float3				u_axis;
	float				_align14;
}						t_cylinder;

typedef struct			s_plane
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				normal;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	float				radius;
	float3				u_axis;
	float				_align13;
}						t_plane;

typedef struct			s_sphere
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	float				radius;
}						t_sphere;

typedef struct			s_ellipsoid
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	float				radius;
	float3				axis_size;
	float				_align13;
}						t_ellipsoid;

typedef struct			s_thor
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	double				lil_radius;
	double				big_radius;
}						t_thor;

typedef struct			s_kube
{
	int					size;
	int					type;
	int					flags;
	int					id;
	float3				pos;
	float				_align0;
	float3				dir;
	float				_align1;
	float3				diff;
	float				_align2;
	float3				spec;
	float				_align3;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	float3				limit_pos;
	float				_align4;
	float3				limit_dir;
	float				_align5;
	float3				waves_p1;
	float				_align6;
	float3				waves_p2;
	float				_align7;
	float3				check_size;
	float				_align8;
	int					diff_map_id;
	float3				diff_offset;
	float				_align9;
	float3				diff_ratio;
	float				_align10;
	float3				cut_min;
	float				_align11;
	float3				cut_max;
	float				_align12;

	double				option;
}						t_kube;

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
	float				ratio;
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
	t_object 			*obj;
	int					mem_index;
	float				opacity;
	unsigned int		color;
	int					wall;
	int					lock;
}						t_hit;

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
	float				_align0;
	unsigned int		mou_x;
	unsigned int		mou_y;
	unsigned int		depth;
	float				u_time;
	int					flag;
	unsigned int		over_sampling;
	unsigned int		mem_size_obj;
	unsigned int		mem_size_lights;
	t_cam				*cameras;
	void				*mem_lights;
	void				*mem_obj;
	unsigned int		*texture_earth;
	unsigned int		*texture_moon;
	unsigned int		*texture_earth_cloud;
	unsigned int		*texture_star;
}						t_scene;

typedef struct			s_cuda
{
	size_t				nb_mem;
	void				**mem;
	bool				(*add_buffer)(struct s_cuda *, size_t);
	bool				(*update_buffer)(struct s_cuda *, size_t);
}						t_cuda;

typedef struct			s_tex
{
	unsigned int		*pixel_array;
	int					width;
	int					height;
}						t_tex;


// OCL TO CUDA -> need tests
__device__ unsigned int	skybox(float3 dir, unsigned int *texture, int t_width, int t_height)
{
	unsigned int	color = 0;
	int2			uv = make_int2(0);

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

// OCL TO CUDA -> OK
inline __device__ float radians(double degree) {
  return (degree * M_PI / 180.f);
}

// OCL TO CUDA -> need tests
__device__ float3	vector_get_rotate(float3 *me, float3 *rot)
{
	float3		n = make_float3(0.f);
	float		tmp = 0.f;

	n = *me;
	if (rot->x)
	{
		tmp = n.y * cosf(rot->x) - n.z * sinf(rot->x);
		n.z = n.y * sinf(rot->x) + n.z * cosf(rot->x);
		n.y = tmp;
	}
	if (rot->y)
	{
		tmp = n.x * cosf(rot->y) + n.z * sinf(rot->y);
		n.z = n.x * -sinf(rot->y) + n.z * cosf(rot->y);
		n.x = tmp;
	}
	if (rot->z)
	{
		tmp = n.x * cosf(rot->z) - n.y * sinf(rot->z);
		n.y = n.x * sinf(rot->z) + n.y * cosf(rot->z);
		n.x = tmp;
	}
	return (n);
}

// OCL TO CUDA -> need tests
__device__ float3	vector_get_inverse(float3 *me, float3 *rot)
{
	float3		n = make_float3(0.f);
	float		tmp = 0.f;

	n = *me;
	if (rot->z)
	{
		tmp = n.x * cosf(rot->z) - n.y * -sinf(rot->z);
		n.y = n.x * -sinf(rot->z) + n.y * cosf(rot->z);
		n.x = tmp;
	}
	if (rot->y)
	{
		tmp = n.x * cosf(rot->y) + n.z * -sinf(rot->y);
		n.z = n.x * sinf(rot->y) + n.z * cosf(rot->y);
		n.x = tmp;
	}
	if (rot->x)
	{
		tmp = n.y * cosf(rot->x) - n.z * -sinf(rot->x);
		n.z = n.y * -sinf(rot->x) + n.z * cosf(rot->x);
		n.y = tmp;
	}
	return (n);
}

// OCL TO CUDA -> OK
__device__ t_hit	hit_init(void)
{
	t_hit		hit;

	hit.dist = 0.f;
	hit.normal = make_float3(0.f);
	hit.obj = 0;
	hit.lock = 0;
	hit.wall = 0;
	hit.color = 0;
	hit.pos = make_float3(0.f);
	hit.mem_index = 0;
	hit.opacity = 0;
	return (hit);
}

// OCL TO CUDA -> need tests
__device__ float3	rotat_zyx(float3 vect, float pitch, float yaw, float roll)
{
	float3		res = make_float3(0.f);
	float		rad_pitch = radians(pitch);
	float		rad_yaw = radians(yaw);
	float		rad_roll = radians(roll);

	res.x = vect.x * cosf(rad_roll) * cosf(rad_yaw) + vect.y * (cosf(rad_pitch) * -sinf(rad_roll) + cosf(rad_roll) * sinf(rad_yaw) * sinf(rad_pitch)) + vect.z * (-sinf(rad_roll) * -sinf(rad_pitch) + cosf(rad_roll) * sinf(rad_yaw) * cosf(rad_pitch));
	res.y = vect.x * sinf(rad_roll) * cosf(rad_yaw) + vect.y * (cosf(rad_roll) * cosf(rad_pitch) + sinf(rad_roll) * sinf(rad_yaw) * sinf(rad_pitch)) + vect.z * (cosf(rad_roll) * -sinf(rad_pitch) + sinf(rad_roll) * sinf(rad_yaw) * cosf(rad_pitch));
	res.z = vect.x * -sinf(rad_yaw) + vect.y * cosf(rad_yaw) * sinf(rad_pitch) + vect.z * cosf(rad_yaw) * cosf(rad_pitch);
	return (res);
}

// OCL TO CUDA -> need tests
__device__ float3	rotat_xyz(float3 vect, float pitch, float yaw, float roll)
{
	float3		res = make_float3(0.f);
	float		rad_pitch = radians(pitch);
	float		rad_yaw = radians(yaw);
	float		rad_roll = radians(roll);

	res.x = vect.x * cos(rad_yaw) * cos(rad_roll) + vect.y * cos(rad_yaw) * -sin(rad_roll) + vect.z * sin(rad_yaw);
	res.y = vect.x * (-sin(rad_pitch) * -sin(rad_yaw) * cos(rad_roll) + cos(rad_pitch) * sin(rad_roll)) + vect.y * (-sin(rad_pitch) * -sin(rad_yaw) * -sin(rad_roll) + cos(rad_pitch) * cos(rad_roll)) + vect.z * cos(rad_yaw) * -sin(rad_pitch);
	res.z = vect.x * (cos(rad_pitch) * -sin(rad_yaw) * cos(rad_roll) + sin(rad_pitch) * sin(rad_roll)) + vect.y * (cos(rad_pitch) * -sin(rad_yaw) * -sin(rad_roll) + sin(rad_pitch) * cos(rad_roll)) + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (res);
}

// OCL TO CUDA -> need tests
__device__ float3	rotat_x(float3 vect, float angle)
{
	float3 		res = make_float3(0.f);
	float		teta = radians(angle);

	res.x = (vect.x * 1.f) + (vect.y * 0.f) + (vect.z * 0.f);
	res.y = (vect.x * 0.f) + (vect.y * cos(teta)) + (vect.z * -sin(teta));
	res.z = (vect.x * 0.f) + (vect.y * sin(teta)) + (vect.z * cos(teta));
	return (res);
}

// OCL TO CUDA -> need tests
__device__ float3	rotat_y(float3 vect, float angle)
{
	float3 		res = make_float3(0.f);
	float		teta = radians(angle);

	res.x = (vect.x * cos(teta)) + (vect.y * 0.f) + (vect.z * sin(teta));
	res.y = (vect.x * 0.f) + (vect.y * 1) + (vect.z * 0.f);
	res.z = (vect.x * -sin(teta)) + (vect.y * 0.f) + (vect.z * cos(teta));
	return (res);
}

// OCL TO CUDA -> need tests
__device__ float3	rotat_z(float3 vect, float angle)
{
	float3 		res = make_float3(0.f);
	float		teta = radians(angle);

	res.x = (vect.x * cos(teta)) + (vect.y * -sin(teta)) + (vect.z * 0.f);
	res.y = (vect.x * sin(teta)) + (vect.y * cos(teta)) + (vect.z * 0.f);
	res.z = (vect.x * 0.f) + (vect.y * 0.f) + (vect.z * 1.f);
	return (res);
}



// OCL TO CUDA -> need tests (is unused in kernel)
__device__ unsigned int	blend_multiply(unsigned int c1, unsigned int c2)
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

// OCL TO CUDA -> need tests in use
__device__ unsigned int	blend_med(unsigned int c1, unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	r = (r1 + r2) / 2;
	g = (g1 + g2) / 2;
	b = (b1 + b2) / 2;
	return ((r << 16) + (g << 8) + b);
}

// OCL TO CUDA -> OK
__device__ unsigned int	blend_add(unsigned int c1, unsigned int c2)
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

// OCL TO CUDA -> OK
__device__ unsigned int	blend_factor(unsigned int c1, float factor)
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

// OCL TO CUDA -> OK
__device__ unsigned int	get_ambient(t_scene *scene, unsigned int obj_color)
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

// OCL TO CUDA -> OK
__device__ unsigned int	sepiarize(unsigned int color)
{
	uint3	base, cooking_pot = make_uint3(0, 0, 0);
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

// OCL TO CUDA -> OK
__device__ unsigned int	invert(unsigned int color)
{
	uint3	base = make_uint3(0, 0, 0);
	base.x = (color & 0x00FF0000) >> 16;
	base.y = (color & 0x0000FF00) >> 8;
	base.z = (color & 0x000000FF);
	base.x = 255 - base.x;
	base.y = 255 - base.y;
	base.z = 255 - base.z;
	return (((uint)base.x << 16) + ((uint)base.y << 8) + (uint)base.z);
}

// OCL TO CUDA -> OK
__device__ unsigned int	desaturate(unsigned int color)
{
	uint3	rgb = make_uint3(0, 0, 0);
	rgb.x = (color & 0x00FF0000) >> 16;
	rgb.y = (color & 0x0000FF00) >> 8;
	rgb.z = (color & 0x000000FF);
	float 	average = (rgb.x + rgb.y + rgb.z) / 3;
	return (((uint)average << 16) + ((uint)average << 8) + (uint)average);
}

// OCL TO CUDA -> OK
__device__ unsigned int cartoonize_four(unsigned int col_r, unsigned int col_g, unsigned int col_b)
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

// OCL TO CUDA -> OK
__device__ unsigned int cartoonize_two(unsigned int col_r, unsigned int col_g, unsigned int col_b)
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

// OCL TO CUDA -> need tests
__device__ float	inter_plan_private(t_plane *plane, float3 ray, float3 origin)
{
	float		t = 0.f;

	t = dot(normalize(ray), plane->normal);
	if (fabs(t) < EPSILONF|| (plane->radius && t > plane->radius))
		return (0.f);
	t = (dot(plane->pos - origin, plane->normal)) / t;
	if (t < EPSILONF)
		return (0.f);
	return (t);
}

// OCL TO CUDA -> need tests
__device__ t_ret	object_limited(t_object *object,
							float res1, float res2,
							float3 ray, float3 origin)
{
	t_ret		ret;
	t_plane		t;
	float		dist_plan = 0.f;

	ret.dist = 0.f;
	ret.wall = 0.f;
	ret.normal = make_float3(0.f);
	t.pos = object->limit_pos;
	t.normal = object->limit_dir;
	t.radius = 0.f;
	dist_plan = inter_plan_private(&t, ray, origin);

	// IN OBJECT
	if (res1 < EPSILONF)
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

// OCL TO CUDA -> need tests
__device__ unsigned int	plane_checkerboard(float3 normale, float3 pos, unsigned int color, float3 check_size)
{
	float3			u_axis = make_float3(0.f);
	float3			v_axis = make_float3(0.f);
	int2			uv = make_int2(0);

	u_axis.x = normale.y;
	u_axis.y = normale.z;
	u_axis.z = -normale.x;
	v_axis = cross(u_axis, normale);
	uv.x = (int)(floor(dot(pos, u_axis) / check_size.x));
	uv.y = (int)(floor(dot(pos, v_axis) / check_size.y));
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


// OCL TO CUDA -> need tests
__device__ unsigned int		plane_texture(float3 normale, float3 pos, float3 u_axis, float3 ratio, float3 offset, unsigned int *texture, int width, int height)
{
	float3			v_axis = make_float3(0.f);
	int2			uv = make_int2(0);

	v_axis = cross(u_axis, normale);
	uv.x = (int)(floor(dot(pos, u_axis) * ratio.x + offset.x));
	uv.y = (int)(floor(dot(pos, v_axis) * ratio.y + offset.y));
	uv.x %= width - 1;
	uv.y %= height - 1;
	if (uv.x < 0)
		uv.x = (uv.x + width - 1);
	if (uv.y < 0)
		uv.y = (uv.y + height - 1);
	uv.x %= width - 1;
	uv.y %= height - 1;
	return (texture[uv.y + uv.x * width]);
}

// OCL TO CUDA -> OK
__device__ bool		solve_quadratic(float a, float b, float c, float *inter0, float *inter1)
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

// OCL TO CUDA -> need tests in use 
__device__ double3	thor_get_rotate(double3 *that, float3 *rot)
{
	double3		n = make_double3(0.f);
	float		tmp = 0.f;

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

// OCL TO CUDA -> need tests in use
__device__ double	ft_ret(double *tab)
{
	double		ret = -1.0f;
	int			i = 0;

	while(i < 4)
	{
		if(tab[i] > EPSILON && ret == -1)
			ret = tab[i];
			if (tab[i] < ret && tab[i] > EPSILON )
			ret = tab[i];
		i++;
	}
	if (ret == -1.0f)
		ret = 0.f;
	return (ret);
}

// OCL TO CUDA -> need tests in use
__device__ double3	ft_solve_3(double a, double b, double c, double d)
{
	double		a1 = 0.f;
	double		a2 = 0.f;
	double		a3 = 0.f;
	double3		Result = make_double3(0.f);
	double		theta = 0.f;
	double		sqrtQ = 0.f;
	double		e = 0.f;
	double		Q = 0.f;
	double		R = 0.f;
	double		Qcubed = 0.f;

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
			Result.x = 0.f;
			Result.y = 0.f;
			Result.z = 0.f;
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

// OCL TO CUDA -> need tests in use
__device__ double	ft_solve_4(double t[5])
{
	double		Result[4] = {0.f};
	double3		Roots = make_double3(0.f);
	double		Rsquare = 0;
	double		Rrec = 0;
	double		D = 0;
	double		E = 0;
	double3		b = make_double3(0.f);
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
		return (0.f);
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
	Result[2] = -0.25f * a3 - 0.5f * R + 0.5f * E;
	Result[3] = -0.25f * a3 - 0.5f * R - 0.5f * E;
	return(ft_ret(Result));
}


// OCL TO CUDA -> need tests in use 
__device__ t_ret		inter_thor(t_thor *thor, float3 ray, float3 origin)
{
	t_ret			ret;
	ret.dist = 0.f;
	ret.normal = make_float3(0.f);
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

// OCL TO CUDA -> need tests in use 
__device__ float3 get_thor_normal(t_thor *thor, float3 hitpos)
{
	float3	res = make_float3(0.f);
	float	c = 0.f;

	float	R = (float)((thor->lil_radius * thor->lil_radius));
	float	r = (float)((thor->big_radius * thor->big_radius));

	float3 pos = hitpos - thor->pos;
	pos = vector_get_rotate(&pos, &thor->dir);

	c = ((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z) - r - R);

	res.x = 4.0f * c * pos.x;
	res.y = 4.0f * pos.y * (c + 2 * r);
	res.z = 4.0f * c * pos.z;

	res = vector_get_inverse(&res, &thor->dir);
	return (res);
}

__device__ t_ret		inter_kube(t_kube *kube, float3 ray, float3 origin)
{
	t_ret		ret;
	ret.dist = 0;
	ret.normal = make_float3(0.f);
	ret.wall = 0;

	double3		d_ray;
	d_ray.x = (double)ray.x;
	d_ray.y = (double)ray.y;
	d_ray.z = (double)ray.z;
	d_ray = thor_get_rotate(&d_ray, &kube->dir);

	double3		d_dir;
	d_dir.x = (double)origin.x - (double)kube->pos.x;
	d_dir.y = (double)origin.y - (double)kube->pos.y;
	d_dir.z = (double)origin.z - (double)kube->pos.z;
	d_dir = thor_get_rotate(&d_dir, &kube->dir);

	double		c[5];
	c[4] = (pow(d_ray.x, 4.0f) + pow(d_ray.y, 4.0f) + pow(d_ray.z, 4.0f));
	c[3] = 4.0f * ((pow(d_ray.x, 3.0f) * d_dir.x) + (pow(d_ray.y, 3.0f) * d_dir.y)+ (pow(d_ray.z, 3.0f) * d_dir.z));
	c[2] = 6.0f * ((pow(d_ray.x, 2.0f) * pow(d_dir.x, 2.0f) + pow(d_ray.y, 2.0f) * pow(d_dir.y, 2.0f) + pow(d_ray.z, 2.0f) * pow(d_dir.z, 2.0f))) - 5.0 * (pow(d_ray.x, 2.0f) + pow(d_ray.y, 2.0f) + pow(d_ray.z, 2.0f));
	c[1] = 4.0f * (pow(d_dir.x, 3.0f) * d_ray.x + pow(d_dir.y, 3.0f) * d_ray.y + pow(d_dir.z, 3.0f) * d_ray.z) - 10.0 * (d_dir.x * d_ray.x + d_dir.y * d_ray.y + d_dir.z * d_ray.z);
	c[0] = (pow(d_dir.x, 4.0f) + pow(d_dir.y, 4.0f) + pow(d_dir.z, 4.0f)) - 5.0 * (d_dir.x * d_dir.x + d_dir.y * d_dir.y +d_dir.z * d_dir.z) + kube->option;

	ret.dist = ft_solve_4(c);
	return (ret);
}

// KUBE
__device__ float3 get_kube_normal(t_kube *kube, float3 hitpos)
{
	float3 pos = hitpos - kube->pos;
	pos = vector_get_rotate(&pos, &kube->dir);
	float3  res = make_float3(0.f);

     res.x = 4.0f * powf(pos.x, 3.0f) - 10.0 * pos.x;
     res.y = 4.0f * powf(pos.y, 3.0f) - 10.0 * pos.y;
     res.z = 4.0f * powf(pos.z, 3.0f) - 10.0 * pos.z;

	 res = vector_get_inverse(&res, &kube->dir);
	 return (res);
}


// OCL TO CUDA -> need tests in use (earth texture missing)
__device__ unsigned int		sphere_texture(float3 pos, unsigned int *texture, int t_width, int t_height, float3 ratio, float3 offset)
{
	unsigned int	color = 0;
	int3			uv = make_int3(0);
	int3			size = make_int3(0);

	size.x = (int)(floor(t_width * ratio.x));
	size.y = (int)(floor(t_height * ratio.y));
	uv.x = (int)(floor((0.5 + (atan2(pos.z, pos.x) / (2 * M_PI))) * size.x + offset.x));
	uv.y = (int)(floor((0.5 - (asin(pos.y) / M_PI)) * size.y + offset.y));
	if (uv.x < 0)
	{
		uv.x %= t_width;
		uv.x = (uv.x - t_width) * -1;
	}
	else
		uv.x %= t_width;
	if (uv.y < 0)
		uv.y %= t_height;
	else
	{
		uv.y %= t_height;
		uv.y = (uv.y - t_height) * -1;
	}
	color = texture[uv.x + uv.y * t_width];
	return (color);
}

// OCL TO CUDA -> need tests
__device__ t_ret	sphere_cut(t_sphere *sphere, float3 ray, float3 origin, float res1, float res2)
{
	t_ret		ret;
	float3		pt_i1 = make_float3(0.f);
	float3		pt_i2 = make_float3(0.f);
	float3		bord1 = make_float3(0.f);
	float3		bord2 = make_float3(0.f);
	ret.dist = 0;
	ret.wall = 0;
	ret.normal = make_float3(0.f);

	bord1.x = sphere->pos.x + sphere->radius;    
	bord2.x = sphere->pos.x - sphere->radius;	  	
	bord1.y = sphere->pos.y + sphere->radius;		
	bord2.y = sphere->pos.y - sphere->radius;		
	bord1.z = sphere->pos.z + sphere->radius;		
	bord2.z = sphere->pos.z - sphere->radius;	

	pt_i1.x = origin.x + ray.x * res1;
	pt_i1.y = origin.y + ray.y * res1;
	pt_i1.z = origin.z + ray.z * res1;

	pt_i2.x = origin.x + ray.x * res2;
	pt_i2.y = origin.y + ray.y * res2;
	pt_i2.z = origin.z + ray.z * res2;
	
	if (pt_i1.x <= 	bord1.x - sphere->cut_max.x && pt_i1.y <= bord1.y - sphere->cut_max.y && pt_i1.z <= bord1.z - sphere->cut_max.z && pt_i1.x >= bord2.x + sphere->cut_min.x && pt_i1.y >= bord2.y + sphere->cut_min.y && pt_i1.z >= bord2.z + sphere->cut_min.z)
	{
		ret.dist = res1;
	}
	else if (pt_i2.x <= bord1.x - sphere->cut_max.x && pt_i2.y <= bord1.y - sphere->cut_max.y && pt_i2.z <= bord1.z - sphere->cut_max.z && pt_i2.x >= bord2.x + sphere->cut_min.x && pt_i2.y >= bord2.y + sphere->cut_min.y && pt_i2.z >= bord2.z + sphere->cut_min.z) 
	{
		ret.dist = res2;
	}
	return (ret);
}

// OCL TO CUDA -> OK
__device__ unsigned int		sphere_checkerboard(float3 dir, unsigned int color, float3 check_size)
{
	int2	uv = make_int2(0);

	uv.x = (int)(floor((0.5 + (atan2(dir.z, dir.x) / (2 * 3.1415))) * check_size.x));
	uv.y = (int)(floor((0.5 - (asin(dir.y) / 3.1415)) * check_size.y));
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

// OCL TO CUDA -> OK
__device__ float3	get_sphere_abc(float radius, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (radius * radius);
	return (abc);
}

__device__ t_ret	mini_inter_sphere(t_sphere *sphere, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);
	float		res1 = 0.f;
	float		res2 = 0.f;
	float3		pos = make_float3(0.f);
	t_ret		ret;

	ret.dist = 0.f;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	else
	{
		if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
			ret.dist = res1;
		else
			ret.dist = res2;
	}
	return (ret);
}


// OCL TO CUDA -> decoupe noe a test
__device__ t_ret	inter_sphere(t_sphere *sphere, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);
	float		res1 = 0.f;
	float		res2 = 0.f;
	float3		pos = make_float3(0.f);
	t_ret		ret;

	ret.dist = 0.f;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	if (sphere->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object *)sphere, res1, res2, ray, origin));
	else
	{
		if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
			ret.dist = res1;
		else
			ret.dist = res2;
	}
	if (sphere->flags & OBJ_FLAG_CUT)
		return(sphere_cut(sphere, ray, origin, res1, res2));
	return (ret);
}

// OCL TO CUDA -> OK
__device__ float3	get_cylinder_normal(t_cylinder *cylinder, t_hit hit)
{
	float3		res = make_float3(0.f);
	float3		v = make_float3(0.f);;
	float3		project = make_float3(0.f);;
	float		doty = 0.f;

	v = hit.pos - cylinder->pos;
	doty = dot(v, cylinder->dir);
	project = doty * cylinder->dir;
	res = v - project;
	return (normalize(res));
}

// OCL TO CUDA -> OK
__device__ float3	get_cylinder_abc(float radius, float3 dir, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);

	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

// OCL TO CUDA -> need test avec la decoupe de Noe
__device__ t_ret	inter_cylinder(t_cylinder *cylinder, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);
	float3		pos = make_float3(0.f);
	float		res1 = 0.f;
	float		res2 = 0.f;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
	pos = origin - cylinder->pos;
	abc = get_cylinder_abc(cylinder->radius, cylinder->dir, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	if (cylinder->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object *)cylinder, res1, res2, ray, origin));
	else
	{
		if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
			ret.dist = res1;
		else
			ret.dist = res2;
	}
	// if (cylinder->flags & OBJ_FLAG_CUT)
	// 	return(sphere_cut(cylinder, ray, origin, res1, res2));
	return (ret);
}

// OCL TO CUDA -> need test avec la decoupe de Noe
__device__ t_ret	inter_plan(t_plane *plane, float3 ray, float3 origin)
{
	float		t = 0.f;
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
	t = dot(normalize(ray), plane->normal);
	if (fabsf(t) < EPSILONF || (plane->radius && t > plane->radius))
		return (ret);
	t = (dot(plane->pos - origin, plane->normal)) / t;
	if (t < EPSILONF)
		return (ret);
	if (plane->radius)
	{
		float3 p = origin + ray * t;
		float3 v = p - plane->pos;
		float d2 = dot(v, v);
		if (sqrtf(d2) > plane->radius)
			return (ret);
	}
	if (plane->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object *)plane, t, t, ray, origin));
	ret.dist = t;
	return (ret);
}

// OCL TO CUDA -> need test
__device__ float3		get_ellipsoid_normal(t_ellipsoid *ellipsoid, t_hit *hit)
{
	float3 pos = hit->pos - ellipsoid->pos;
	pos = vector_get_rotate(&pos, &ellipsoid->dir);

	float3 res = make_float3(0.f);

	res.x = (pos.x) / (ellipsoid->axis_size.x * ellipsoid->axis_size.x);
	res.y = (pos.y) / (ellipsoid->axis_size.y * ellipsoid->axis_size.y);
	res.z = (pos.z) / (ellipsoid->axis_size.z * ellipsoid->axis_size.z);
	res = vector_get_inverse(&res, &ellipsoid->dir);
	return (res);
}

// OCL TO CUDA -> need test avec la decoupe de Noe
__device__ t_ret	inter_ellipsoid(t_ellipsoid *ellipsoid, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);
	float		res1, res2 = 0.f;
	float3		pos = make_float3(0.f);
	float3		save_ray = make_float3(0.f);
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
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
	if (ellipsoid->flags & OBJ_FLAG_PLANE_LIMIT)
		return (object_limited((t_object *)ellipsoid, res1, res2, save_ray, origin));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}

// OCL TO CUDA -> need test
__device__ float3	get_cone_normal(t_cone *cone, t_hit hit)
{
	float3		res = make_float3(0.f);
	float3		v = make_float3(0.f);
	float3		project = make_float3(0.f);
	float		doty = 0.f;

	v = hit.pos - cone->pos;
	doty = dot(v, cone->dir);
	project = doty * cone->dir;
	res = v - project;

	return (normalize(res));
}

// OCL TO CUDA -> need test
__device__ float3	get_cone_abc(t_cone *cone, float3 ray, float3 origin)
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

// OCL TO CUDA -> need test avec decoupe Noe
__device__ t_ret	inter_cone(t_cone *cone, float3 ray, float3 origin)
{
	float3		abc = make_float3(0.f);
	float		res1 = 0.f;
	float		res2 = 0.f;
	float3		pos = make_float3(0.f);
	t_ret		ret;

	ret.dist = 0;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
	pos = origin - cone->pos;
	abc = get_cone_abc(cone, ray, pos);
	if (!solve_quadratic(abc.x, abc.y, abc.z, &res1, &res2))
		return (ret);
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		ret.dist = res1;
	else
		ret.dist = res2;
	return (ret);
}

// OCL TO CUDA -> need test
__device__ unsigned int		cone_texture(float3 pos, float3 dir, float3 u_axis, unsigned int *texture, int t_width, int t_height, float3 ratio, float3 offset)
{
	unsigned int	color = 0;
	float3			v_axis = make_float3(0.f);
	float			npos = 0.f;
	float			vpos = 0.f;
	int2			uv = make_int2(0);

	v_axis = cross(u_axis, dir);
	npos = dot(pos, dir);
	while (npos > 10)
		npos -= 10;
	while (npos < 0)
		npos += 10;
	uv.y = (int)(floor((length(npos * dir) / 10) * ratio.y * (t_height - 1) + offset.y));
	npos = dot(pos, u_axis);
	vpos = dot(pos, v_axis);
	uv.x = (int)(floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * ratio.x * (t_width - 1) + offset.x));
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


// OCL TO CUDA -> need test
__device__ t_hit		ray_hit(t_scene *scene, float3 origin, float3 ray, float lightdist)
{
	t_hit						hit;
	t_object 					*obj;
	unsigned int				mem_index_obj = 0;
	t_ret						ret;

	hit = hit_init();
	obj = 0;
	ret.dist = 0.f;
	ret.wall = 0;
	ret.normal = make_float3(0.f);
	if (lightdist == 0)
		hit.opacity = 1;
	while (mem_index_obj < scene->mem_size_obj)
	{
		obj = (t_object *)((char *)scene->mem_obj + mem_index_obj);
		if (obj->type == OBJ_SPHERE)
		 	ret = inter_sphere((struct s_sphere *)obj, ray, origin);
		else if (obj->type == OBJ_CYLINDER)
		 	ret = inter_cylinder((struct s_cylinder *)obj, ray, origin);
		else if (obj->type == OBJ_PLANE)
		 	ret = inter_plan((struct s_plane *)obj, ray, origin);
		else if (obj->type == OBJ_CONE)
		 	ret = inter_cone((struct s_cone *)obj, ray, origin);
		else if (obj->type == OBJ_ELLIPSOID)
		   	ret = inter_ellipsoid((struct s_ellipsoid *)obj, ray, origin);
		else if (obj->type == OBJ_THOR)
			ret = inter_thor((struct s_thor *)obj, ray, origin);
		else if (obj->type == OBJ_KUBE)
			ret = inter_kube((struct s_kube *)obj, ray, origin);
		if (lightdist > 0 && ret.dist < lightdist && ret.dist > EPSILON)
			hit.opacity += obj->opacity;
		if ((ret.dist < hit.dist || hit.dist == 0) && ret.dist > EPSILON)
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

// OCL TO CUDA -> need test
__device__ float3		get_hit_normal(t_scene *scene, float3 ray, t_hit hit)
{
	float3						res, save = make_float3(0.f);
	t_object 					*object;

	object = hit.obj;
	res = make_float3(0.f);
	if (hit.wall)
		res = hit.normal;
	else
	{
		if (hit.obj->type == OBJ_SPHERE)
		{ 
			if (hit.obj->flags & OBJ_FLAG_CUT)
			{
				t_ret tmp  = mini_inter_sphere((t_sphere*)hit.obj, ray, ACTIVECAM.pos);
				if (tmp.dist < hit.dist)
					res = hit.obj->pos - hit.pos;
				else
					res = hit.pos - hit.obj->pos;
			}
			else
				res = hit.pos - hit.obj->pos;
		}
		else if (hit.obj->type == OBJ_CYLINDER)
			res = get_cylinder_normal((t_cylinder *)hit.obj, hit);
		else if (hit.obj->type == OBJ_CONE)
			res = get_cone_normal((t_cone *)hit.obj, hit);
		else if (hit.obj->type == OBJ_ELLIPSOID)
			res = get_ellipsoid_normal(( t_ellipsoid *)hit.obj, &hit);
		else if (hit.obj->type == OBJ_THOR)
			res = get_thor_normal((t_thor *)hit.obj, hit.pos);
		else if (hit.obj->type == OBJ_KUBE)
			res = get_kube_normal((t_kube *)hit.obj, hit.pos);
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
			save.y = res.y + object->waves_p1.x * sinf((hit.pos.x + scene->u_time));
		// no sinwave with torus
		else if (object->type == OBJ_THOR)
		{
			save.x = res.x + object->waves_p1.x * 100 * sinf(res.y * object->waves_p2.x + scene->u_time);
			save.z = res.z + object->waves_p1.y * 100 * sinf(res.x * object->waves_p2.y + scene->u_time);
			save.y = res.y + object->waves_p1.z * 100 * sinf(res.x * object->waves_p2.z + scene->u_time);
		}
		else
		{
			save.x = res.x + object->waves_p1.x * sinf(res.y * object->waves_p2.x + scene->u_time);
			save.z = res.z + object->waves_p1.y * sinf(res.x * object->waves_p2.y + scene->u_time);
			save.y = res.y + object->waves_p1.z * sinf(res.x * object->waves_p2.z + scene->u_time);
		}
	}

	return (normalize(save));
}

// OCL TO CUDA -> need test
__device__ unsigned int		cylinder_texture(float3 pos, t_cylinder *cyl, unsigned int *texture, int t_width, int t_height)
{
	unsigned int	color = 0;
	float3			v_axis = make_float3(0.f);
	float			npos = 0;
	float			vpos = 0;
	int2			uv = make_int2(0);

	v_axis = cross(cyl->u_axis, cyl->dir);
	npos = length(dot(pos, cyl->dir) * cyl->dir);
	while (npos > 10)
		npos -= 10;
	if (dot(pos, cyl->dir) < 0)
		npos = (npos - 10) * -1;
	uv.y = (int)(floor((npos / 10) * t_height * cyl->diff_ratio.y + cyl->diff_offset.y));
	npos = dot(pos, cyl->u_axis);
	vpos = dot(pos, v_axis);
	uv.x = (int)(floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * t_width * cyl->diff_ratio.x + cyl->diff_offset.x));
	uv.x %= t_width;
	uv.y %= t_height;
	if (uv.x < 0)
		uv.x = uv.x + t_width;
	if (uv.y < 0)
		uv.y = -uv.y;
	else
		uv.y = (uv.y - t_height) * -1;
	uv.x %= t_width;
	uv.y %= t_height;
	color = (unsigned int)texture[uv.x + (uv.y * t_width)];
	return (color);
}

// OCL TO CUDA -> need test
__device__ unsigned int			phong(t_scene *scene, t_hit hit, float3 ray)
{
	t_object 			*obj;
	t_light 			*light;
	unsigned int		mem_index_lights = 0;

	unsigned int		res_color = 0;
	float				tmp = 0.f;
	float3				reflect = make_float3(0.f);
	float3 				diffuse = make_float3(0.f);
	float 				brightness = 0.f;
	unsigned int 		hue = 0;
	unsigned int 		hue_light = 0;
	unsigned int 		col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g = 0;
	t_light_ray			light_ray;
	t_hit				light_hit;
	float 				pow_of_spec = 0.f;
	int 				light_color = 0;
	float3 			speculos = make_float3(0.f);

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
			reflect = normalize(((float)(2.0f * dot(hit.normal, light_ray.dir)) * hit.normal) - light_ray.dir);
			tmp = dot(reflect, ray * -1);
			if (tmp > EPSILON)
			{
				speculos = obj->spec;
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = powf(tmp, (light->shrink));
				light_color = light->color;

				col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
				col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;

				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);

				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}


			// opacite de l'ombre à debug!!!!!
			res_color = blend_factor(res_color, ((light_hit.opacity - 1) * -1));
			// res_color = blend_factor(res_color, 1 - (light_hit.opacity / 2));
	
			// si pas de depth alors opacity = 0, la couleur n'est pas touchée
			// res_color = blend_factor(res_color, 1 - (light_hit.opacity * light_hit.opacity));
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

// OCL TO CUDA -> need test
__device__ float		reflect_ratio(float n1, float n2, float cos1, float sint)
{
	float			fr1 = 0.f;
	float			fr2 = 0.f;
	float			cos2 = sqrtf(1 - sint * sint);

	if (cos1 >= 0)
	{
		fr1 = n1;
		n1 = n2;
		n2 = fr1;
	}
	else
		cos1 = -cos1;
	if (n1 / n2 * sqrtf(1 - cos1 * cos1) > 1)
		return (1);
	fr1 = (n2 * cos1 - n1 * cos2) / (n2 * cos1 + n1 * cos2);
	fr2 = (n1 * cos2 - n2 * cos1) / (n1 * cos2 + n2 * cos1);
	fr1 *= fr1;
	fr2 *= fr2;
	return ((fr1 + fr2) / 2);
}

// OCL TO CUDA -> need test
__device__ float3		refract_ray(t_scene *scene, float3 ray, float3 normale, float tra)
{
	float3			refract = make_float3(0.f);
	float			c1 = 0.f;
	float			c2 = 0.f;
	float			eta = 0.f;

	c1 = dot(normale, ray);
	eta = 1 / tra;
	if (c1 < 0)
		c1 = -c1;
	else
	{
		normale = -normale;
		eta = tra;
	}
	c2 = sqrtf(1 - ((eta * eta) * (1 - (c1 * c1))));
	// DEUXIEME LOIS DE SNELL-DECARTES /////////////////////////////////////////////
	refract = normalize((eta * ray) + ((eta * c1) - c2) * normale);
	////////////////////////////////////////////////////////////////////////////////
	return (refract);
}

__device__ float3		bounce_ray(t_scene *scene, float3 ray, t_tor tor)
{
	float3			reflex;

	reflex = make_float3(0.f);
	// PREMIÈRE LOI DE SNELL-DESCARTES ///////////////////////////////////////////////////////////
	reflex = normalize(ray - (2 * (float)dot(tor.normale, ray) * tor.normale));
	//////////////////////////////////////////////////////////////////////////////////////////////
	return (reflex);
}

// OCL TO CUDA -> need test
__device__ int			tor_height(int i)
{
	int				h = 0;

	while ((i = (i - 1) / 2) >= 0)
		h++;
	return (h);
}

// OCL TO CUDA -> need test
__device__ unsigned int	tor_final_color(t_tor *tor)
{
	int				i = 31;
	unsigned int	color = 0;

	while (i > 0)
	{
		if (tor[i].activate == 0 || (tor[(2 * i) + 2].activate == 0 && tor[(2 * i) + 1].activate == 0))
			;
		else
		{
			color = blend_add(blend_factor(tor[(2 * i) + 2].color, tor[(2 * i) + 2].ratio), blend_factor(tor[(2 * i) + 1].color, tor[(2 * i) + 1].ratio));
			if (tor[i].coef_tra != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
			else if (tor[i].coef_ref != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
		}
		i = i - 1;
	}
	color = blend_add(blend_factor(tor[(2 * i) + 2].color, tor[(2 * i) + 2].ratio), blend_factor(tor[(2 * i) + 1].color, tor[(2 * i) + 1].ratio));
	if (tor[i].coef_tra != 0)
		color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
	else
		color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
	return (color);
}

// OCL TO CUDA -> need test
__device__ t_tor		tor_push(float3 ray, float3 normale, float3 pos, float coef_ref, float coef_tra, float opacity, unsigned int color, int type, float ratio)
{
	t_tor			tor;

	tor.prim = ray;
	tor.pos = pos;
	tor.normale = normale;
	tor.coef_ref = coef_ref;
	tor.coef_tra = coef_tra;
	tor.opacity = opacity;
	tor.color = color;
	tor.activate = 1;
	tor.ratio = ratio;
	tor.type = type;
	return (tor);
}

// OCL TO CUDA -> need test
__device__ unsigned int	fresnel(t_scene *scene, float3 ray, t_hit old_hit, int depth, unsigned int color)
{
	t_hit			new_hit;
	unsigned int	ncolor = 0;
	float3			new_ray = make_float3(0.f);
	float3			dummy = make_float3(0.f);
	float			fr = 0.f;
	float			cos1 = 0.f;
	float			sint = 0.f;
	t_tor			tor[63];
	int				i = 0;
	int				tor_depth = 0;

	tor_depth = (int)(pow(2.f, (float)(depth))) - 1;
	i = 0;
	while (i < 63)
	{
		tor[i].activate = 0;
		tor[i].prim = make_float3(0.f);
		tor[i].normale = make_float3(0.f);
		tor[i].pos = make_float3(0.f);
		tor[i].coef_ref = 0.f;
		tor[i].coef_tra = 0.f;
		tor[i].color = 0;
		tor[i].opacity = 0.f;
		tor[i].type = 0;
		tor[i].ratio = 0.f;
		i++;
	}
	i = 0;
	
	tor[i] = tor_push(	ray, 
						old_hit.normal, 
						old_hit.pos, 
						old_hit.obj->reflex,
						old_hit.obj->refract, 
						old_hit.obj->opacity, 
						color,
						old_hit.obj->type, 
						0);

	while (i < 31 && i < tor_depth)
	{
		int rhododendron = 0;
		if (tor[i].coef_tra != 0)
		{
			while (rhododendron < 4)
			{
				cos1 = dot(tor[i].normale, tor[i].prim);
				if (cos1 >= 0)
					sint = tor[i].coef_tra * sqrt(1 - cos1 * cos1);
				else
					sint = 1 / tor[i].coef_tra * sqrt(1 - cos1 * cos1);
				if (sint >= 1)
					fr = 1;
				else
					fr = reflect_ratio(1, tor[i].coef_tra, cos1, sint);
				if (fr < 1)
				{
					if (tor[i].type != OBJ_PLANE)
						new_ray = refract_ray(scene, tor[i].prim, tor[i].normale, tor[i].coef_tra);
					else
						new_ray = tor[i].prim;
					if (cos1 < 0)
						new_hit = ray_hit(scene, tor[i].pos + (0.001f * (2.f * -tor[i].normale)), new_ray, 0);
					else
						new_hit = ray_hit(scene, tor[i].pos, new_ray, 0);
					if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
					{
						if (cos1 < 0)
							new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos + (0.001f * (2.f * -tor[i].normale));
						else
							new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos;
						new_hit.normal = get_hit_normal(scene, new_ray, new_hit);
						new_hit.pos = new_hit.pos + (0.001f * new_hit.normal);

						if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
							new_hit.color = sphere_texture(normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, ((t_sphere *)new_hit.obj)->diff_ratio, ((t_sphere *)new_hit.obj)->diff_offset);
						else if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
							new_hit.color = sphere_checkerboard(normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

						else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
							new_hit.color = plane_texture(new_hit.normal, new_hit.pos, ((t_plane *)new_hit.obj)->u_axis, ((t_plane *)new_hit.obj)->diff_ratio, ((t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
						else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
							new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

						else if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
							new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, (t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

						else if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
							new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, ((t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((t_cone *)new_hit.obj)->diff_ratio, ((t_cone *)new_hit.obj)->diff_offset);
						else
							new_hit.color = new_hit.obj->color;
		
						ncolor = phong(scene, new_hit, new_ray);
						tor[(i * 2) + 1] = tor_push(new_ray, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.obj->type, 1 - fr);
					}
					else
					{
						if (scene->flag & OPTION_SKYBOX)
							ncolor = skybox(new_ray, scene->texture_star, 4096, 2048);
						else
							ncolor = get_ambient(scene, BACKCOLOR);
						tor[(i * 2) + 1] = tor_push(new_ray, new_hit.normal, new_hit.pos, 0, 0, 0, ncolor, 0, 1 - fr);
					}
				}
				rhododendron++;
				i++;
			}
			i -= 4;
		}
		else if (tor[i].coef_ref != 0)
			fr = 1;
		else
			fr = 0;
		if (fr > 0)
		{
			cos1 = dot(tor[i].normale, tor[i].prim);
			if (cos1 >= 0)
				new_ray = bounce_ray(scene, tor[i].prim, tor[i]);
			else
				new_ray = bounce_ray(scene, tor[i].prim, tor[i]);
			if (cos1 >= 0)
				new_hit = ray_hit(scene, tor[i].pos + (0.001f * (2.f * -tor[i].normale)), new_ray, 0);
			else
				new_hit = ray_hit(scene, tor[i].pos, new_ray, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				if (cos1 >= 0)
					new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos + (0.001f * (2.f * -tor[i].normale));
				else
					new_hit.pos = (new_hit.dist * new_ray) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, new_ray, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / SHADOW_BIAS * new_hit.normal);


				if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = sphere_texture(normalize(new_hit.obj->pos - new_hit.pos), scene->texture_earth, 4915, 2457, ((t_sphere *)new_hit.obj)->diff_ratio, ((t_sphere *)new_hit.obj)->diff_offset);
				else if ((new_hit.obj->type == OBJ_SPHERE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = sphere_checkerboard(normalize(new_hit.obj->pos - new_hit.pos), new_hit.obj->color, new_hit.obj->check_size);

				else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = plane_texture(new_hit.normal, new_hit.pos, ((t_plane *)new_hit.obj)->u_axis, ((t_plane *)new_hit.obj)->diff_ratio, ((t_plane *)new_hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
				else if ((new_hit.obj->type == OBJ_PLANE) && (new_hit.obj->flags & OBJ_FLAG_CHECKERED))
					new_hit.color = plane_checkerboard(new_hit.normal, new_hit.pos, new_hit.obj->color, new_hit.obj->check_size);

				else if ((new_hit.obj->type == OBJ_CYLINDER) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cylinder_texture(new_hit.pos - new_hit.obj->pos, (t_cylinder *)new_hit.obj, scene->texture_star, 1500, 1500);

				else if ((new_hit.obj->type == OBJ_CONE) && (new_hit.obj->flags & OBJ_FLAG_DIFF_MAP))
					new_hit.color = cone_texture(new_hit.pos - new_hit.obj->pos, new_hit.obj->dir, ((t_cone *)new_hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((t_cone *)new_hit.obj)->diff_ratio, ((t_cone *)new_hit.obj)->diff_offset);
				else
					new_hit.color = new_hit.obj->color;
				
				ncolor = phong(scene, new_hit, new_ray);
				tor[(2 * i) + 2] = tor_push(new_ray, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.obj->type, fr);
			}
			else
			{
				if (scene->flag & OPTION_SKYBOX)
					ncolor = skybox(new_ray, scene->texture_star, 4096, 2048);
				else
					ncolor = get_ambient(scene, BACKCOLOR);
				tor[(2 * i) + 2] = tor_push(new_ray, new_hit.normal, new_hit.pos, 0, 0, 0, ncolor, 0, fr);

			}
		}
		i = i + 1;
		while (i < 31 && tor[i].activate == 0)
			i = i + 1;
	}
	return (tor_final_color(tor));
}

// OCL TO CUDA -> need test
__device__ unsigned int	get_pixel_color(t_scene *scene, float3 ray, int *target, bool isHim, int index)
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
		hit.pos = hit.pos + (hit.dist / 1000.f * hit.normal);


		if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			 hit.color = sphere_texture(normalize(hit.obj->pos - hit.pos), scene->texture_earth, 4915, 2457, ((t_sphere *)hit.obj)->diff_ratio, ((t_sphere *)hit.obj)->diff_offset);
		else if ((hit.obj->type == OBJ_SPHERE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
			hit.color = sphere_checkerboard(normalize(hit.obj->pos - hit.pos), hit.obj->color, hit.obj->check_size);

		else if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = plane_texture(hit.normal, hit.pos, ((t_plane *)hit.obj)->u_axis, ((t_plane *)hit.obj)->diff_ratio, ((t_plane *)hit.obj)->diff_offset, scene->texture_star, 1500, 1500);
		else if ((hit.obj->type == OBJ_PLANE) && (hit.obj->flags & OBJ_FLAG_CHECKERED))
			hit.color = plane_checkerboard(hit.normal, hit.pos, hit.obj->color, hit.obj->check_size);

		else if ((hit.obj->type == OBJ_CYLINDER) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = cylinder_texture(hit.pos - hit.obj->pos, (t_cylinder *)hit.obj, scene->texture_star, 1500, 1500);

		else if ((hit.obj->type == OBJ_CONE) && (hit.obj->flags & OBJ_FLAG_DIFF_MAP))
			hit.color = cone_texture(hit.pos - hit.obj->pos, hit.obj->dir, ((t_cone *)hit.obj)->u_axis, scene->texture_star, 1500, 1500, ((t_cone *)hit.obj)->diff_ratio, ((t_cone *)hit.obj)->diff_offset);

		color = phong(scene, hit, ray);
		if (((hit.obj->refract != 0 && hit.obj->opacity < 1) || hit.obj->reflex > 0) && depth > 0)
			return (fresnel(scene, ray, hit, depth, color));

		return (blend_add(color, bounce_color));
	}
	
	if (scene->flag & OPTION_SKYBOX)
	{
		color = skybox(ray, scene->texture_star, 4096, 2048);
		return (color);
	}
	else
		return (get_ambient(scene, BACKCOLOR));
}


// OCL TO CUDA -> ok
__device__ float3		get_ray_cam(t_scene *scene, int x, int y, int width, int height)
{
	float3			cam_ray = make_float3(0.f);
	float			ratio = ((float)width) / ((float)height);

	cam_ray.x = ((2.f * (((float)x + 0.5f) / (float)width)) - 1.f) * ratio * (tanf(radians(ACTIVECAM.fov / 2.f)));
	cam_ray.y = ((1.f - (2 * (((float)y + 0.5f) / (float)height))) * tanf(radians(ACTIVECAM.fov / 2.f)));
	cam_ray.z = 1.f;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(normalize(cam_ray));
}

__device__ unsigned int	ray_trace(	int				index,
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
	unsigned int	final_color = 0;
	unsigned int	final_color_o[32] = {0};
	uint3			rgb = make_uint3(0);
	float3			prim_ray = make_float3(0.f);
	int				x = 0;
	int				y = 0;

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

	if (scene->over_sampling > 1)
	{
		uint2 true_pix = make_uint2(x, y);
		unsigned int lap = 0;
		x *= scene->over_sampling;
		y *= scene->over_sampling;

		while (lap < scene->over_sampling * 2)
		{
			x += (lap % 2);
			y += !(lap % 2);
			prim_ray = get_ray_cam(scene, x, y, scene->win_w * scene->over_sampling, scene->win_h * scene->over_sampling);
			final_color_o[lap] = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && true_pix.x == scene->mou_x && true_pix.y == scene->mou_y), index);
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
		prim_ray = get_ray_cam(scene, x, y, scene->win_w, scene->win_h);
		final_color = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && x == scene->mou_x && y == scene->mou_y), index);
	}

	if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);
	if (scene->flag & OPTION_INVERT)
		final_color = invert(final_color);

	// test
	__syncthreads();

	// ALPHA INSERT and RGB SWAP
	int nw, nx, ny, nz;
	nw = 255;
	nx = (final_color & 0x00FF0000) >> 16;
	ny = (final_color & 0x0000FF00) >> 8;
	nz = (final_color & 0x000000FF);
	final_color = ((nw << 24) + (nz << 16) + (ny << 8) + nx);
	return (final_color);
}

__global__ void rt_launcher(unsigned int *output,
						char *mem_objects, int mem_size_objects,
						float u_time,
						t_scene *scene_data, t_cam *cameras_data,
						char *mem_lights, int mem_size_lights, int *target,
						unsigned int *texture_0,
						unsigned int *texture_1,
						unsigned int *texture_2,
						unsigned int *texture_3)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int index = row * scene_data->win_w + col;
	output[index] = ray_trace(index, mem_objects, mem_size_objects,
								u_time,
							scene_data, cameras_data,
							mem_lights, mem_size_lights, target, texture_0, texture_1, texture_2, texture_3);
}

extern "C" void render_cuda(t_cuda			*cuda,
							int 			*pixel_data,
							int				*target,
							t_gen			*gen_objects,
							t_gen			*gen_lights,
							float			u_time,
							t_scene			*scene_data,
							t_cam			*cameras_data)
{
	dim3					threads_per_block(8, 8);
	dim3					grid_size(scene_data->win_w / threads_per_block.x, scene_data->win_h / threads_per_block.y);
		/*printf("GPU\n");
		printf("t_cam %zu\n", sizeof(t_cam));
		printf("t_scene %zu\n", sizeof(t_scene));
		printf("t_object %zu\n", sizeof(t_object));
		printf("t_gen %zu\n", sizeof(t_gen));
		printf("t_sphere %zu\n", sizeof(t_sphere));
		printf("t_light %zu\n", sizeof(t_light));
		printf("t_cylinder %zu\n", sizeof(t_cylinder));
		printf("t_sphere %zu\n", sizeof(t_sphere));
		printf("t_ellipsoid %zu\n", sizeof(t_ellipsoid));
		printf("t_plane %zu\n", sizeof(t_plane));
		printf("t_cone %zu\n", sizeof(t_cone));
		printf("t_cone %zu\n", sizeof(t_cone));
		printf("\n");*/

	cudaMemcpy(cuda->mem[1], gen_objects->mem, gen_objects->mem_size, cudaMemcpyHostToDevice);
	cudaMemcpy(cuda->mem[2], gen_lights->mem, gen_lights->mem_size, cudaMemcpyHostToDevice);
	cudaMemcpy(cuda->mem[3], scene_data, sizeof(t_scene), cudaMemcpyHostToDevice);
	cudaMemcpy(cuda->mem[4], cameras_data, sizeof(t_cam), cudaMemcpyHostToDevice);

	rt_launcher <<< grid_size, threads_per_block >>> ((unsigned int *)cuda->mem[0],
												(char *)cuda->mem[1], gen_objects->mem_size,
												u_time,
												(t_scene *)cuda->mem[3], (t_cam *)cuda->mem[4],
												(char *)cuda->mem[2], gen_lights->mem_size, (int *)cuda->mem[5],
												NULL,
												NULL,
												NULL,
												NULL);
	cudaDeviceSynchronize();

	// check for errors
	cudaError_t error = cudaGetLastError();
	// HANDLE_ERROR(error);
	if (error != cudaSuccess)
	{
	 fprintf(stderr, "CUDA1 ERROR: %s \n", cudaGetErrorString(error));
	}

	//lecture framebuffer
	HANDLE_ERROR(cudaMemcpy(pixel_data, cuda->mem[0], scene_data->win_w * scene_data->win_h * sizeof(int), cudaMemcpyDeviceToHost));
	// error = cudaMemcpy(pixel_data, cuda->mem[0], scene_data->win_w * scene_data->win_h * sizeof(int), cudaMemcpyDeviceToHost);
	// if (error != cudaSuccess)
	// {
	//  fprintf(stderr, "CUDA2 ERROR: %s \n", cudaGetErrorString(error));
	// }

	//lecture target
	if (scene_data->flag & OPTION_RUN)
	{
		HANDLE_ERROR(cudaMemcpy(target, cuda->mem[5], sizeof(int), cudaMemcpyDeviceToHost));
		// error = cudaMemcpy(target, cuda->mem[5], sizeof(int), cudaMemcpyDeviceToHost);
		scene_data->flag ^= OPTION_RUN;
	}
	// if (error != cudaSuccess)
	// {
	//  fprintf(stderr, "CUDA3 ERROR: %s \n", cudaGetErrorString(error));
	// }
}
