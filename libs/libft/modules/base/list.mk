MODULE_NAME :=	$(PARENT_NAME)/list

MODULE_SRCS :=	ft_lst_pushback.c	\
				ft_lstadd.c			\
				ft_lstdel.c			\
				ft_lstdelone.c		\
				ft_lstextract.c		\
				ft_lstiter.c		\
				ft_lstlen.c			\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_lstrem.c			\

MODULE_INCS :=	libft_base/list.h

$(call addmodule) ## DO NOT EDIT THIS LINE
