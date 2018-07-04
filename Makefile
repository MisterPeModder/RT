# Project settings
NAME := rt

## LIBS
LIBS := $(CURDIR)/libs

# Libft
LIBFT_PATH := $(LIBS)/libft
LIBFT_NAME := ft
LIBFT := $(LIBFT_PATH)/lib$(LIBFT_NAME).a
LIBFT_MODULES := base containers math

# Libftjson
LIBFT_JSON_PATH := $(LIBS)/ft_json
LIBFT_JSON_NAME := ftjson
LIBFT_JSON := $(LIBFT_JSON_PATH)/lib$(LIBFT_JSON_NAME).a

# SDL2
LIBSDL_PATH := $(LIBS)/sdl2
LIBSDL_NAME := SDL2
LIBSDL := $(LIBSDL_PATH)/lib/lib$(LIBSDL_NAME).a

# SDL2_TTF
LIBSDL_TTF_PATH := $(LIBS)/sdl2_ttf
LIBSDL_TTF_NAME := SDL2_ttf
LIBSDL_TTF := $(LIBSDL_PATH)/lib/lib$(LIBSDL_TTF_NAME).a

UNAME := $(shell uname -s 2> /dev/null)

ifeq ($(UNAME), Darwin)
	FRAMEWORKS := -framework OpenCL
else
	FRAMEWORKS :=
endif

# Basic definitions
SRC_PATH := srcs
OBJ_PATH := .bin
INC_PATH := includes

# OPENCL
KERNEL_PATH := kernel
KERNELSRC_PATH := $(KERNEL_PATH)/kernel.cl
OCL_FLAGS := -I$(INC_PATH) -Ikernel -Werror

# Compiler flags
CPPFLAGS := -iquote$(INC_PATH) -isystem$(LIBFT_PATH)/includes -isystem$(LIBFT_JSON_PATH)/includes
CFLAGS :=	-Wall -Wextra -Werror -Wmissing-prototypes -Wsign-conversion	\
			-g -O3 `$(LIBSDL_PATH)/sdl2-config --cflags`					\
			-D KERNEL_PATH='"$(KERNELSRC_PATH)"' -D OPENCL_BUILD_FLAGS='"$(OCL_FLAGS)"'
LDFLAGS :=	-L$(LIBFT_PATH) -L$(LIBFT_JSON_PATH)						\
			-l$(LIBFT_NAME) -l$(LIBFT_JSON_NAME) -l$(LIBFT_NAME) -lm	\
			`$(LIBSDL_PATH)/sdl2-config --libs` -l$(LIBSDL_TTF_NAME)

# Commands
CC := gcc
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
PRINT := printf
NORM := norminette

SRCS_NAMES :=	core.c							\
				img.c							\
				main.c							\
				sdl_render.c					\

SRCS_NAMES +=	controllers/controller_event.c	\
				controllers/controller_motion.c	\
				controllers/controller_update.c	\
				controllers/mappings_add.c		\

SRCS_NAMES +=	events/events.c					\
				events/loop.c					\
				events/move.c					\
				events/window_events.c			\

SRCS_NAMES +=	objects/cone.c					\
				objects/cylinder.c				\
				objects/disk.c					\
				objects/material.c				\
				objects/objects.c				\
				objects/paraboloid.c			\
				objects/sphere.c				\
				objects/triangle.c				\

SRCS_NAMES +=	ocl/kernel_args.c				\
				ocl/load_first_args.c			\
				ocl/ocl_data.c					\
				ocl/ocl_render.c				\
				ocl/ocl_stack_init.c			\
				ocl/read_kernel.c				\

SRCS_NAMES +=	parsing/args.c					\
				parsing/cam.c					\
				parsing/from_json.c				\
				parsing/from_json2.c			\
				parsing/lights.c				\
				parsing/meshes.c				\
				parsing/meshes_utils.c			\
				parsing/options.c				\
				parsing/read.c					\
				parsing/scene.c					\

SRCS_NAMES +=	utils/angle.c					\
				utils/filters.c					\
				utils/rotate.c					\
				utils/timer.c					\
				utils/utils.c					\
				utils/vec3cl.c					\

SRCS := $(addprefix $(SRC_PATH)/,$(SRCS_NAMES))
OBJS := $(addprefix $(OBJ_PATH)/,$(SRCS_NAMES:.c=.o))

OBJ_DIRS := $(sort $(dir $(OBJS)))

INCS :=	controller.h			\
		filters.h				\
		image.h					\
		internal_ocl_types_c.h	\
		internal_ocl_types_cl.h	\
		move.h					\
		objects.h				\
		ocl_common_structs.h	\
		ocl_data.h				\
		ocl_types.h				\
		rt.h					\
		scene.h					\
		sdl_defs.h				\
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

all: $(LIBFT) $(LIBFT_JSON) $(LIBSDL) $(LIBSDL_TTF) $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(GREEN)done!$(RESET)"
endif
	@$(PRINT) "\n$(GREY)Compiling $(RESET)$(NAME)$(GREY): $(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(FRAMEWORKS)
	@$(PRINT) "$(GREEN)done!$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_PATH) VERBOSE=0 MODULES="$(LIBFT_MODULES)"

$(LIBFT_JSON):
	@make -C $(LIBFT_JSON_PATH) VERBOSE=0 LIBFT_PATH=$(LIBFT_PATH)

$(LIBSDL):
	@cd $(LIBSDL_PATH) && ./configure --prefix $(LIBSDL_PATH)
	@make -C $(LIBSDL_PATH)
	@make -C $(LIBSDL_PATH) install

$(LIBSDL_TTF):
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install freetype &> /dev/null || true
	@cd $(LIBSDL_TTF_PATH) && ./configure --prefix $(LIBSDL_PATH)
	@make -C $(LIBSDL_TTF_PATH)
	@make -C $(LIBSDL_TTF_PATH) install

$(OBJ_DIRS):
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
	@$(RMDIR) $(OBJ_DIRS) 2> /dev/null || true
	@make -C $(LIBFT_PATH) clean > /dev/null
	@make -C $(LIBFT_JSON_PATH) LIBFT_PATH=$(LIBFT_PATH) clean > /dev/null
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)object files!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) 2> /dev/null || true
	@$(RM) $(TEST_NAME) 2> /dev/null || true
	@make -C $(LIBFT_PATH) fclean > /dev/null
	@make -C $(LIBFT_JSON_PATH) LIBFT_PATH=$(LIBFT_PATH) fclean > /dev/null
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

.PHONY: all clean fclean re sdl_install norm
