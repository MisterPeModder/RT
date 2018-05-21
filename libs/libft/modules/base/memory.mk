MODULE_NAME :=	$(PARENT_NAME)/memory

MODULE_SRCS :=	ft_bzero.c		\
				ft_memalloc.c	\
				ft_memccpy.c	\
				ft_memchr.c		\
				ft_memcmp.c		\
				ft_memcpy.c		\
				ft_memdel.c		\
				ft_memdup.c		\
				ft_memmove.c	\
				ft_memset.c		\

MODULE_INCS :=	libft_base/memory.h

$(call addmodule) ## DO NOT EDIT THIS LINE
