#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"
# include <sys/time.h>

# ifdef MAC_KEYS
#  include "mac_keys.h"
# elif LINUX_KEYS
#  include "linux_keys.h"
# endif

# ifdef GPU
#  define IS_GPU			1
# else
#  define IS_GPU			0
# endif

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# ifdef DEBUG
#  define DBUG					1
# else
#  define DBUG					0
# endif

# define MAX_SOURCE_SIZE	(0x100000)
# define DESTROYNOTIFY			17
# define KEYPRESSMASK			(1L<<0)
# define KEYRELEASEMASK			(1L<<1)
# define KEYPRESS				2
# define KEYRELEASE				3

# define DEG2RAD				(M_PI / 180)
# define RAD2DEG				(180 / M_PI)

# define WIDTH					e->scene->win_w
# define HEIGHT					e->scene->win_h
# define DEPTH					e->scene->depth

# define KRT					e->cl.kernel
# define NCAM					e->scene->n_cams
# define NCON					e->scene->n_cones
# define NCYL					e->scene->n_cylinders
# define NLIG					e->scene->n_lights
# define NPLA					e->scene->n_planes
# define NSPH					e->scene->n_spheres
# define ACTIVEOBJ				e->target_obj
# define CAM					e->cameras
# define CONES					e->cones
# define CYLIND					e->cylinders
# define LIGHT					e->lights
# define PLANE					e->planes
# define SPHERE					e->spheres
# define ACTIVECAM				e->cameras[e->scene->active_cam]

# define XMLSUB					e->xml->sub_node
# define XML					e->xml
# define SCN					e->scene

# define RESERVED				(1 << 0)
# define OPTION_WAVE			(1 << 1)
# define OPTION_SEPIA			(1 << 2)
# define OPTION_BW				(1 << 3)
# define OPTION_RUN				(1 << 4)

# define OBJ_CONE			1
# define OBJ_CYLINDER		2
# define OBJ_PLANE			3
# define OBJ_SPHERE			4

typedef struct			s_object
{
	cl_int				size;
	cl_int				id;
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			diff;
	cl_float4			spec;
	cl_int				color;
	cl_float			reflex;
}						t_object;

typedef struct			s_fps
{
	struct timeval		step2;
	struct timeval		step;
	struct timeval		cur;
	float				delta_time;
	float				u_time;
	unsigned int		fps;
	unsigned int		ret_fps;
}						t_fps;

typedef struct			s_p2i
{
	int					x;
	int					y;
}						t_p2i;

typedef struct			s_hit
{
	cl_float			dist;
	cl_float4			normale;
	cl_float4			pos;
	t_object			*obj;
	cl_int				mem_index;
}						t_hit;

typedef struct			s_cam
{
	cl_float4			pos;
	cl_float4			dir;
	cl_float			fov;
	cl_float			pitch;
	cl_float			yaw;
	cl_float			roll;
}						t_cam;

typedef struct			s_light
{
	cl_int				size;
	cl_int				type;
	cl_float4			pos;
	cl_float4			dir;
	cl_int				shrink;
	cl_float			brightness;
	cl_int				color;
}						t_light;

/*							*\
**|							**|
**|			OBJECT			**|
**|							**!
*/

typedef struct			s_cone
{
	cl_int				size;
	cl_int				id;
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			diff;
	cl_float4			spec;
	cl_int				color;
	cl_float			reflex;

	cl_float			angle;

}						t_cone;

typedef struct			s_cylinder
{
	cl_int				size;
	cl_int				id;
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			diff;
	cl_float4			spec;
	cl_int				color;
	cl_float			reflex;

	cl_float			height;
	cl_float4			base_dir;
	cl_float			radius;
}						t_cylinder;

typedef struct			s_plane
{
	cl_int				size;
	cl_int				id;
	cl_float4			pos;
	cl_float4			normale;
	cl_float4			diff;
	cl_float4			spec;
	cl_int				color;
	cl_float			reflex;
}						t_plane;

typedef struct			s_sphere
{
	cl_int				size;
	cl_int				id;
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			diff;
	cl_float4			spec;
	cl_int				color;
	cl_float			reflex;

	cl_float			radius;
}						t_sphere;

typedef struct			s_param
{
	int					n_cams;
	int					n_cones;
	int					n_cylinders;
	int					n_lights;
	int					n_planes;
	int					n_spheres;
	int					active_cam;
	int					win_w;
	int					win_h;
	cl_float4			mvt;
	cl_float4			ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
}						t_param;

typedef struct			s_node
{
	int					id;
	int					type;
	cl_float			fov;
	cl_float4			dir;
	cl_float4			pos;
	cl_float4			normale;
	cl_float			radius;
	cl_float			angle;
	cl_int				color;
	cl_int				light;
	cl_int				shrink;
	cl_float			brightness;
	cl_float			height;
	cl_float4			diff;
	cl_float4			spec;
	cl_float			reflex;
	struct s_node		*next;
}						t_node;

typedef	struct			s_xml
{
	char				*scene;
	int					scene_fd;
	char				**nodes;
	char				**sub_node;
	t_node				*node_lst;
	char				is_comm;
	char				in_scene;
	int					n_nodes;
	int					n_sub;
	int					lbra;
	int					rbra;
	int					slas;
	int					dquo;
	int					excl;
}						t_xml;

typedef struct			s_frame
{
	void				*ptr;
	char				*pix;
	int					x;
	int					y;
	int					w;
	int					h;
	int					row;
	int					bpp;
	int					endian;
}						t_frame;

typedef	struct			s_tor
{
	cl_float4			prim;
//	cl_float4			refl;
//	cl_float4			refr;
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
	t_cam				*cameras;
	void				*mem_lights;
	void				*mem_obj;
	unsigned int		n_cams;
	unsigned int		n_cones;
	unsigned int		n_cylinders;
	unsigned int		n_lights;
	unsigned int		n_planes;
	unsigned int		n_spheres;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	cl_float4			ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
	float				u_time;
	int					flag;
	int					tor_count;
	size_t				mem_size_obj;
	size_t				mem_size_lights;
}						t_scene;

typedef struct			s_gen
{
	bool				(*add)(struct s_gen *, void *);
	size_t				mem_size;
	size_t				unit_size;
	void				*mem;
}						t_gen;
void		*construct_gen();
bool		gen_add(t_gen *gen, void *elem);
void		*destruct_gen(t_gen **gen);

# define CL_ERROR_LEN_BUFFER 17000

typedef struct			s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	cq;
	size_t				nb_mem;
	cl_mem				*mem;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				err;
	size_t				global_item_size;
	size_t				local_item_size;

	char				*path;
}						t_cl;

void					cl_check_err(cl_int err, const char *name);
void					cl_end(t_cl *cl);
int						cl_init(t_cl *cl, const char *path, const char *name,
								const size_t global_item_size);
bool					cl_create_buffer(t_cl *cl, size_t size);

typedef	struct			s_env
{
	t_cl			cl;

	void				*mlx;
	void				*win;
	t_frame				*frame;
	t_key				keys;
	int					win_w;
	int					win_h;
	int					sce_w;
	int					sce_h;
	int					cen_x;
	int					cen_y;
	int					debug;
	t_xml				*xml;

	char				*frame_buffer;
	cl_mem				target_obj_buf;
	t_hit				target_obj;
	int					gpu;
	size_t				global;
	size_t				local;
	unsigned int		count;

	t_cam				*cameras;
	cl_mem				cameras_mem;
	t_cone				*cones;
	cl_mem				cones_mem;
	t_cylinder			*cylinders;
	cl_mem				cylinders_mem;
	t_light				*lights;
	cl_mem				lights_mem;
	t_plane				*planes;
	cl_mem				planes_mem;
	t_sphere			*spheres;
	cl_mem				spheres_mem;

	t_scene				*scene;
	cl_mem				scene_mem;
	t_fps				fps;

	t_tor				*tree;
	int					node_count;

	cl_mem				gen_mem;
	t_gen				*gen_objects;
	t_gen				*gen_lights;
}						t_env;

cl_float4				add_cl_float(cl_float4 v1, cl_float4 v2);
void					display_hud(t_env *e);
int						draw(t_env *e);
void					error(void);
cl_float4				*get_target_dir(t_env *e);
cl_float4				*get_target_pos(t_env *e);
void					init(t_env *e, int ac, char *av);
void					mlx_img_line(t_frame *sce, t_p2i p1, t_p2i p2, int c);
int						mlx_img_pix_put(t_frame *sce, int x, int y, int color);
void					mlx_keyboard_repeated(t_env *e);
void					mlx_key_no_repeat_event(t_env *e, const int key);
int						mlx_key_press(int key, t_env *e);
int						mlx_key_release(int key, t_env *e);
int						mlx_key_simple(int key, t_env *e);
int						mlx_main_loop(t_env *e);
int						mlx_mouse_events(int btn, int x, int y, t_env *e);
cl_float4				normalize_vect(cl_float4 v);
void					p_error(char *str, t_env *e);
void					print_usage();
int						quit(t_env *e);
void					refresh(t_env *e);
cl_float4				rotz(cl_float4 dir, float roll);
cl_float4				roty(cl_float4 dir, float yaw);
cl_float4				rotx(cl_float4 dir, float pitch);
cl_float4				rotcam(cl_float4 vect, float rad_pitch, float rad_yaw);
void					s_error(char *str, t_env *e);
void					set_hooks(t_env *e);
cl_float4				sub_cl_float(cl_float4 v1, cl_float4 v2);
t_tor					*tor_create(t_env *e);
int						tor_flush(t_env *e);
void					ui_cam(t_env *e);
void					ui_obj(t_env *e);
void					update_fps(t_fps *fps);
void					xml_allocate_cam(t_env *e);
void					xml_allocate_cone(t_env *e);
void					xml_allocate_cyl(t_env *e);
void					xml_allocate_light(t_env *e);
void					xml_allocate_plane(t_env *e);
void					xml_allocate_sphere(t_env *e);
int						xml_check_attr(t_env *e, char **att);
int						check_float(cl_float3 *clf, float f, int mod);
int						xml_check_char(char c);
char					*xml_check_line(t_env *e, char *buf);
int						xml_check_node_format(char **node, int mod);
void					xml_data_angle(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_brightness(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_color(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_diffiouse(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_dir(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_height(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_normale(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_pos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_reflex(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_shrink(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_speculos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_type(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_init(t_env *e, int ac, char *av);
void					xml_get_file(t_env *e, int ac, char *av);
void					xml_list_add_first(t_node **begin, t_node *node);
void					xml_list_clean(t_env *e, t_node **list);
t_node					*xml_list_new(char type);
void					xml_node_clean(char **target);
void					xml_node_cam(t_env *e, char *node);
void					xml_node_cone(t_env *e, char *node);
void					xml_node_cylinder(t_env *e, char *node);
void					xml_node_light(t_env *e, char *node);
void					xml_node_plane(t_env *e, char *node);
void					xml_node_scene(t_env *e, char *node, char mod);
void					xml_node_sphere(t_env *e, char *node);
void					xml_parse_nodes(t_env *e);
void					xml_push_cam(t_env *e, t_node *list);
void					xml_push_cone(t_env *e, t_node *list);
void					xml_push_cyl(t_env *e, t_node *list);
void					xml_push_light(t_env *e, t_node *list);
void					xml_push_plane(t_env *e, t_node *list);
void					xml_push_sphere(t_env *e, t_node *list);

#endif
