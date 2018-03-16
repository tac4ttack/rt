NAME = 					rt

CC = 					clang
CFLAGS +=				-Wall -Wextra -Werror
OFLAGS := 				-O2
RM := 					rm -rf

INC = 					$(addprefix $(INC_PATH)/,$(INC_NAMES))
INC_PATH =				./includes

LIBFT :=				$(LIBFT_PATH)/libft.a
LIBFT_PATH :=			./libft
LIBFT_INC_PATH :=		./libft
LIBFTFLAGS :=			-lft

LIBMATHFLAGS :=			-lm

GTK_CFLAGS	=	$(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS	=	$(shell pkg-config --libs gtk+-3.0)

OPENCL :=				-framework OpenCL

INC_NAMES = 			$(NAME).h \
						cl.h

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
						hud.c \
						init.c \
						gen/gen_add.c \
						gen/gen_construct.c \
						gen/gen_destruct.c \
						main.c \
						opencl_compute.c \
						rotations.c \
						tools.c \
						ui/cb_ambient_update.c \
						ui/cb_configure_draw_area.c \
						ui/cb_depth_update.c \
						ui/cb_draw_render.c \
						ui/cb_postproc_radio.c \
						ui/cb_render_btnpress.c \
						ui/cb_render_keypress.c \
						ui/cb_render_keyrelease.c \
						ui/cb_resolution_update.c \
						ui/gtk.c \
						ui/gtk_main_loop.c \
						ui/gtk_render_events.c \
						ui/ui_cam.c \
						ui/ui_obj.c \
						update_fps.c \
						vectors.c \
						xml/xml.c \
						xml/xml_cameras.c \
						xml/xml_check_attr.c \
						xml/xml_cones.c \
						xml/xml_cylinders.c \
						xml/xml_data_float.c \
						xml/xml_data_float3.c \
						xml/xml_data_int.c \
						xml/xml_data_vector.c \
						xml/xml_lights.c \
						xml/xml_list.c \
						xml/xml_nodes.c \
						xml/xml_planes.c \
						xml/xml_scene.c \
						xml/xml_spheres.c \
						xml/xml_tools.c

default: gpu

all: libft
	@echo "$(GREEN)Checking for RT$(EOC)"
	@make $(NAME)

$(NAME): $(SRC) $(INC) $(OBJ_PATH) $(OBJ)
	@echo "$(GREEN)Compiling $(NAME)$(EOC)"
	$(CC) -o $@ $(OBJ) -L$(LIBFT_PATH) $(LIBFTFLAGS) $(GTK_CLIBS) $(LIBMATHFLAGS) $(OPENCL) $(ASANFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDES_PATH) $(INC)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIBFT_INC_PATH) $(GTK_CFLAGS) $(GPU_MACRO) $(KEYS) $(DEBUG_MACRO) $(ASANFLAGS)

$(OBJ_PATH):
	@echo "$(GREEN)Creating ./obj path and making binaries from source files$(EOC)"
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/cl
	@mkdir $(OBJ_PATH)/xml
	@mkdir $(OBJ_PATH)/gen
	@mkdir $(OBJ_PATH)/ui
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

debuggpu: fclean debuglibft
	@echo "$(GREEN)So you want to compile RT with GPU and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for GPU accelerated RT with ASAN debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make debug_flag gpu_flags $(NAME)

debugcpu: fclean debuglibft
	@echo "$(GREEN)So you want to compile RT with CPU mode forced and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for CPU ONLY RT with ASAN debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make debug_flag cpu_flags $(NAME)

debug_flag:
	$(eval DEBUG_MACRO = -DDEBUG -g)
	$(eval ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer)

debuglibft:
	@echo "$(GREEN)Checking for Libft library with ASan$(EOC)"
	make -C $(LIBFT_PATH)/ debug libft.a

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
