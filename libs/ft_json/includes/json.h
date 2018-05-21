/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 10:07:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 16:48:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

# include "json_datatypes.h"

/*
** tells the parser wheter it ignore checking for extra
** non-whitspace characters after the main object.
*/
# define JFLAG_IGNORE_EXTRA 1

/*
** ignores comments.
*/
# define JFLAG_ALLOW_COMMENTS 2

/*
** json_from_file: parses a file's contents into a JSON object.
**
** -fd: the file descriptor.
** -flags: flags for the parser. NOTE: only the above flags may be used !
**
** example: json_from_file(42, JFLAG_ALLOW_EXTRA | JFLAG_INGORE_EXTRA);
**
** returns: a t_json_parse_res instance.
*/
t_json_parse_res		*json_from_file(int fd, int flags);

/*
** json_from_str: parses a string into a JSON object.
**
** -src: the source string.
** -flags: flags for the parser. NOTE: only the above flags may be used !
**
** returns: a t_json_parse_res instance.
*/
t_json_parse_res		*json_from_str(const char *src, int flags);

/*
** json_to_tab: converts the passed JSON value into an array.
**
** -val: the JSON value.
**
** returns: a string array containg each line of the serialized JSON value,
**          NULL if an error occured.
*/
char					**json_to_tab(const t_json_value *val);

/*
** json_to_str: converts the passed JSON value into a string.
**
** -val: the JSON value.
**
** returns: a string containg each line of the serialized JSON value,
**          NULL if an error occured.
*/
char					*json_to_str(const t_json_value *val);

/*
** json_to_file: puts the contents of a JSON object into a file.
**
** -obj: a pointer to a JSON object instance.
** -p: the file descriptor.
**
** returns: 1 if successful, 0 if not.
*/
int						json_to_file(const t_json_value *obj, int fd);

/*
** json_release_value: frees the passed JSON value.
**
** returns: always 1 to allow chaining.
*/
int						json_release(t_json_value **val);

/*
** json_release_file: frees the passed JSON file.
**
** -rel_obj: if 1, then the contained json object will be freed.
**           Otherwise the object will not be touched, this means YOU will have
**           to free it manually using json_release_value().
*/
void					json_release_file(t_json_parse_res **file, int rel_obj);

/*
** json_obj_get: gets the value stored at key k in a json OBJECT.
**
** -obj: the json object to search from.
** -k: the key;
**
** returns: a json value if found, null otherwise.
*/
t_json_value			*json_obj_get(const t_json_object *obj, const char *k);

/*
** json_arr_get: gets the value stored at index i in a json ARRAY.
**
** -arr: the json array to search from.
** -i: the index;
**
** returns: a json value if found, null otherwise.
*/
t_json_value			*json_arr_get(const t_json_array *arr, size_t i);

/*
** json_obj_put: stores a json_value into the passed object at key k.
** if a value already exists at key, it will be freed.
**
** returns: 1 if successful, 0 if not.
*/
int						json_obj_put(t_json_object *obj, t_json_value *v,
		const char *k);

/*
** json_arr_put: stores a json_value into the passed array at index i.
** if a value already exists at index, it will be freed.
**
** returns: 1 if successful, 0 if not.
*/
int						json_arr_put(t_json_array *arr, t_json_value *v,
		size_t i);

/*
** defines how prescise the serializer should be when handling doubles.
*/
# define JSON_FP_PRECISION 16

#endif
