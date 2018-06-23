/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 07:17:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 19:35:07 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
   static int			no_schemes(t_controller *c)
   {
   c->current_scheme = NULL;
   c->schemes = NULL;
   c->con_schemes = NULL;
   return (1);
   }

   static int			get_scheme(t_scheme *s, const char *name, t_json_object *o)
   {
   t_json_value	*tmp;
   t_hmiterator	it;

   s->name = name;
   if ((tmp = json_obj_get(o, "buttons")) && tmp->obj.type == JSON_OBJECT &&
   tmp->obj.data && tmp->obj.data->size)
   {
   s->buttons_len = tmp->obj.data->size;
   if (!(s->buttons_ids = malloc(sizeof(int) * s->buttons_len)))
   return (0);
   else if (!(s->bkeys_ids = malloc(sizeof(int) * s->buttons_len)))
   {
   free(s->buttons_ids);
   return (0);
   }
   hm_iter_init(tmp->obj.data, &it);
   while (hm_iter_next(&it))
   {
   if ((s->buttons_ids[it.i] =
   SDL_GameControllerGetButtonFromString(it.key)) !=
   SDL_CONTROLLER_BUTTON_INVALID)
   ;
   else if (it.value &&
   ((t_json_value *)it.value)->str.type == JSON_STRING &&
   (s->bkeys_ids[it.i] = SDL_GetKeyFromName(((t_json_value *)it.value)->str.value))
   != SDLK_UNKNOWN)
   ;
   else
   {
   free(s->buttons_ids);
   free(s->bkeys_ids);
   return (0);
   }
			//TODO MOVE THE ABOVE HORROR IN A FUNCTION
			}
			}
			else
			s->buttons_len = 0;
			if ((tmp = json_obj_get(o, "axis")) && tmp->obj.type == JSON_OBJECT)
			{

			}
			}

			static int			get_schemes(t_controller *c, const t_json_object *schemes,
			const t_json_object *data)
			{
			t_hmiterator	it;

			if (!schemes->data || !schemes->data->size)
			return (no_schemes(c));
			if (!(c->schemes = malloc(sizeof(t_scheme) * schemes->data->size)))
			return (0);
			hm_iter_init(schemes->data, &it);
			while (hm_iter_next(&it))
			{
			if (!it.value || ((t_json_value *)it.value)->obj.type != JSON_OBJECT ||
			!get_scheme(&c->schemes[it.i], it.key, &it.value->obj))
			{
			free(c->schemes);
return (0);
}
}
}

static int			options_controllers(t_rt *core, const t_json_object *data)
{
	t_json_value	*tmp;

	if ((tmp = json_obj_get(data, "mappings")))
	{
		if (tmp->arr.type != JSON_ARRAY || !add_sdl_mappings(&tmp->arr))
			return (0);
	}
	if ((tmp = json_obj_get(data, "schemes")))
	{
		if (tmp->obj.type != JSON_OBJECT ||
				!get_schemes(&core->controller, &tmp->obj, data))
			return (0);
	}
	else
		no_schemes(&core->controller);
	return (1);
}*/

int					options_parse(t_rt *core, const char *path)
{
	t_json_object	*obj;
/*	t_json_value	*tmp;*/
	(void)core;

	if (!(obj = &(json_file_read(path)->obj)))
		return (0);
	/*if ((tmp = json_obj_get(obj, "controllers")))
	  {
	  if (tmp->obj.type != JSON_OBJECT ||
	  !options_controllers(core, &tmp->obj))
	  return (rel_error("Couldn't parse controller options", &obj));
	  }*/
	json_release((t_json_value **)&obj);
	return (1);
}
