MODULE_NAME :=	args

MODULE_DEPS :=	base

MODULE_SRCS :=	args_add.c			\
				args_del.c			\
				args_error.c		\
				args_get.c			\
				args_init.c			\
				args_parse.c		\
				args_parse_default.c\
				args_parse_option.c	\
				args_parse_param.c	\
				args_print.c		\

MODULE_INCS :=	libft_args/args.h			\
				libft_args/args_defs.h		\
				libft_args/args_internal.h	\

$(call addmodule) ## DO NOT EDIT THIS LINE
