/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:19:14 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/22 18:58:28 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>
# include <float.h>
# include <stdbool.h>
# include <stdint.h>

# include "libft.h"
# include "ui.h"
# include "gen.h"
# include "t_cuda.h"
# include "cuda.hl"

# ifdef GPU
#  define IS_GPU			1
# else
#  define IS_GPU			0
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
# define OPTION_SKYBOX			(1 << 11)

# define OBJ_FLAG_WAVES				(1 << 1)
# define OBJ_FLAG_CHECKERED			(1 << 2)
# define OBJ_FLAG_DIFF_MAP			(1 << 3)
# define OBJ_FLAG_BUMP_MAP			(1 << 4)
# define OBJ_FLAG_PLANE_LIMIT		(1 << 5)
# define OBJ_FLAG_PLANE_LIMIT_FIX	(1 << 6)
# define OBJ_FLAG_CUT				(1 << 7)

# define OBJ_CAM			1
# define OBJ_LIGHT			2
# define OBJ_CONE			3
# define OBJ_CYLINDER		4
# define OBJ_PLANE			5
# define OBJ_SPHERE			6
# define OBJ_ELLIPSOID		7
# define OBJ_TORUS			8
# define OBJ_KUBE			9

# define NB_TEXTURE			4

typedef struct			s_float3
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_float3;

# define FT_FLOAT3	t_float3
# define CUDA		1

typedef struct			s_uint2
{
	unsigned int		x;
	unsigned int		y;
}						t_uint2;

typedef struct			s_object
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;
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
	unsigned int		id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	float				fov;
	float				pitch;
	float				yaw;
	float				roll;
}						t_cam;

typedef struct			s_light
{
	int					size;
	int					type;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	int					shrink;
	float				brightness;
	int					color;
}						t_light;

typedef struct			s_cone
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	float				angle;
	FT_FLOAT3			u_axis;
}						t_cone;

typedef struct			s_cylinder
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	FT_FLOAT3			base_dir;
	float				radius;
	FT_FLOAT3			u_axis;
}						t_cylinder;

typedef struct			s_plane
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			normal;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	float				radius;
	FT_FLOAT3			u_axis;
}						t_plane;

typedef struct			s_sphere
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	float				radius;
}						t_sphere;

typedef struct			s_torus
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	double				lil_radius;
	double				big_radius;
}						t_torus;

typedef struct			s_kube
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	double				option;
}						t_kube;

typedef struct			s_ellipsoid
{
	int					size;
	int					type;
	int					flags;
	int					id;
	FT_FLOAT3			pos;
	FT_FLOAT3			dir;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	int					color;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_pos;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			waves_p1;
	FT_FLOAT3			waves_p2;
	FT_FLOAT3			check_size;
	int					diff_map_id;
	FT_FLOAT3			diff_offset;
	FT_FLOAT3			diff_ratio;
	FT_FLOAT3			cut_min;
	FT_FLOAT3			cut_max;
	FT_FLOAT3			cos;
	FT_FLOAT3			sin;

	float				radius;
	FT_FLOAT3			axis_size;
}						t_ellipsoid;

typedef struct			s_node
{
	int					id;
	int					type;
	float				fov;
	FT_FLOAT3			dir;
	FT_FLOAT3			pos;
	FT_FLOAT3			normale;
	FT_FLOAT3			axis_size;
	FT_FLOAT3			min;
	FT_FLOAT3			max;
	float				radius;
	float				radius2;
	float				angle;
	int					color;
	int					light;
	int					shrink;
	float				brightness;
	FT_FLOAT3			diff;
	FT_FLOAT3			spec;
	float				reflex;
	float				refract;
	float				opacity;
	FT_FLOAT3			limit_dir;
	FT_FLOAT3			limit_pos;
	int					flags;
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
	unsigned int		n_cams;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	FT_FLOAT3			ambient;
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
	cudaTextureObject_t tex[5];
	t_uint2				tex_res[5];
}						t_scene;

typedef	struct			s_env
{
	t_cuda				*cuda;
	t_ui				*ui;

	char				*scene_file;
	int					scene_fd;
	t_scene				*scene;

	t_xml				*xml;
	t_cam				*cameras;

	t_gen				*gen_objects;
	t_gen				*gen_lights;

	int					debug;
	int					gpu;
	t_fps				fps;

	int					*pixel_data;
	int					target;

	t_texture			*textures;

	int					current_index_objects;
}						t_env;

void					init_cuda(t_env *e, t_cuda *cuda);

int						draw(t_env *e);
void					init_kernel(t_env *e);

void					render_cuda(t_cuda *cuda, int *pixel_data, int *target,
							t_gen		*gen_objects,
							t_gen		*gen_lights,
							float		u_time,
							t_scene			*scene_data,
							t_cam			*cameras_data,
							cudaTextureObject_t *tex0,
							cudaTextureObject_t *tex1,
							cudaTextureObject_t *tex2,
							cudaTextureObject_t *tex3,
							cudaTextureObject_t *skybox);

FT_FLOAT3				add_cl_float(FT_FLOAT3 v1, FT_FLOAT3 v2);
FT_FLOAT3				sub_cl_float(FT_FLOAT3 v1, FT_FLOAT3 v2);
FT_FLOAT3				cross_vect(FT_FLOAT3 v1);
FT_FLOAT3				rotz(FT_FLOAT3 dir, float roll);
FT_FLOAT3				roty(FT_FLOAT3 dir, float yaw);
FT_FLOAT3				rotx(FT_FLOAT3 dir, float pitch);
FT_FLOAT3				rotcam(FT_FLOAT3 vect, float rad_pitch, float rad_yaw);

void					calculate_cos_sin_obj(t_object *obj);
void					init(GtkApplication *app, gpointer data);
void					init_gtk(GtkApplication *app, gpointer data);
void					init_cb_cam(t_env *e);
void					init_cb_light(t_env *e);
void					init_cb_main(t_env *e);
void					init_cb_object(t_env *e);
void					init_cb_scene(t_env *e);
void					init_cb_obj_cut(t_env *e);
void					init_cb_object_checkboard(t_env *e);
void					init_cb_object_diffmap(t_env *e);
void					init_cb_object_limit(t_env *e);
void					init_cb_object_sinwave(t_env *e);
void					init_gtk_cam(t_env *e);
void					init_gtk_css(t_env *e);
void					init_gtk_light(t_env *e);
void					init_gtk_obj_cut(t_env *e);
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

FT_FLOAT3				normalize_vect(FT_FLOAT3 v);

void					p_error(char *str, t_env *e);
void					s_error(char *str, t_env *e);
void					flush(t_env *e);
void					print_usage();
int						quit(t_env *e);

void					clear_surface(t_env *e);
void					gtk_render_events(t_env *e);

void					texture_init(t_env *e);
void					texture_destroy(t_env *e, t_texture *tex);

void					ui_add_cone(t_env *e);
void					ui_add_cylinder(t_env *e);
void					ui_add_ellipsoid(t_env *e);
void					ui_add_kube(t_env *e);
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
void					ui_obj_set_kube(t_env *e, t_kube *obj);
void					ui_obj_set_plane(t_env *e, t_plane *obj);
void					ui_obj_set_sphere(t_env *e, t_sphere *obj);
void					ui_obj_set_torus(t_env *e, t_torus *obj);
void					ui_obj_update(t_env *e, t_object *obj);
void					ui_obj_update_checkboard(t_env *e, t_object *obj);
void					ui_obj_update_cut(t_env *e, t_object *obj);
void					ui_obj_update_diff_map(t_env *e, t_object *obj);
void					ui_obj_update_limit(t_env *e, t_object *obj);
void					ui_obj_update_sinwave(t_env *e, t_object *obj);
void					ui_obj_update_cut_check(t_env *e, t_object *obj);
void					ui_obj_update_limit_plane_check(t_env *e, \
														t_object *obj);
void					ui_obj_update_limit_fix_check(t_env *e, \
													t_object *obj);

void					update_fps(t_fps *fps);

void					xml_allocate_cam(t_env *e);
int						xml_check_attr(t_env *e, char **att);
int						xml_check_char(char c);
int						xml_check_float(FT_FLOAT3 *clf, float f, int mod);
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
void					xml_data_lil_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_normale(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_opacity(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_option(t_env *e, char **attributes, \
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
										int *i, FT_FLOAT3 *f);
void					xml_init(t_env *e);
void					xml_get_file(t_env *e);
void					xml_list_add_first(t_node **begin, t_node *node);
void					xml_list_clean(t_env *e, t_node **list);
t_node					*xml_list_new(char type);

void					xml_node_cam(t_env *e, char *node);
void					xml_node_clean(char ***target);
void					xml_node_cone(t_env *e, char *node);
void					xml_node_cylinder(t_env *e, char *node);
void					xml_node_ellipsoid(t_env *e, char *node);
void					xml_node_kube(t_env *e, char *node);
void					xml_node_light(t_env *e, char *node);
void					xml_node_plane(t_env *e, char *node);
void					xml_node_scene(t_env *e, char *node, char mod);
void					xml_node_sphere(t_env *e, char *node);
void					xml_node_torus(t_env *e, char *node);

void					xml_parse_nodes(t_env *e);
void					xml_push_cam(t_env *e, t_node *list);
void					xml_push_cone(t_env *e, t_node *list);
void					xml_push_cyl(t_env *e, t_node *list);
void					xml_push_ellipsoid(t_env *e, t_node *list);
void					xml_push_kube(t_env *e, t_node *list);
void					xml_push_light(t_env *e, t_node *list);
void					xml_push_plane(t_env *e, t_node *list);
void					xml_push_sphere(t_env *e, t_node *list);
void					xml_push_torus(t_env *e, t_node *list);

void					xml_save_scene(t_env *e, char *filename);
void					xml_write_flags(const int flags, const int fd);
void					xml_write_color(const int color, const int fd);
void					xml_write_int(const char *name, const float data, \
										const int fd);
void					xml_write_float(const char *name, const float data, \
										const int fd);
void					xml_write_float3(const char *name, \
										const FT_FLOAT3 data, const int fd);

void					xml_write_cameras(t_env *e, const int fd, \
										t_cam *cameras);
void					xml_write_cone(t_cone *cone, const int fd);
void					xml_write_cylinder(t_cylinder *cyl, const int fd);
void					xml_write_lights(t_env *e, const int fd);
void					xml_write_ellipsoid(t_ellipsoid *elli, const int fd);
void					xml_write_plane(t_plane *plane, const int fd);
void					xml_write_sphere(t_sphere *sphere, const int fd);
void					xml_write_torus(t_torus *torus, const int fd);
void					xml_write_kube(t_kube *kube, const int fd);

#endif
