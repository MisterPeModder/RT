MODULE_NAME :=	base

MODULE_DEPS :=

PARENT_NAME :=	base
SUBMODULES :=	character	\
				io			\
				list		\
				memory		\
				string		\

MODULE_SRCS :=

MODULE_INCS +=	libft.h				\
				libft_base/base.h	\

$(call addmodule) ## DO NOT EDIT THIS LINE

-include $(addprefix $(MODULES_PATH)/$(MODULE_NAME)/,$(addsuffix .mk,$(SUBMODULES)))
