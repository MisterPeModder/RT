/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:58:37 by jhache            #+#    #+#             */
/*   Updated: 2018/08/20 15:33:22 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		cut_x_axis(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float2 c,
		int *face
		)
{
	float	delta;
	float3	tmp;

	tmp = c.x * u + origin;
	if (c.x < 0 && c.y > 0 && dot(origin - obj->pos, obj->dir) < 0)
	{
		delta = dot((obj->pos - origin), obj->dir) / dot(u, obj->dir);
		tmp = delta * u + origin;
		if (dot(tmp - obj->pos, tmp - obj->pos)
				<= obj->props.sphere.radius * obj->props.sphere.radius && delta > 0)
		{
			*face = 5;
			return (delta);
		}
		else
			*face = 1;
		return (c.y);
	}
	else if (dot(tmp - obj->pos, obj->dir) > 0)
	{
		delta = dot((obj->pos - origin), obj->dir) / dot(u, obj->dir);
		tmp = delta * u + origin;
		if (dot(tmp - obj->pos, tmp - obj->pos)
				<= obj->props.sphere.radius * obj->props.sphere.radius)
		{
			*face = 3;
			return (delta);
		}
		return (FLT_MAX);
	}
	return (c.x);
}

static float		cut_y_axis(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float2 c,
		int *face
		)
{
	float	delta;
	float3	tmp;

	tmp = c.x * u + origin;
	if (c.x < 0 && c.y > 0 && dot(origin - obj->pos, obj->facing) < 0)
	{
		delta = dot((obj->pos - origin), obj->facing) / dot(u, obj->facing);
		tmp = delta * u + origin;
		if (dot(tmp - obj->pos, tmp - obj->pos)
				<= obj->props.sphere.radius * obj->props.sphere.radius && delta > 0)
		{
			*face = 6;
			return (delta);
		}
		else
			*face = 1;
		return (c.y);
	}
	else if (dot(tmp - obj->pos, obj->facing) > 0)
	{
		delta = dot((obj->pos - origin), obj->facing) / dot(u, obj->facing);
		tmp = delta * u + origin;
		if (dot(tmp - obj->pos, tmp - obj->pos)
				<= obj->props.sphere.radius * obj->props.sphere.radius)
		{
			*face = 4;
			return (delta);
		}
		return (FLT_MAX);
	}
	return (c.x);
}

static float		cut_z_axis(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float2 c,
		int *face
		)
{
	float	delta;
	float3	tmp;

	tmp = c.x * u + origin;
	if (c.x < 0 && c.y > 0 && dot(origin - obj->pos, obj->right) < 0)
	{
		delta = dot((obj->pos - origin), obj->right) / dot(u, obj->right);
		tmp = delta * u + origin;
		if (dot(tmp - obj->pos, tmp - obj->pos)
				<= obj->props.sphere.radius * obj->props.sphere.radius && delta > 0)
		{
			*face = 7;
			return (delta);
		}
		else
			*face = 1;
		return (c.y);
	}
	else if (dot(tmp - obj->pos, obj->right) > 0)
	{
		delta = dot((obj->pos - origin), obj->right) / dot(u, obj->right);
		tmp = delta * u + origin;
		if (dot(tmp - obj->pos, tmp - obj->pos)
				<= obj->props.sphere.radius * obj->props.sphere.radius)
		{
			*face = 2;
			return (delta);
		}
		return (FLT_MAX);
	}
	return (c.x);
}

static float		sphere_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	tmp;

	*face = 0;
	a = dot(u, u);
	tmp = origin - obj->pos;
	b = 2 * dot(u, tmp);
	c = dot(tmp, tmp) - obj->props.sphere.radius * obj->props.sphere.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	b = c > a ? a : c;
	c = c > a ? c : a;
	if (obj->props.sphere.axis != -1)
	{
		if (!obj->props.sphere.axis)
			return (cut_z_axis(obj, origin, u, (float2)(b, c), face));
		else if(obj->props.sphere.axis == 1)
			return (cut_x_axis(obj, origin, u, (float2)(b, c), face));
		else if(obj->props.sphere.axis == 2)
			return (cut_y_axis(obj, origin, u, (float2)(b, c), face));
	}
	if (b > 0 && c < 0)
		*face = 1;
	if (b < 0)
		b = c;
	return (b);
}

static float2		negative_sphere_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u
		)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	tmp;
	float2	ret;

	a = dot(u, u);
	tmp = origin - obj->pos;
	b = 2 * dot(u, tmp);
	c = dot(tmp, tmp) - obj->props.sphere.radius * obj->props.sphere.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return ((float2)(FLT_MAX, FLT_MAX));
	else if (delta == 0)
		return ((float2)(-b / (2 * a), -b / (2 * a)));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	ret[0] = c > a ? a : c;
	ret[1] = c > a ? c : a;
	return (ret);
}

static void			sphere_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	if (!face)
		r->normal = normalize(r->pos - o->pos);
	else if (face == 1)
		r->normal = -normalize(r->pos - o->pos);
	else if (face == 2 || face == 7)
		r->normal = face == 7 ? o->right : -o->right;
	else if (face == 3 || face == 5)
		r->normal = face == 3 ? o->dir : -o->dir;
	else if (face == 4 || face == 6)
		r->normal = face == 3 ? o->facing : -o->facing;
}
