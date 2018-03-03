NAME		=	gtk

SRCS_PATH	=	./

SRCS_NAME	=	main.c

OBJS_NAME 	= 	$(SRCS_NAME:.c=.o)

OBJS_PATH	=	./objs
LFT_PATH	=	./libft
INCS_PATH	=	./

GTK_CFLAGS	=	$(shell pkg-config --cflags gtk+-3.0)
GTK_CLIBS	=	$(shell pkg-config --libs gtk+-3.0)

CC			=	gcc -fdiagnostics-color=auto

CFLAGS		=	-O3 -I$(LFT_PATH) -I$(INCS_PATH)-Wall -Wextra -Werror -ffast-math -funroll-loops
CFLAGS		+=	$(GTK_CFLAGS)

CLIBS		=	-O3 -lm -L$(LFT_PATH) -lft
CLIBS		+=	$(GTK_CLIBS)

SRCS		=	$(addprefix $(SRCS_PATH)/,$(SRCS_NAME))
OBJS		=	$(addprefix $(OBJS_PATH)/,$(OBJS_NAME))

all: $(NAME)

$(NAME): 		$(OBJS)
				make -C $(LFT_PATH)
				gcc $^ -o $@ $(CLIBS)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
				@mkdir $(OBJS_PATH) 2> /dev/null || true
				$(CC) -o $@ -c $< $(CFLAGS)

clean:
				rm -rf $(OBJS)
				@rm -rf $(OBJS_PATH) 2> /dev/null || true
				make -C $(LFT_PATH) clean

fclean:
				rm -rf $(OBJS)
				rm -rf $(NAME)
				@rm -rf $(OBJS_PATH) 2> /dev/null || true
				make -C $(LFT_PATH) fclean

re: 			fclean all
