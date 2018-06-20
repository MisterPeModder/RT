# Project settings
NAME := rt

## LIBS
LIBS := $(CURDIR)/libs


# Libft
LIBFT_PATH := $(LIBS)/libft
LIBFT_NAME := ft
LIBFT := $(LIBFT_PATH)/lib$(LIBFT_NAME).a

# Libftjson
LIBFT_JSON_PATH := $(LIBS)/ft_json
LIBFT_JSON_NAME := ftjson
LIBFT_JSON := $(LIBFT_JSON_PATH)/lib$(LIBFT_JSON_NAME).a

# MLX
UNAME := $(shell uname -s 2> /dev/null)

ifeq ($(UNAME), Darwin)
	MLX_PATH := $(LIBS)/minilibx_macos
	FRAMEWORKS := -framework OpenCL -framework OpenGL -framework AppKit
else
	MLX_PATH := $(LIBS)/minilibx_x11
	FRAMEWORKS := -lXext -lX11
	EXTRA_FLAGS := -D X11_MLX
endif

MLX_NAME := mlx
MLX = $(MLX_PATH)/lib$(MLX_NAME).a

# Basic definitions
SRC_PATH := srcs
OBJ_PATH := .bin
INC_PATH := includes

# OPENCL
KERNEL_PATH := kernel
KERNELSRC_PATH := $(KERNEL_PATH)/kernel.cl
OCL_FLAGS := -I$(INC_PATH) -Ikernel -Werror

SUBDIRS := $(addprefix $(OBJ_PATH)/, objects)

# Compiler flags
CPPFLAGS := -iquote$(INC_PATH) -isystem$(LIBFT_PATH)/includes -isystem$(LIBFT_JSON_PATH)/includes -isystem$(MLX_PATH)
CFLAGS :=	-Wall -Wextra -Werror -Wmissing-prototypes -Wsign-conversion	\
			-g -O3															\
			-D KERNEL_PATH='"$(KERNELSRC_PATH)"' -D OPENCL_BUILD_FLAGS='"$(OCL_FLAGS)"'
LDFLAGS :=	-L$(LIBFT_PATH) -L$(LIBFT_JSON_PATH) -L$(MLX_PATH)	\
			-l$(LIBFT_NAME) -l$(LIBFT_JSON_NAME) -l$(LIBFT_NAME) -l$(MLX_NAME) -lm

# Commands
CC := gcc
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
PRINT := printf
NORM := norminette

SRCS_NAMES :=	angle.c			\
				cam.c			\
				core.c			\
				events.c		\
				events2.c		\
				from_json.c		\
				img.c			\
				lights.c		\
				main.c			\
				move.c			\
				ocl_render.c	\
				ocl_data.c		\
				read_kernel.c	\
				rotate.c		\
				scene.c			\
				timer.c			\
				utils.c			\
				vec3cl.c		\

SRCS_NAMES +=	objects/cone.c		\
				objects/objects.c	\
				objects/sphere.c	\
				objects/cylinder.c	\
				objects/disk.c		\
				objects/triangle.c	\
				objects/cube.c		\
				objects/pyramid.c	\
				objects/paraboloid.c\

SRCS := $(addprefix $(SRC_PATH)/,$(SRCS_NAMES))

OBJS := $(addprefix $(OBJ_PATH)/,$(SRCS_NAMES:.c=.o))

INCS :=	image.h					\
		internal_ocl_types_c.h	\
		internal_ocl_types_cl.h	\
		mlx_defs.h				\
		move.h					\
		objects.h				\
		ocl_common_structs.h	\
		ocl_data.h				\
		ocl_types.h				\
		rt.h					\
		scene.h					\
		timer.h					\

# THE NORM IS REAL
NORM_LOG := norm.log
NORM_FILES := $(SRCS) $(addprefix $(INC_PATH)/,$(INCS))

# Cosmetic features
DETAILED = 1
RESET := \033[0m
GREY := \033[90m
GREEN := \033[32m
YELLOW := \033[93m
DYELLOW := \033[33m
UNDERLINE := \033[4m

all: $(LIBFT) $(LIBFT_JSON) $(MLX) $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ_PATH) $(SUBDIRS) $(OBJS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(GREEN)done!$(RESET)"
endif
	@$(PRINT) "\n$(GREY)Compiling $(RESET)$(NAME)$(GREY): $(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(FRAMEWORKS)
	@$(PRINT) "$(GREEN)done!$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_PATH) VERBOSE=0

$(LIBFT_JSON):
	@make -C $(LIBFT_JSON_PATH) VERBOSE=0 LIBFT_PATH=$(LIBFT_PATH)

$(MLX):
	@printf "\033[90mCompiling \033[0m$(MLX_NAME)\033[90m: \033[0m"
	@make -C $(MLX_PATH) &> /dev/null
	@printf "\033[32mdone!\n\n"

$(OBJ_PATH) $(SUBDIRS):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(addprefix $(INC_PATH)/,$(INCS))
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(RESET)$(notdir $@)"
endif
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(EXTRA_FLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) -r *.dSYM
	@$(RM) $(OBJS) 2> /dev/null || true
	@$(RMDIR) $(OBJS_DIRS) 2> /dev/null || true
	@make -C $(LIBFT_PATH) clean > /dev/null
	@make -C $(LIBFT_JSON_PATH) LIBFT_PATH=$(LIBFT_PATH) clean > /dev/null
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)object files!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) 2> /dev/null || true
	@$(RM) $(TEST_NAME) 2> /dev/null || true
	@make -C $(LIBFT_PATH) fclean > /dev/null
	@make -C $(LIBFT_JSON_PATH) LIBFT_PATH=$(LIBFT_PATH) fclean > /dev/null
	@make -C $(MLX_PATH) clean &> /dev/null || true
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)$(NAME) executable!$(RESET)\n\n"

re: fclean all

norm:
	@$(PRINT) "$(GREY)Checking $(RESET)The Norm$(GREY)...$(RESET)\n"
	@$(PRINT) "Found $(GREEN)$(words $(NORM_FILES))$(RESET) files!\n"
	@$(RM) $(NORM_LOG)
	@$(NORM) $(NORM_FILES) > $(NORM_LOG)
	@$(PRINT) "Norm Errors: "
	@cat $(NORM_LOG) | grep Error | wc -l | bc
	@$(PRINT) "See $(UNDERLINE)$(NORM_LOG)$(RESET) for details.\n"

.PHONY: all clean fclean re norm
