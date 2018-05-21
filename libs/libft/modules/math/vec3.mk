MODULE_NAME :=	$(PARENT_NAME)/vec3

MODULE_SRCS :=	vec3_add.c			\
				vec3_cast1.c		\
				vec3_cast2.c		\
				vec3_cpy.c			\
				vec3_div.c			\
				vec3_dot_product.c	\
				vec3_fill.c			\
				vec3_mul.c			\
				vec3_neg.c			\
				vec3_norm.c			\
				vec3_normalize.c	\
				vec3_sub.c			\

MODULE_INCS :=	libft_math/vec3.h

$(call addmodule) ## DO NOT EDIT THIS LINE
