/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 01:40:49 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:25:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <libft_base/stringft.h>
#include "json.h"
#include "json_internal.h"

static void				json_release_value_helper(t_json_value *v)
{
	size_t				i;

	if (v->str.type == JSON_STRING && v->str.value)
		free(v->str.value);
	else if (v->obj.type == JSON_OBJECT && v->obj.data)
		hm_release(&v->obj.data, (void (*)(void *))&json_release_value_helper);
	else if (v->arr.type == JSON_ARRAY && v->arr.values)
	{
		i = 0;
		while (i < v->arr.values_num)
			if (v->arr.values[i++])
				json_release_value_helper(v->arr.values[i - 1]);
		free(v->arr.values);
	}
	free(v);
}

int						json_rd(t_json_value *v)
{
	size_t				i;

	if (!v)
		return (1);
	if (v->str.type == JSON_STRING && v->str.value)
		ft_strdel(&v->str.value);
	else if (v->obj.type == JSON_OBJECT && v->obj.data)
		hm_release(&v->obj.data, (void (*)(void *))&json_release_value_helper);
	else if (v->arr.type == JSON_ARRAY && v->arr.values)
	{
		i = 0;
		while (i < v->arr.values_num)
			if (v->arr.values[i++])
				json_release_value_helper(v->arr.values[i - 1]);
		ft_memdel((void **)&v->arr.values);
	}
	v->obj.type = JSON_NULL;
	return (1);
}

int						json_release(t_json_value **v)
{
	if (!v || !*v)
		return (1);
	json_release_value_helper(*v);
	*v = NULL;
	return (1);
}

void					json_release_file(t_json_parse_res **file, int rel_obj)
{
	if ((*file)->err)
		free((*file)->err);
	if (rel_obj && (*file)->obj)
		json_release(&(*file)->obj);
	ft_bzero(*file, sizeof(t_json_parse_res));
	free(*file);
	*file = NULL;
}

void					json_rel4lst(void *value, size_t n)
{
	(void)n;
	json_release_value_helper(value);
}
