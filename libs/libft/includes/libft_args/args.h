/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:10:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/27 14:37:17 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

# include "args_internal.h"

/*
** Argument Parser functions.
*/

/*
** Anti-norm tricks...
*/
# ifndef ARGS_DEFS_H

typedef int			t_arg_error;

# endif

/*
** init_args: initalizes the parser's main structure.
**
** -mode:       determines how the parser should behave.
**              see t_args::mode in args_defs.h for more infos.
** -err_to_str: a funtion pointer that converts an error code to a string.
**              see t_args::err_to_str in args_defs for more infos.
** -usage:      the program's usage, can be NULL.
**
** returns:     the main structure.
*/
t_args				*init_args(int mode,
		char *(*err_to_str)(int, const char *), const char *usage);

/*
** free_args: frees the memory allocated by the args parser.
**
** -args: the main structure, set to NULL after being freed.
*/
void				free_args(t_args **args);

/*
** clear_arg_errors: clears the current error state.
*/
int					clear_arg_errors(t_args *args);

/*
** set_arg_error: 'throws' an error.
**
** -args:    the main structure.
** -errcode: whatever error you want to throw.
** -detail:  extra information about the error, such as the cause.
**
** returns:  returns 0 if errcode == ARG_VALID, -1 otherwise.
*/
int					set_arg_error(t_args *args, t_arg_error errcode,
		const char *detail);

/*
** has_arg_errors: returns wheter the parser is in an errored state.
**
** -args:   the main structure.
** -mask:   a bit-mask that prevent certain errors to be checked.
**          you might want to set the mask to ARG_VALID to ignore the error
**          thrown when to program is run without args for instance.
**
** returns: 1 if there is an error, 0 if not.
*/
int					has_arg_errors(const t_args *args, int mask);

/*
** put_arg_error: prints the current error into STDERR.
**
** -prefix:  will be displayed before the error followed by ':'.
**          can be NULL.
** -args:    the main structure.
*/
void				put_arg_error(const char *prefix, const t_args *args);

/*
** show_usage: prints the usage in STDERR.
*/
void				show_usage(const t_args *args);

/*
** add_arg_options: adds new options, pretty self-explanatory.
**
** -args:    the main structure.
** -options: options to be added, you can define multiple options at once.
**           example: passing "la" will add the "-l" and the "-a" options.
**
** returns:  0 if no error occured, -1 otherwise.
*/
int					add_arg_options(t_args *args, const char *options);

/*
** add_arg_param: adds a new parameter.
**
** -args:   the main structure.
** -name:   name of the parameter.
** -size:   the size of its arguments.
** -policy: tells how the size value is used,
**          see t_argv_plst::policy for more infos.
**
** returns: 0 if no error occured, -1 otherwise.
*/
int					add_arg_param(t_args *args, const char *name,
		size_t size, t_size_policy policy);

/*
** parse_args: parses the arguments.
**
** -args:   the main structure.
** -argc:   the number of arguments.
** -argv:   the arguments themselves.
**
** returns: 0 if no error occured, -1 otherwise.
*/
int					parse_args(t_args *args, int argc, char **argv);

/*
** has_arg: checks if the argument exists, can be an option or a parameter
**
** -args:   the main structure.
** -name:   the name of the arguement. (can be "my-param" or "a" for instance)
** -type:   the type of argument to search, if type == ARG_DEFAULT or
**          is undifined the function will always throw an ARG_UNKWON_ERR.
**
** returns: 0 if no error occured, -1 otherwise.
*/
int					has_arg(const t_args *args, char *name,
		t_argtype type);

/*
** is_arg_listed: check if an argument has been added.
**
** -args:   the main structure.
** -name:   the name of the arguement. (can be "my-param" or "a" for instance)
** -type:   the type of argument to search, if type == ARG_DEFAULT or
**          is undifined the function will always throw an ARG_UNKWON_ERR.
**
** returns: 0 if no error occured, -1 otherwise.
*/
int					is_arg_listed(const t_args *args, const char *name,
		t_argtype type);

/*
** get_pargv: get the value of a parameter.
**
** -args:   the main structure.
** -name:   the name of the parameter.
**
** returns: NULL is paramter was not found and is present in the args list.
**          Returns a pointer to the argv structure if found.
*/
t_argv_plst			*get_pargv(t_args *args, const char *name);

#endif
