#define BACKCOLOR 0x00999999

# define EPSILON 0.000005f

#define MAX_DIST 10000000.0 // epsilon 0.00000001 ?
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
#define FLAG_DEBUG		(1 << 2)

# define OBJ_CONE			1
# define OBJ_CYLINDER		2
# define OBJ_PLANE			3
# define OBJ_SPHERE			4

typedef struct			s_object
{
	int					size;
	int					id;
	float4				pos;
	float4				dir;
	float4				diff;
	float4				spec;
	int					color;
	float				reflex;
}						t_object;

typedef struct			s_light_ray
{
	float4				dir;
	float				dist;
}						t_light_ray;

typedef struct			s_hit
{
	float				dist;
	float4				normale;
	float4				pos;
	t_object __local	*obj;
}						t_hit;

typedef struct			s_cam
{
	float4				pos;
	float4				dir;
	float				fov;
	float				pitch;
	float				yaw;
	float				roll;
}						t_cam;

typedef struct			s_light
{
	int					type;
	float4				pos;
	float4				dir;
	int					shrink;
	float				brightness;
	int					color;
}						t_light;

typedef struct			s_cone
{
	int					size;
	int					id;
	float4				pos;
	float4				dir;
	float4				diff;
	float4				spec;
	int					color;
	float				reflex;

	float				angle;

}						t_cone;

typedef struct			s_cylinder
{
	int					size;
	int					id;
	float4				pos;
	float4				dir;
	float4				diff;
	float4				spec;
	int					color;
	float				reflex;

	float				height;
	float4				base_dir;
	float				radius;
}						t_cylinder;

typedef struct			s_plane
{
	int					size;
	int					id;
	float4				pos;
	float4				normale;
	float4				diff;
	float4				spec;
	int					color;
	float				reflex;
}						t_plane;

typedef struct			s_sphere
{
	int					size;
	int					id;
	float4				pos;
	float4				dir;
	float4				diff;
	float4				spec;
	int					color;
	float				reflex;

	float				radius;
}						t_sphere;

typedef	struct			s_tor
{
	float4				prim;
//	float4				refl;
//	float4				refr;
	unsigned int		hit_type;
	unsigned int		hit_id;
//	float				coef_refl;
//	float				coef_refr;
	unsigned int		color;
	char				check_g;
	char				check_d;
}						t_tor;

typedef struct			s_scene
{
	t_cam				__local *cameras;
	//void				*void1;
	t_cone				__local *cones;
	//void				*void2;
	t_cylinder			__local *cylinders;
	//void				*void3;
	t_light				__local *lights;
	//void				*void4;
	t_plane				__local *planes;
	//void				*void5;
	t_sphere			__local *spheres;
	//void				*void6;
	void				__local *mem_obj;
	//void				*void7;
	unsigned int		n_cams;
	unsigned int		n_cones;
	unsigned int		n_cylinders;
	unsigned int		n_lights;
	unsigned int		n_planes;
	unsigned int		n_spheres;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	float4				ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
	float				u_time;
	int					flag;
	int					tor_count;
	size_t				mem_size_obj;
}						t_scene;
