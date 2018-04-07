/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:19:14 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/07 16:33:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define DEG2RAD		(M_PI / 180)
# define RAD2DEG		(180 / M_PI)

# define WIDTH			e->scene->win_w
# define HEIGHT			e->scene->win_h
# define DEPTH			e->scene->depth

# define KRT			e->cl.kernel
# define NCAM			e->scene->n_cams
# define NCON			e->scene->n_cones
# define NCYL			e->scene->n_cylinders
# define NLIG			e->scene->n_lights
# define NPLA			e->scene->n_planes
# define NSPH			e->scene->n_spheres
# define NELL			e->scene->n_ellipsoids

# define A_CAM			e->cameras[e->scene->active_cam]
# define A_LIG			((t_light*)e->gen_lights->mem)[e->ui->light_selector]

# define XMLSUB			e->xml->sub_node
# define XML			e->xml
# define SCN			e->scene

# define RESERVED				(1 << 0)
# define OPTION_WAVE			(1 << 1)
# define OPTION_SEPIA			(1 << 2)
# define OPTION_BW				(1 << 3)
# define OPTION_RUN				(1 << 4)
# define OPTION_GPU				(1 << 5)
# define OPTION_DEBUG			(1 << 6)
# define OPTION_INVERT			(1 << 7)
# define OPTION_CARTOON_FOUR	(1 << 8)
# define OPTION_STEREO			(1 << 9)
# define OPTION_CARTOON_TWO		(1 << 10)

# define OBJ_FLAG_WAVES			(1 << 1)
# define OBJ_FLAG_CHECKERED		(1 << 2)
# define OBJ_FLAG_DIFF_MAP		(1 << 3)
# define OBJ_FLAG_BUMP_MAP		(1 << 4)
# define OBJ_FLAG_PLANE_LIMIT	(1 << 5)
# define OBJ_FLAG_PLANE_LIMIT_FIX		(1 << 6)

# define OBJ_CAM			1
# define OBJ_LIGHT			2
# define OBJ_CONE			3
# define OBJ_CYLINDER		4
# define OBJ_PLANE			5
# define OBJ_SPHERE			6
# define OBJ_ELLIPSOID		7
# define OBJ_TORUS			8
# define OBJ_BOX			9

# define NB_TEXTURE			4

typedef struct			s_object
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;
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

typedef struct			s_box
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

	cl_float3			min;
	cl_float3			max;
}						t_box;

typedef struct			s_cone
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

	cl_float			angle;
	cl_float3			u_axis;
}						t_cone;

typedef struct			s_cylinder
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

	cl_float			height;
	cl_float3			base_dir;
	cl_float			radius;
	cl_float3			u_axis;
}						t_cylinder;

typedef struct			s_plane
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			normal;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

	cl_float			radius;
	cl_float3			u_axis;
}						t_plane;

typedef struct			s_sphere
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

	cl_float			radius;
}						t_sphere;

typedef struct			s_torus
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

	cl_double			lil_radius;
	cl_double			big_radius;
}						t_torus;

typedef struct			s_ellipsoid
{
	cl_int				size;
	cl_int				type;
	cl_int				flags;
	cl_int				id;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			diff;
	cl_float3			spec;
	cl_int				color;
	cl_float			reflex;
	cl_float			refract;
	cl_float			opacity;
	cl_float3			limit_pos;
	cl_float3			limit_dir;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
	cl_float2			check_size;
	cl_int				diff_map_id;
	cl_float2			diff_offset;
	cl_float2			diff_ratio;
	cl_float2			test_var1;
	cl_float2			test_var2;
	cl_float2			test_var3;

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
	cl_float3			min;
	cl_float3			max;
	cl_float			radius;
	cl_float			radius2;
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
	cl_float3			limit_dir;
	cl_float3			limit_pos;
	cl_int				flags;
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

typedef struct			s_rtx
{
	GdkPixbuf			*pixbuf;
	guchar				*pixels;
	int					width;
	int					height;
	int					rowstride;
	int					n_channels;
}						t_rtx;

typedef struct			s_tex
{
	unsigned int		*pixel_array;
	int					width;
	int					height;
}						t_tex;

typedef struct			s_scene
{
	t_cam				*cameras;
	void				*mem_lights;
	void				*mem_obj;
	unsigned int		*texture_earth;
	unsigned int		*texture_moon;
	unsigned int		*texture_earth_cloud;
	unsigned int		*texture_star;
	cl_uint				n_cams;
	cl_uint				active_cam;
	cl_uint				win_w;
	cl_uint				win_h;
	cl_float3			ambient;
	cl_uint				mou_x;
	cl_uint				mou_y;
	cl_uint				depth;
	cl_float			u_time;
	cl_int				flag;
	cl_uint				over_sampling;
	cl_uint				mem_size_obj;
	cl_uint				mem_size_lights;
	cl_float3			check_p1;
	cl_float3			check_p2;
	cl_float3			waves_p1;
	cl_float3			waves_p2;
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

	int					*pixel_data;
	int					target;
	t_rtx				raw_texture;
	t_tex				*texture;
	int					current_index_objects;
}						t_env;

cl_float4				add_cl_float(cl_float4 v1, cl_float4 v2);
cl_float3				sub_cl_float(cl_float3 v1, cl_float3 v2);
cl_float3				rotz(cl_float3 dir, float roll);
cl_float3				roty(cl_float3 dir, float yaw);
cl_float3				rotx(cl_float3 dir, float pitch);
cl_float3				rotcam(cl_float3 vect, float rad_pitch, float rad_yaw);

int						opencl_draw(t_env *e);

void					init(GtkApplication *app, gpointer data);
void					init_gtk(GtkApplication *app, gpointer data);
void					init_cb_cam(t_env *e);
void					init_cb_light(t_env *e);
void					init_cb_main(t_env *e);
void					init_cb_object(t_env *e);
void					init_cb_scene(t_env *e);
void					init_cb_object_checkboard(t_env *e);
void					init_cb_object_diffmap(t_env *e);
void					init_cb_object_limit(t_env *e);
void					init_cb_object_sinwave(t_env *e);
void					init_gtk_cam(t_env *e);
void					init_gtk_css(t_env *e);
void					init_gtk_light(t_env *e);
void					init_gtk_object(t_env *e);
void					init_gtk_object_checkboard(t_env *e);
void					init_gtk_object_diffmap(t_env *e);
void					init_gtk_object_effects(t_env *e);
void					init_gtk_object_limit(t_env *e);
void					init_gtk_object_sinwave(t_env *e);
void					init_gtk_scene(t_env *e);
void					init_gtk_texture(t_env *e);
void					init_gtk_toolbar(t_env *e);
void					init_gtk_win(t_env *e);

cl_float3				normalize_vect(cl_float3 v);

void					opencl_set_args(t_env *e, t_cl *cl);

void					p_error(char *str, t_env *e);
void					s_error(char *str, t_env *e);
void					print_usage();
int						quit(t_env *e);

void					clear_surface(t_env *e);
void					gtk_render_events(t_env *e);
void					ui_add_cone(t_env *e);
void					ui_add_cylinder(t_env *e);
void					ui_add_ellipsoid(t_env *e);
void					ui_add_plane(t_env *e);
void					ui_add_sphere(t_env *e);
void					ui_add_torus(t_env *e);
void					ui_cam(t_env *e);
void					ui_cam_set_id(t_env *e);
void					ui_cam_update(t_env *e);
void					ui_light_set_id(t_env *e);
void					ui_light_update(t_env *e);
void					ui_obj(t_env *e);
void					ui_obj_jump_list(t_env *e);
void					ui_obj_set_cone(t_env *e, t_cone *obj);
void					ui_obj_set_cylinder(t_env *e, t_cylinder *obj);
void					ui_obj_set_ellipsoid(t_env *e, t_ellipsoid *obj);
void					ui_obj_set_plane(t_env *e, t_plane *obj);
void					ui_obj_set_sphere(t_env *e, t_sphere *obj);
void					ui_obj_set_torus(t_env *e, t_torus *obj);
void					ui_obj_update(t_env *e, t_object *obj);
void					ui_obj_update_checkboard(t_env *e, t_object *obj);
void					ui_obj_update_diff_map(t_env *e, t_object *obj);
void					ui_obj_update_limit(t_env *e, t_object *obj);
void					ui_obj_update_sinwave(t_env *e, t_object *obj);

void					update_fps(t_fps *fps);

void					xml_allocate_cam(t_env *e);
int						xml_check_attr(t_env *e, char **att);
int						xml_check_char(char c);
int						xml_check_float(cl_float3 *clf, float f, int mod);
char					*xml_check_line(t_env *e, char *buf);
int						xml_check_node_format(char **node, int mod);
void					xml_data_angle(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_axis_size(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_big_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_brightness(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_color(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_diffiouse(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_dir(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_flag(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_height(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_lil_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_normale(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_opacity(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_plane_limit_dir(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_plane_limit_pos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_plane_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_pos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_reflex(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_refract(t_env *e, char **attributes, \
										int *i, t_node *node);

void					xml_data_shrink(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_speculos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_type(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_min_max(t_env *e, char **attributes, \
										int *i, cl_float3 *f);
void					xml_init(t_env *e);
void					xml_get_file(t_env *e);
void					xml_list_add_first(t_node **begin, t_node *node);
void					xml_list_clean(t_env *e, t_node **list);
t_node					*xml_list_new(char type);

void					xml_node_cam(t_env *e, char *node);
void					xml_node_clean(char **target);
void					xml_node_cone(t_env *e, char *node);
void					xml_node_cylinder(t_env *e, char *node);
void					xml_node_ellipsoid(t_env *e, char *node);
void					xml_node_light(t_env *e, char *node);
void					xml_node_plane(t_env *e, char *node);
void					xml_node_scene(t_env *e, char *node, char mod);
void					xml_node_sphere(t_env *e, char *node);
void					xml_node_box(t_env *e, char *node);
void					xml_node_torus(t_env *e, char *node);

void					xml_parse_nodes(t_env *e);
void					xml_push_cam(t_env *e, t_node *list);
void					xml_push_cone(t_env *e, t_node *list);
void					xml_push_cyl(t_env *e, t_node *list);
void					xml_push_ellipsoid(t_env *e, t_node *list);
void					xml_push_light(t_env *e, t_node *list);
void					xml_push_plane(t_env *e, t_node *list);
void					xml_push_sphere(t_env *e, t_node *list);
void					xml_push_box(t_env *e, t_node *list);
void					xml_push_torus(t_env *e, t_node *list);

void					xml_save_scene(t_env *e, char *filename);
void					xml_write_flags(const int flags, const int fd);
void					xml_write_color(const int color, const int fd);
void					xml_write_int(const char *name, const float data, \
										const int fd);
void					xml_write_float(const char *name, const float data, \
										const int fd);
void					xml_write_float3(const char *name, \
										const cl_float3 data, const int fd);

void					xml_write_cameras(t_env *e, const int fd, \
										t_cam *cameras);
void					xml_write_cone(t_cone *cone, const int fd);
void					xml_write_cylinder(t_cylinder *cyl, const int fd);
void					xml_write_lights(t_env *e, const int fd);
void					xml_write_ellipsoid(t_ellipsoid *elli, const int fd);
void					xml_write_plane(t_plane *plane, const int fd);
void					xml_write_sphere(t_sphere *sphere, const int fd);
void					xml_write_torus(t_torus *torus, const int fd);

void					init_test_var(t_env *e);
void					init_test_var_cb(t_env *e);
#endif
