NAME = rt

CC = 					clang
CFLAGS +=				-Wall -Wextra -Werror
OFLAGS := 				-O2
RM := 					rm -rf

INC = $(addprefix $(INC_PATH)/,$(INC_NAMES))
INC_PATH = ./includes

LIBFT := $(LIBFT_PATH)/libft.a
LIBFT_PATH := ./libft
LIBFT_INC_PATH := ./libft
LIBFTFLAGS := -lft

LIBMATHFLAGS := -lm

GTK_CFLAGS	=	$(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS	=	$(shell pkg-config --libs gtk+-3.0)

OPENCL :=				-framework OpenCL

INC_NAMES = 			$(NAME).h \
						cl.h \
						ui.h \
						gen.h

OBJ =					$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ_PATH =				./obj
OBJ_NAME =				$(SRC_NAME:.c=.o)

SRC =					$(addprefix $(SRC_PATH)/,$(SRC_NAME))
SRC_PATH =				./src
SRC_NAME =	 			cl/cl_compute.c \
						cl/cl_construct.c \
						cl/cl_create_buffer.c \
						cl/cl_destruct.c \
						cl/cl_print_error.c \
						init.c \
						gen/gen_add.c \
						gen/gen_remove_mem_index.c \
						gen/gen_remove_index.c \
						gen/gen_get_index_ptr.c \
						gen/gen_get_ptr_index.c \
						gen/gen_print.c \
						gen/gen_construct.c \
						gen/gen_destruct.c \
						main.c \
						opencl_compute.c \
						rotations.c \
						tools.c \
						ui/add/ui_add_cone.c \
						ui/add/ui_add_cylinder.c \
						ui/add/ui_add_ellipsoid.c \
						ui/add/ui_add_plane.c \
						ui/add/ui_add_sphere.c \
						ui/add/ui_add_torus.c \
						ui/callback/cb_about_dialog.c \
						ui/callback/cb_ambient_update.c \
						ui/callback/cb_cam_dir.c \
						ui/callback/cb_cam_fov_update.c \
						ui/callback/cb_cam_manager.c \
						ui/callback/cb_cam_nav.c \
						ui/callback/cb_cam_pos.c \
						ui/callback/cb_cartoon_radio.c \
						ui/callback/cb_cone_angle.c \
						ui/callback/cb_configure_draw_area.c \
						ui/callback/cb_cylinder_radius.c \
						ui/callback/cb_depth_update.c \
						ui/callback/cb_ellipsoid_axis.c \
						ui/callback/cb_ellipsoid_radius.c \
						ui/callback/cb_export_dialog.c \
						ui/callback/cb_light_manager.c \
						ui/callback/cb_light_nav.c \
						ui/callback/cb_light_params.c \
						ui/callback/cb_light_pos.c \
						ui/callback/cb_obj_checkboard.c \
						ui/callback/cb_obj_color.c \
						ui/callback/cb_obj_combo_type.c \
						ui/callback/cb_obj_diff.c \
						ui/callback/cb_obj_dir.c \
						ui/callback/cb_obj_jump.c \
						ui/callback/cb_obj_plane_limit_btn.c \
						ui/callback/cb_obj_limit_dir.c \
						ui/callback/cb_obj_limit_pos.c \
						ui/callback/cb_obj_nav_add.c \
						ui/callback/cb_obj_nav_del.c \
						ui/callback/cb_obj_nav_next.c \
						ui/callback/cb_obj_nav_prev.c \
						ui/callback/cb_obj_opacity.c \
						ui/callback/cb_obj_pos.c \
						ui/callback/cb_obj_reflex.c \
						ui/callback/cb_obj_refrac.c \
						ui/callback/cb_obj_sinwave_btn.c \
						ui/callback/cb_obj_sinwave_param1.c \
						ui/callback/cb_obj_sinwave_param2.c \
						ui/callback/cb_obj_spec.c \
						ui/callback/cb_obj_texture_diff.c \
						ui/callback/cb_obj_texture_diff_chooser.c \
						ui/callback/cb_plane_disk_radius.c \
						ui/callback/cb_postproc_radio.c \
						ui/callback/cb_render_btnpress.c \
						ui/callback/cb_render_btnrelease.c \
						ui/callback/cb_render_draw.c \
						ui/callback/cb_render_keypress.c \
						ui/callback/cb_render_keyrelease.c \
						ui/callback/cb_render_update_size.c \
						ui/callback/cb_resolution_update.c \
						ui/callback/cb_save_btn.c \
						ui/callback/cb_sphere_radius.c \
						ui/callback/cb_supersampling_update.c \
						ui/callback/cb_tool_bar.c \
						ui/callback/cb_torus_radius.c \
						ui/gdkrgba_to_int.c \
						ui/gtk_main_loop.c \
						ui/gtk_render_events.c \
						ui/init/init_cb_cam.c \
						ui/init/init_cb_light.c \
						ui/init/init_cb_main.c \
						ui/init/init_cb_object.c \
						ui/init/init_cb_object_checkboard.c \
						ui/init/init_cb_object_diffmap.c \
						ui/init/init_cb_object_limit.c \
						ui/init/init_cb_object_sinwave.c \
						ui/init/init_cb_scene.c \
						ui/init/init_gtk_cam.c \
						ui/init/init_gtk_css.c \
						ui/init/init_gtk_light.c \
						ui/init/init_gtk_object.c \
						ui/init/init_gtk_object_checkboard.c \
						ui/init/init_gtk_object_diffmap.c \
						ui/init/init_gtk_object_effects.c \
						ui/init/init_gtk_object_limit.c \
						ui/init/init_gtk_object_sinwave.c \
						ui/init/init_gtk_scene.c \
						ui/init/init_gtk_toolbar.c \
						ui/init/init_gtk_win.c \
						ui/init/init_gtk.c \
						ui/ui_cam.c \
						ui/ui_cam_update.c \
						ui/ui_light_update.c \
						ui/ui_obj.c \
						ui/ui_obj_jump.c \
						ui/ui_obj_set_cone.c \
						ui/ui_obj_set_cylinder.c \
						ui/ui_obj_set_ellipsoid.c \
						ui/ui_obj_set_plane.c \
						ui/ui_obj_set_sphere.c \
						ui/ui_obj_set_torus.c \
						ui/ui_obj_update.c \
						ui/ui_obj_update_effects.c \
						update_fps.c \
						vectors.c \
						xml/data/xml_data_angle.c \
						xml/data/xml_data_flag.c \
						xml/data/xml_data_axis_size.c \
						xml/data/xml_data_brightness.c \
						xml/data/xml_data_color.c \
						xml/data/xml_data_diffuse.c \
						xml/data/xml_data_dir.c \
						xml/data/xml_data_height.c \
						xml/data/xml_data_min_max.c \
						xml/data/xml_data_normale.c \
						xml/data/xml_data_opacity.c \
						xml/data/xml_data_pos.c \
						xml/data/xml_data_radius.c \
						xml/data/xml_data_reflex.c \
						xml/data/xml_data_refrac.c \
						xml/data/xml_data_shrink.c \
						xml/data/xml_data_specular.c \
						xml/data/xml_data_type.c \
						xml/object/xml_cameras.c \
						xml/object/xml_cones.c \
						xml/object/xml_cylinders.c \
						xml/object/xml_ellipsoid.c \
						xml/object/xml_lights.c \
						xml/object/xml_planes.c \
						xml/object/xml_spheres.c \
						xml/object/xml_torus.c \
						xml/save/xml_save_camera.c \
						xml/save/xml_save_cone.c \
						xml/save/xml_save_cylinder.c \
						xml/save/xml_save_data.c \
						xml/save/xml_save_ellipsoid.c \
						xml/save/xml_save_light.c \
						xml/save/xml_save_plane.c \
						xml/save/xml_save_scene.c \
						xml/save/xml_save_sphere.c \
						xml/save/xml_save_torus.c \
						xml/xml.c \
						xml/xml_check_attr.c \
						xml/xml_list.c \
						xml/xml_nodes.c \
						xml/xml_scene.c \
						xml/xml_tools.c \
						ui/callback/cb_skybox_check.c \
						ui/callback/cb_obj_cut_check.c \
						ui/init/init_gtk_obj_cut.c \
						ui/init/init_cb_obj_cut.c \
						ui/callback/cb_obj_cut_x.c \
						ui/callback/cb_obj_cut_y.c \
						ui/callback/cb_obj_cut_z.c 

default: gpu

all: libft
	@echo "$(GREEN)Checking for RT$(EOC)"
	@make $(NAME)

$(NAME): $(SRC) $(INC) $(OBJ_PATH) $(OBJ)
	@echo "$(GREEN)Compiling $(NAME)$(EOC)"
	$(CC) -o $@ $(OBJ) -L$(LIBFT_PATH) $(LIBFTFLAGS) $(GTK_CLIBS) $(LIBMATHFLAGS) $(OPENCL) $(ASANFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDES_PATH) $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIBFT_INC_PATH) $(GTK_CFLAGS) $(GPU_MACRO) $(KEYS) $(DEBUG_MACRO) $(ASANFLAGS)

$(OBJ_PATH):
	@echo "$(GREEN)Creating ./obj path and making binaries from source files$(EOC)"
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/cl
	@mkdir $(OBJ_PATH)/xml
	@mkdir $(OBJ_PATH)/xml/data
	@mkdir $(OBJ_PATH)/xml/object
	@mkdir $(OBJ_PATH)/xml/save
	@mkdir $(OBJ_PATH)/gen
	@mkdir $(OBJ_PATH)/ui
	@mkdir $(OBJ_PATH)/ui/add
	@mkdir $(OBJ_PATH)/ui/callback
	@mkdir $(OBJ_PATH)/ui/init
	@mkdir $(OBJ_PATH)/event

CPU:
	@echo "$(GREEN)Checking for CPU ONLY RT$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make cpu_flags $(NAME)

cpu: libft CPU
cpu_flags:
$(eval GPU_MACRO = )

GPU:
	@echo "$(GREEN)Checking for GPU accelerated RT$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make gpu_flags $(NAME)

gpu: libft GPU
gpu_flags:
	$(eval GPU_MACRO = -DGPU)

debuggpu: debuglibft
	@echo "$(GREEN)So you want to compile RT with GPU and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for GPU accelerated RT with debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make debug_flag gpu_flags $(NAME)

debugasangpu: debugasanlibft
	@echo "$(GREEN)So you want to compile RT with GPU and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for GPU accelerated RT with ASAN debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make debug_asan_flag gpu_flags $(NAME)


debugcpu: debuglibft
	@echo "$(GREEN)So you want to compile RT with CPU mode forced and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for CPU ONLY RT with debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make debug_flag cpu_flags $(NAME)

debugasancpu: debugasanlibft
	@echo "$(GREEN)So you want to compile RT with CPU mode forced and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for CPU ONLY RT with ASAN debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make debug_asan_flag cpu_flags $(NAME)

debug_flag:
	$(eval DEBUG_MACRO = -DDEBUG -g)

debug_asan_flag:
	$(eval DEBUG_MACRO = -DDEBUG -g)
	$(eval ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer)

debuglibft:
	@echo "$(GREEN)Checking for Libft library with ASan$(EOC)"
	make -C $(LIBFT_PATH)/ debug libft.a

debugasanlibft:
	@echo "$(GREEN)Checking for Libft library with ASan$(EOC)"
	make -C $(LIBFT_PATH)/ debugasan libft.a

clean:
	@echo "$(GREEN)Cleaning...$(EOC)"
	@echo "$(GREEN)Deleting .obj files$(EOC)"
	@rm -rf $(OBJ_PATH)

fclean: fcleanlibft clean
	@echo "$(GREEN)Full cleaning...$(EOC)"
	@echo "$(GREEN)Deleting $(NAME) binary$(EOC)"
	@rm -rf $(NAME)

libft:
	@echo "$(GREEN)Checking for Libft library$(EOC)"
	make -C $(LIBFT_PATH)/ libft.a
	@echo ""
	@read -p "Please press enter to continue..."
	@echo ""

cleanlibft:
	@echo "$(GREEN)Cleaning Libft folder$(EOC)"
	make -C $(LIBFT_PATH)/ clean

fcleanlibft: cleanlibft
	@echo "$(GREEN)Full cleaning Libft$(EOC)"
	make -C $(LIBFT_PATH)/ fclean

re: fclean fcleanlibft default

installbrewshit:
	@echo "$(B_GREEN)Updating $(EOC)$(B_RED)brew$(EOC)$(B_GREEN) database...$(EOC)"
	@brew update
	@echo "$(B_GREEN)Applying $(EOC)$(B_RED)brew$(EOC)$(B_GREEN) updates...$(EOC)"
	@brew update
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtk+$(EOC)$(B_GREEN) from brew...$(EOC)"
	@brew install -f gtk+
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtk+3$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f gtk+3
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtk-chtheme$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f gtk-chtheme
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtk-mac-integration$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f gtk-mac-integration
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtkdatabox$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f gtkdatabox
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtkextra$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f gtkextra
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)gtkspell3$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f gtkspell3
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)pygtk$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f pygtk
	@echo "$(B_GREEN)Installing $(EOC)$(B_RED)adwaita-icon-theme$(EOC)$(B_GREEN) from brew...$(EOC)"
	brew install -f adwaita-icon-theme

norme:
	norminette $(SRC_PATH)
	norminette $(INC_PATH)
	norminette $(LIBFT_PATH)

usage:
	@echo "\n$(B_RED)A REDIGER!!!!$(EOC)\n"


.PHONY: all clean fclean re libft cpu gpu cleanlibft fcleanlibft debug usage norme

GREY =					\x1b[2;29m
BLACK =					\x1b[2;30m
RED =					\x1b[2;31m
GREEN =					\x1b[2;32m
YELL =					\x1b[2;33m
BLUE =					\x1b[2;34m
PINK =					\x1b[2;35m
CYAN =					\x1b[2;36m
WHIT =					\x1b[2;37m
WHIBLK =				\x1b[2;40m
WHIRED =				\x1b[2;41m
WHIGRE =				\x1b[2;42m
WHIYEL =				\x1b[2;43m
WHIBLU =				\x1b[2;44m
WHIPI =					\x1b[2;45m
WHICYA =				\x1b[2;46m
B_GREY =				\x1b[1;29m
B_BLACK =				\x1b[1;30m
B_RED =					\x1b[1;31m
B_GREEN =				\x1b[1;32m
B_YELL =				\x1b[1;33m
B_BLUE =				\x1b[1;34m
B_PINK =				\x1b[1;35m
B_CYAN =				\x1b[1;36m
B_WHIT =				\x1b[1;37m
B_WHIBLK =				\x1b[1;40m
B_WHIRED =				\x1b[1;41m
B_WHIGRE =				\x1b[1;42m
B_WHIYEL =				\x1b[1;43m
B_WHIBLU =				\x1b[1;44m
B_WHIPI =				\x1b[1;45m
B_WHICYA =				\x1b[1;46m
U_GREY =				\x1b[4;29m
U_BLACK =				\x1b[4;30m
U_RED =					\x1b[4;31m
U_GREEN =				\x1b[4;32m
U_YELL =				\x1b[4;33m
U_BLUE =				\x1b[4;34m
U_PINK =				\x1b[4;35m
U_CYAN =				\x1b[4;36m
U_WHIT =				\x1b[4;37m
U_WHIBLK =				\x1b[4;40m
U_WHIRED =				\x1b[4;41m
U_WHIGRE =				\x1b[4;42m
U_WHIYEL =				\x1b[4;43m
U_WHIBLU =				\x1b[4;44m
U_WHIPI =				\x1b[4;45m
U_WHICYA =				\x1b[4;46m
IC_GREY =				\x1b[2;29m
IC_BLACK =				\x1b[2;30m
IC_RED =				\x1b[2;31m
IC_GREEN =				\x1b[2;32m
IC_YELL =				\x1b[2;33m
IC_BLUE =				\x1b[2;34m
IC_PINK =				\x1b[2;35m
IC_CYAN =				\x1b[2;36m
IC_WHIT =				\x1b[2;37m
IC_WHIBLK =				\x1b[2;40m
IC_WHIRED =				\x1b[2;41m
IC_WHIGRE =				\x1b[2;42m
IC_WHIYEL =				\x1b[2;43m
IC_WHIBLU =				\x1b[2;44m
IC_WHIPI =				\x1b[2;45m
IC_WHICYA =				\x1b[7;46m
EOC =					\x1b[0m
