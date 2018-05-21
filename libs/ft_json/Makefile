# Project settings
LIB_NAME := ftjson
NAME := lib$(LIB_NAME).a

# Libft
ifndef LIBFT_PATH
$(error missing LIBFT_PATH variable)
endif

LIBFT_NAME := ft
LIBFT := $(LIBFT_PATH)/lib$(LIBFT_NAME).a

# Basic definitions
SRC_PATH := srcs
OBJ_PATH := .bin
INC_PATH := includes

# Compiler flags
CPPFLAGS := -iquote$(INC_PATH) -isystem$(LIBFT_PATH)/includes
CFLAGS := -Wall -Wextra -Werror -std=c89 -pedantic -Wmissing-prototypes -Wsign-conversion -g

# Commands
CC := gcc
LC = ar rcs
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
PRINT := printf
NORM := norminette

SRCS_NAMES :=	json_check_number.c		\
				json_error.c			\
				json_from.c				\
				json_get.c				\
				json_lex_string.c		\
				json_lexing.c			\
				json_make_value.c		\
				json_number.c			\
				json_parse_array.c		\
				json_parse_obj_value.c	\
				json_parse_object.c		\
				json_parsing_helpers.c	\
				json_put.c				\
				json_release.c			\
				json_str_iterator.c		\
				json_stringify.c		\
				json_to_file.c			\
				json_to_str.c			\
				json_val_to_tab.c		\

SRCS := $(addprefix $(SRC_PATH)/,$(SRCS_NAMES))

OBJS := $(addprefix $(OBJ_PATH)/,$(SRCS_NAMES:.c=.o))

INCS :=			json.h				\
				json_datatypes.h	\
				json_internal.h		\

# THE NORM IS REAL
NORM_LOG := norm.log
NORM_FILES := $(SRCS) $(INCS)

# Cosmetic features
DETAILED = 1
RESET := \033[0m
GREY := \033[90m
GREEN := \033[32m
YELLOW := \033[93m
DYELLOW := \033[33m
UNDERLINE := \033[4m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(GREEN)done!$(RESET)"
endif
	@$(PRINT) "\n$(GREY)Compiling $(RESET)$(NAME)$(GREY): $(RESET)"
	@$(LC) $(NAME) $(OBJS) $(LIBFT)
	@$(PRINT) "$(GREEN)done!$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_PATH) VERBOSE=0

$(OBJ_PATH):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(addprefix $(INC_PATH)/,$(INCS))
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(RESET)$(notdir $@)"
endif
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) -r *.dSYM
	@$(RM) $(OBJS) 2> /dev/null || true
	@$(RMDIR) $(OBJS_DIRS) 2> /dev/null || true
	@make -C $(LIBFT_PATH) clean > /dev/null
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)object files!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) 2> /dev/null || true
	@make -C $(LIBFT_PATH) fclean > /dev/null
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)$(NAME) library!$(RESET)\n\n"

re: fclean all

norm:
	@$(PRINT) "$(GREY)Checking $(RESET)The Norm$(GREY)...$(RESET)\n"
	@$(PRINT) "Found $(GREEN)$(words $(NORM_FILES))$(RESET) files!\n"
	@$(RM) $(NORM_LOG)
	@$(NORM) $(NORM_FILES) >> $(NORM_LOG)
	@$(PRINT) "Norm Errors: "
	@cat $(NORM_LOG) | grep Error | wc -l | bc
	@$(PRINT) "See $(UNDERLINE)$(NORM_LOG)$(RESET) for details.\n"

.PHONY: all clean fclean re norm
