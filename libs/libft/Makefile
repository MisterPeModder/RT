# Project settings
NAME := libft.a

# Basic definitions
MODULES_PATH := modules
SRC_PATH := srcs
OBJ_PATH := .bin
INC_PATH := includes

# Compiler flags
CPPFLAGS = -iquote$(INC_PATH)
CFLAGS := -Wall -Wextra -Werror -std=c89 -pedantic -Wmissing-prototypes -Wsign-conversion -g

# Commands
CC := gcc
LC = ar rcs
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
PRINT := printf
NORM := norminette

###############################################################
#                                                             #
#                 /!\  DO NOT EDIT BELOW  /!\                 #
#                                                             #
###############################################################

SRCS :=
INCS :=
OBJS :=

# Default modules if MODULES is not set.
DEFAULT_MODULES :=	args		\
					base		\
					containers	\
					gnl			\
					math		\

DEPS :=

ifndef MODULES
	MODULES := $(DEFAULT_MODULES)
endif

define addmodule
	$(eval SRCS += $(addprefix $(SRC_PATH)/$(MODULE_NAME)/,$(MODULE_SRCS)));
	$(eval INCS += $(addprefix $(INC_PATH)/,$(MODULE_INCS)));
	$(eval OBJS += $(addprefix $(OBJ_PATH)/$(MODULE_NAME)/,$(MODULE_SRCS:.c=.o)));
	$(eval -include $(addprefix $(MODULES_PATH)/, $(addsuffix .mk, $(MODULE_DEPS))));
endef

# Add the sources of each module.
-include $(addprefix $(MODULES_PATH)/, $(addsuffix .mk, $(MODULES)))

INCS := $(sort $(INCS))
SRCS := $(sort $(SRCS))
OBJS := $(sort $(OBJS))

# Adding all modules to vpath.
COLON := :
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)
VPATH = $(subst $(SPACE),$(COLON),$(addprefix $(SRC_PATH)/,$(strip $(MODULES))))

OBJS_DIRS := $(sort $(dir $(OBJS)))

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

# The rules are simple, you laugh, YOU LOOSE!

all: $(NAME)

$(NAME): $(OBJS_DIRS) $(OBJS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(GREEN)done!$(RESET)"
endif
	@$(PRINT) "\n$(GREY)Compiling $(RESET)$(NAME)$(GREY): $(RESET)"
	@$(LC) $(NAME) $(OBJS)
	@$(PRINT) "$(GREEN)done!$(RESET)\n"

$(OBJS_DIRS):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(RESET)$(notdir $@)"
endif
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) -r *.dSYM
	@$(RM) $(OBJS) 2> /dev/null || true
	@$(RMDIR) $(OBJS_DIRS) 2> /dev/null || true
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)object files!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) 2> /dev/null || true
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
