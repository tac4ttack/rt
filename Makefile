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

OS_TEST := $(shell uname)
ifeq ($(OS_TEST), Darwin)
INC_NAMES = 			$(NAME).h \
						mac_keys.h
MLXFLAGS =				-framework OpenGL -framework AppKit
KEYS =					-DMAC_KEYS
OS_VERSION_TEST := $(shell uname -r | cut -d . -f 1)
endif
ifeq  ($(OS_VERSION_TEST),16)
OS_NAME =				"Sierra"
MLX_PATH =				./mlx/mlx_sierra
else ifeq ($(OS_TEST), Darwin)
OS_NAME =				"El_Capitan"
MLX_PATH =				./mlx/mlx_capitan
endif
ifeq ($(OS_TEST),"Linux")
OS_NAME =				"Linux"
MLX_PATH =				./mlx/mlx_x11
INC_NAMES = 			$(NAME).h \
						linux_keys.h
MLXFLAGS =				-lmlx -lXext -lX11
KEYS =					-DLINUX_KEYS
endif

MLX =					$(MLX_PATH)/libmlx.a

OBJ =					$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ_PATH =				./obj
OBJ_NAME =				$(SRC_NAME:.c=.o)

SRC =					$(addprefix $(SRC_PATH)/,$(SRC_NAME))
SRC_PATH =				./src
SRC_NAME =  			gtk.c \
						gtk_main_loop.c \
						hud.c \
						init.c \
						main.c \
						mlx_image_draw.c \
						mlx_key_press.c \
						mlx_key_release.c \
						mlx_key_norepeat.c \
						mlx_key_events.c \
						mlx_main_loop.c \
						mlx_mouse.c \
						opencl_compute.c \
						opencl_error.c \
						opencl_init.c \
						opencl_memalloc.c \
						rotations.c \
						tools.c \
						ui_obj.c \
						ui_cam.c \
						update_fps.c \
						vectors.c \
						xml.c \
						xml_check_attr.c \
						xml_cameras.c \
						xml_cones.c \
						xml_cylinders.c \
						xml_data_float.c \
						xml_data_float3.c \
						xml_data_int.c \
						xml_data_vector.c \
						xml_lights.c \
						xml_list.c \
						xml_nodes.c \
						xml_planes.c \
						xml_scene.c \
						xml_spheres.c \
						hooks.c \
						xml_tools.c	

default: gpu

all: libft mlx
	@echo "$(GREEN)Checking for RT$(EOC)"
	@make -j $(NAME)

$(NAME): $(SRC) $(INC) $(OBJ_PATH) $(OBJ)
	@echo "$(GREEN)Compiling $(NAME) with $(OS_NAME) MLX version$(EOC)"
	$(CC) -o $@ $(OBJ) -L$(LIBFT_PATH) $(LIBFTFLAGS) $(GTK_CLIBS) $(MLX) $(MLXFLAGS) $(LIBMATHFLAGS) $(OPENCL) $(ASANFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDES_PATH) $(INC)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIBFT_INC_PATH) -I $(MLX_PATH) $(GTK_CFLAGS) $(GPU_MACRO) $(KEYS) $(DEBUG_MACRO) $(ASANFLAGS)

$(OBJ_PATH):
	@echo "$(GREEN)Creating ./obj path and making binaries from source files$(EOC)"
	@mkdir $(OBJ_PATH)

CPU:
	@echo "$(GREEN)Checking for CPU ONLY RT$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make -j cpu_flags $(NAME)

cpu: libft mlx CPU
cpu_flags:
$(eval GPU_MACRO = )

GPU:
	@echo "$(GREEN)Checking for GPU accelerated RT$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make -j gpu_flags $(NAME)

gpu: libft mlx GPU
gpu_flags:
	$(eval GPU_MACRO = -DGPU)

debuggpu: fclean debuglibft mlx
	@echo "$(GREEN)So you want to compile RT with GPU and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for GPU accelerated RT with ASAN debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make -j debug_flag gpu_flags $(NAME)

debugcpu: fclean debuglibft mlx
	@echo "$(GREEN)So you want to compile RT with CPU mode forced and DEBUG enabled hu?$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' when switching back to debug mode disabled$(EOC)"
	@echo "$(GREEN)Checking for CPU ONLY RT with ASAN debug flags enabled$(EOC)"
	@echo "$(YELL)Be sure to do a 'make fclean' before switching between normal and CPU forced mode$(EOC)"
	@make -j debug_flag cpu_flags $(NAME)

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

fclean: fcleanlibft cleanmlx clean 
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

mlx:
	@echo "$(GREEN)Checking for MLX library$(EOC)"
	make -C $(MLX_PATH)/ libmlx.a
	@echo ""
	@read -p "Please press enter to continue..."
	@echo ""

cleanmlx:
	@echo "$(GREEN)Cleaning Minilibx folder$(EOC)"
	@make -C ./mlx/mlx_capitan/ clean
	@make -C ./mlx/mlx_sierra/ clean
	@make -C ./mlx/mlx_x11/ clean

re: fclean fcleanlibft cleanmlx default

norme:
	norminette $(SRC_PATH)
	norminette $(INC_PATH)
	norminette $(LIBFT_PATH)

usage:
	@echo "\n$(B_RED)Please use one of the following commands:$(EOC)\n"
	@echo "\tCompile and compute with one $(GREEN)CPU$(EOC) thread -> $(B_YELL)make cpu$(EOC)\n"
	@echo "\tCompile the $(GREEN)LIBFT$(EOC) -> $(B_YELL)make libft$(EOC)\n"
	@echo "\tCompile the $(GREEN)MLX$(EOC) (according to your OS) -> $(B_YELL)make mlx$(EOC)\n"
	@echo "\tCheck the $(GREEN)42 C STANDARD$(EOC) in sources and includes directories -> $(B_YELL)make norme$(EOC)\n"
	@echo "\tClean the $(GREEN)$(NAME)$(EOC) directory from object files -> $(B_YELL)make clean$(EOC)\n"
	@echo "\tClean the $(GREEN)LIBFT$(EOC) directory from object files -> $(B_YELL)make cleanlibft$(EOC)\n"
	@echo "\tClean the $(GREEN)MLX$(EOC) directory from object files -> $(B_YELL)make cleanmlx$(EOC)\n"
	@echo "\tRemove object files and binaries from $(GREEN)$(NAME) LIBFT and MLX$(EOC) directories -> $(B_YELL)make fclean$(EOC)\n"
	@echo "\tRemove object files and binaries from $(GREEN)LIBFT$(EOC) directory -> $(B_YELL)make fcleanlibft$(EOC)\n"
	@echo "\tRemove object files and binaries from $(GREEN)$(NAME)$(EOC) directory then compile it again using one $(GREEN)CPU$(EOC) thread -> $(B_YELL)make re$(EOC)\n"
	@echo "\t$(B_RED)NOT IMPLEMENTED YET!$(EOC) Compile and compute with $(GREEN)OpenCL$(EOC) using multiple threads -> $(B_YELL)make gpu$(EOC)\n"
	@echo "\tIf you want to activate the debugging output add \
	$(GREEN)debug$(EOC) before -> $(B_YELL)make debug cpu$(EOC)\n"

.PHONY: all clean fclean re libft mlx cpu gpu cleanlibft cleanmlx fcleanlibft debug usage norme

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
