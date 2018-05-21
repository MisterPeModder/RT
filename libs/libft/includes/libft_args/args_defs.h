/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_defs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 17:13:35 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/28 15:25:54 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_DEFS_H
# define ARGS_DEFS_H

# include <stdlib.h>

/*
** Argument Parser definitions header:
** here are declared all of the types/constants used be the arg parser.
*/

/*
** t_argtype: enum
** Represents the types of arguments supported.
**
** -DEFAULT:   default argument type; stores all misc arguments
**             such as file names.
** -OPTION:    corresponds to flag arguments, (e.g: -a)
** -PARAMETER: corresponds to arguments than can have arguments themselves,
**             such as "--screen-dims 1600 900" or "-std=c89"
*/
typedef enum		e_argtype
{
	DEFAULT,
	OPTION,
	PARAMETER
}					t_argtype;

/*
** t_arg_error: enum
** Represents errors that may be thrown when parsing args.
** Errors can be 'ORed' together to form a bitmask.
**
** -ARG_VALID:          no errors, everything is fine.
** -ARG_EMPTY:          thrown when then program is executed without args.
** -ARG_MEM_ERROR:      thrown upon failing a memory allocation.
** -ARG_UNKNOWN_OPTION: thrown when an option does not exist.
** -ARG_UNKNOWN_PARAM:  thrown when a parameter does not exist.
** -ARG_PARAM_VALUE:    invalid parameter argument.
** -ARG_DEF_TWICE:      option/paramter is defined more than once.
** -ARG_UNSPECIFIED:    thrown when an empty option (single '-') is declered.
** -ARG_INVALID_SIZE:   number of paramter arguments does not match size policy.
** -ARG_UNKNOWN_ERR:    unknown error.
*/
typedef enum		e_arg_error
{
	ARG_VALID = 0,
	ARG_EMPTY = 1,
	ARG_MEM_ERROR = 2,
	ARG_UNKNOWN_OPTION = 4,
	ARG_UNKNOWN_PARAM = 8,
	ARG_PARAM_VALUE = 16,
	ARG_DEF_TWICE = 32,
	ARG_UNSPECIFIED = 64,
	ARG_INVALID_SIZE = 128,
	ARG_UNKNOWN_ERR = 256
}					t_arg_error;

/*
** t_size_policy: enum
** Different policies for the length of parameter arguments.
** (note: 'size' corresponds to the value size in the t_argv_plst struct)
**
** -SIZEP_MIN:   makes 'size' become the minimun size of the argument array.
** -SIZEP_FORCE: makes 'size' become the required size of the argument array.
** -SIZEP_MAX:   makes 'size' become the minimun size of the argument array.
** -SIZEP_ONE:   forces 'size' to 1, parameters with this policy will require
**               an equal character '=' instead of whitespce to declare
**               its argument.
*/
typedef enum		e_size_policy
{
	SIZEP_MIN,
	SIZEP_FORCE,
	SIZEP_MAX,
	SIZEP_ONE
}					t_size_policy;

/*
** t_argv_default: struct
** Contains all the default arguments.
**
** -argc: the number of arguments in the argc array.
** -argv: an array of strings, contains the arguments.
*/
typedef struct		s_argv_default
{
	size_t			argc;
	char			**argv;
}					t_argv_default;

/*
** t_argv_opts: struct
** Contains all the option arguments.
**
** -options_l: array of declared options
** -options_v: array of parsed options
*/
typedef struct		s_argv_opts
{
	char			*options_l;
	char			*options_v;
}					t_argv_opts;

/*
** t_argv_plst: struct
** Contains a parameter's data.
**
** -name:      name of the parameter
** -size:      desired number of arguments, depends on the size policy.
** -policy:    size policy, affects how the size property should used.
** -values:    array of strings that contains the parsed arguments.
** -validator: used to determine if the arguments are valid,
**             returns 0 if invlid and 1 otherwise.
**             for example, you can use the validator function to make sure
**             that the argument array conains only numbers.
**             Leave NULL if you do want to check the parameter's arguments.
*/
typedef struct		s_argv_plst
{
	char			*name;
	int				defined;
	size_t			size;
	t_size_policy	policy;
	char			**values;
	int				(*validator)(const struct s_argv_plst *);
}					t_argv_plst;

/*
** t_argv: union
** Contains all the types of arguments.
*/
typedef union		u_argv
{
	t_argv_default	d;
	t_argv_opts		o;
	t_argv_plst		l;
}					t_argv;

struct s_args;

/*
** t_arglst: struct
** A simply linked list that contains all of the argument structures.
**
** -argv: the contained argument struct.
** -type: the type of argument.
** -next: a pointer to the next list element.
*/
typedef struct		s_arglst
{
	t_argv			argv;
	t_argtype		type;
	struct s_arglst	*next;
	struct s_args	*args;
}					t_arglst;

/*
** t_argmode: enum
** Contains values that can be used in the main structure's mode bit-mask.
**
** -ARG_MDEFAULT:            default mode.
** -ARG_MSIMPLE:             activates simple parameters mode, options are
**                           disabled (functions related to options will always
**                           throw an error) and parameters are passed with one
**                           dash '-' (e.g: --std=c89 in normal mode is
**                           -std=c89 in simple mode)
** -ARG_MDISCONTINUOUS:      allows default arguments (like files) no to be
**                           next to each other.
** -ARG_MALLOW_FILES_BEFORE: allows default arguments to be before options and
**                           parameters.
** -ARG_MENABLE_SEP:         allows the separator option ('--') to be used.
**                           this options makes that all the options that come
**                           after it te be treated as default arguments
**                           regardless of how they are formated.
** -ARG_MSINGLE_PARAMS:      cause an error to be thrown if the same parameter
**                           is present more than once.
*/
typedef enum		e_argmode
{
	ARG_MDEFAULT = 0,
	ARG_MSIMPLE = 1,
	ARG_MDISCONTINUOUS = 2,
	ARG_MALLOW_FILES_BEFORE = 4,
	ARG_MENABLE_SEP = 8,
	ARG_MSINGLE_PARAMS = 16
}					t_argmode;

/*
** t_args: struct
** The argument parser's main structure.
**
** -arglst:     the argument list.
** -err_to_str: a function pointer that converts an error code (t_arg_error)
**              into a string, this function MUST dynamically alloctate the
**              returned string, or it will crash.
**              Can return NULL if error is not supported
** -mode:       a bit-mask composed of constants of type t_argmode 'ORed
**              together that tells how the parser should behave.
** -errcode:    current error code of type t_arg_error.
** -errinfo:    holds extra information about the current error state.
** -usage:      store the usage of this pro	gram.
*/
typedef struct		s_args
{
	t_arglst		*arglst;
	char			*(*err_to_str)(int, const char *);
	int				mode;
	t_arg_error		errcode;
	char			*errinfo;
	char			*usage;
}					t_args;

#endif
