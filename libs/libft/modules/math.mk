MODULE_NAME :=	math

MODULE_DEPS :=

PARENT_NAME :=	math
SUBMODULES :=	calc	\
				vec2	\
				vec3	\

MODULE_SRCS :=

MODULE_INCS +=	libft_math/math.h	\

$(call addmodule) ## DO NOT EDIT THIS LINE

-include $(addprefix $(MODULES_PATH)/$(MODULE_NAME)/,$(addsuffix .mk,$(SUBMODULES)))
