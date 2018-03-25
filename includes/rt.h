#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"

# include "cl.h"
# include "ui.h"
# include "gen.h"


# ifdef GPU
#  define IS_GPU			1
# else
#  define IS_GPU			1
# endif

# ifdef DEBUG
#  define DBUG					1
# else
#  define DBUG					0
# endif

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
# define NELL					e->scene->n_ellipsoids
# define NPAR					e->scene->n_paraboloids
//# define ACTIVEOBJ				e->target_obj // DELETE
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
# define OPTION_GPU				(1 << 5)
# define OPTION_DEBUG			(1 << 6)
# define OPTION_INVERT			(1 << 7)

# define OBJ_CAM			1
# define OBJ_LIGHT			2
# define OBJ_CONE			3
# define OBJ_CYLINDER		4
# define OBJ_PLANE			5
# define OBJ_SPHERE			6
# define OBJ_ELLIPSOID		7
# define OBJ_PARABOLOID		8

typedef struct			s_object
{
	cl_int				size;
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
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
	cl_float3			normale;
	cl_float3			pos;
	t_object			*obj;
	cl_int				mem_index;
	cl_float			m;
	cl_int				isin;
}						t_hit;

typedef struct			s_cam
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			fov;
	cl_float			pitch;
	cl_float			yaw;
	cl_float			roll;
}						t_cam;

typedef struct			s_light
{
	cl_int				size;
	cl_int				type;
	cl_float3			pos;
	cl_float3			dir;
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
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float			angle;

}						t_cone;

typedef struct			s_cylinder
{
	cl_int				size;
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float			height;
	cl_float3			base_dir;
	cl_float			radius;
}						t_cylinder;

typedef struct			s_paraboloid
{
	cl_int				size;
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float			height;
	cl_float3			base_dir;
	cl_float			radius;
}						t_paraboloid;

typedef struct			s_plane
{
	cl_int				size;
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			normale;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
}						t_plane;

typedef struct			s_sphere
{
	cl_int				size;
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float			radius;
}						t_sphere;

typedef struct			s_ellipsoid
{
	cl_int				size;
	cl_int				type;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float			radius;
	cl_float3			axis_size;
}						t_ellipsoid;


typedef struct			s_node
{
	int					id;
	int					type;
	cl_float			fov;
	cl_float3			dir;
	cl_float3			pos;
	cl_float3			normale;
	cl_float3			axis_size;
	cl_float			radius;
	cl_float			angle;
	cl_int				color;
	cl_int				light;
	cl_int				shrink;
	cl_float			brightness;
	cl_float			height;
	cl_float3			diff;
	cl_float3			spec;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	struct s_node		*next;
}						t_node;

typedef	struct			s_xml
{
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
	unsigned int		n_ellipsoids;
	unsigned int		n_paraboloids;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	cl_float3			ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
	float				u_time;
	int					flag;
	int					tor_count;
	size_t				mem_size_obj;
	size_t				mem_size_lights;
	int					over_sampling;
}						t_scene;

typedef	struct			s_env
{
	t_cl				*cl;
	t_ui				*ui;

	char				*scene_file;
	int					scene_fd;
	t_scene				*scene;

	t_xml				*xml;
	t_cam				*cameras;

	cl_mem				gen_mem;
	t_gen				*gen_objects;
	t_gen				*gen_lights;

	int					debug;
	int					gpu;
	t_fps				fps;

	int					*pixel_data; // raw pixel image
	int					target;
	int					current_index_objects;
}						t_env;

cl_float4				add_cl_float(cl_float4 v1, cl_float4 v2);
cl_float3				sub_cl_float(cl_float3 v1, cl_float3 v2);
cl_float3				rotz(cl_float3 dir, float roll);
cl_float3				roty(cl_float3 dir, float yaw);
cl_float3				rotx(cl_float3 dir, float pitch);
cl_float3				rotcam(cl_float3 vect, float rad_pitch, float rad_yaw);

void					display_hud(t_env *e);
int						opencl_draw(t_env *e);

cl_float3				*get_target_dir(t_env *e);
cl_float3				*get_target_pos(t_env *e);

void					init(GtkApplication* app, gpointer data);

cl_float3				normalize_vect(cl_float3 v);

void					opencl_set_args(t_env *e, t_cl *cl);


void					p_error(char *str, t_env *e);
void					s_error(char *str, t_env *e);
void					print_usage();
int						quit(t_env *e);

void					refresh(t_env *e);
void					print_obj(t_gen *gen, void *data);


void					clear_surface(t_env *e);
void					gtk_render_events(t_env *e);
void					ui_cam(t_env *e);
void					ui_cam_set_id(t_env *e);
void					ui_cam_update(t_env *e);
void					ui_light_set_id(t_env *e);
void					ui_light_update(t_env *e);
void					ui_obj(t_env *e);
void					update_fps(t_fps *fps);

void					xml_allocate_cam(t_env *e);
int						xml_check_attr(t_env *e, char **att);
int						xml_check_float(cl_float3 *clf, float f, int mod);
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
void					xml_data_axis_size(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_pos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_reflex(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_refract(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_opacity(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_shrink(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_speculos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_type(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_init(t_env *e);
void					xml_get_file(t_env *e);
void					xml_list_add_first(t_node **begin, t_node *node);
void					xml_list_clean(t_env *e, t_node **list);
t_node					*xml_list_new(char type);
void					xml_node_clean(char **target);
void					xml_node_cam(t_env *e, char *node);
void					xml_node_cone(t_env *e, char *node);
void					xml_node_cylinder(t_env *e, char *node);
void					xml_node_paraboloid(t_env *e, char *node);
void					xml_node_light(t_env *e, char *node);
void					xml_node_plane(t_env *e, char *node);
void					xml_node_scene(t_env *e, char *node, char mod);
void					xml_node_sphere(t_env *e, char *node);
void					xml_node_ellipsoid(t_env *e, char *node);
void					xml_parse_nodes(t_env *e);
void					xml_push_cam(t_env *e, t_node *list);
void					xml_push_cone(t_env *e, t_node *list);
void					xml_push_cyl(t_env *e, t_node *list);
void					xml_push_paraboloid(t_env *e, t_node *list);
void					xml_push_light(t_env *e, t_node *list);
void					xml_push_plane(t_env *e, t_node *list);
void					xml_push_sphere(t_env *e, t_node *list);
void					xml_push_ellipsoid(t_env *e, t_node *list);

#endif
