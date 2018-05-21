MODULE_NAME :=	$(PARENT_NAME)/vec2

MODULE_SRCS :=	vec2_add.c			\
				vec2_cast1.c		\
				vec2_cast2.c		\
				vec2_cpy.c			\
				vec2_div.c			\
				vec2_dot_product.c	\
				vec2_fill.c			\
				vec2_mul.c			\
				vec2_neg.c			\
				vec2_norm.c			\
				vec2_normalize.c	\
				vec2_sub.c			\

MODULE_INCS :=	libft_math/vec2.h

$(call addmodule) ## DO NOT EDIT THIS LINE
