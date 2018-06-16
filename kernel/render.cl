/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:04:19 by jhache            #+#    #+#             */
/*   Updated: 2018/06/16 12:22:07 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int constant		seed = 20;
static int constant		hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,
	247,247,40,185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,
	224,245,128,167,204,9,92,217,54,239,174,173,102,193,189,190,121,100,
	108,167,44,43,77,180,204,8,81,70,223,11,38,24,254,210,210,177,32,81,
	195,243,125,8,169,112,32,97,53,195,13,203,9,47,104,125,117,114,124,165,
	203,181,235,193,206,70,180,174,0,167,181,41,164,30,116,127,198,245,146,
	87,224,149,206,57,4,192,210,65,210,129,240,178,105,228,108,245,148,140,
	40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,232,50,217,
	64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
	193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,
	39,145,101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,
	120,67,87,167,135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,
	211,118,137,139,255,114,20,218,113,154,27,127,246,250,1,8,198,250,209,
	92,222,173,21,88,102,219};
// WTF ??????????? (serieux les gars...)

static float 			lin_inter(float x, float y, float s)
{
	return (x + s * (y - x));
}

static float 			smooth_inter(float x, float y, float s)
{
    //return (lin_inter(x, y, s * s * s * (s * (s * 6 - 15) + 10))); 
	return (lin_inter(x, y, s * s * (3 - 2 * s)));
}

static int				noise2(int x, int y)
{
	int 		tmp;

	tmp = hash[(y + seed) % 256];
	return hash[(tmp + x) % 256];
}

static float			noise2d(float x, float y)
{
	int 		s;
	int 		t;
	int 		u;
	int 		v;
	int 		x_int;
	int 		y_int;
	float 		low;
	float 		high;
	float 		x_frac;
	float 		y_frac;

	x_int = x;
	y_int = y;
	x_frac = x - x_int;
	y_frac = y - y_int;
	s = noise2(x_int, y_int);
	t = noise2(x_int + 1, y_int);
	u = noise2(x_int, y_int + 1);
	v = noise2(x_int + 1, y_int + 1);
	low = smooth_inter(s, t, x_frac);
	high = smooth_inter(u, v, x_frac);
	return (lin_inter(low, high, y_frac));
}

static float			perlin2d(float x, float y, float freq, int depth)
{
	int 		i;
	float 		xa = x * freq;
	float 		ya = y * freq;
	float 		amp = 1.0;
	float 		fin = 0;
	float 		div = 0.0;

	i = 0;
	fin = 0;
	amp = 1.0;
	xa = x * freq;
	ya = y * freq;
	while (i < depth)
	{
		div += 256 * amp;
		fin += noise2d(xa, ya) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
		i++;
	}
	return (fin/div);
}

static float3		compute_pixel_coor(constant t_cam *cam, unsigned int w,
		unsigned int h, unsigned int x, unsigned int y)
{
	float3			vec;
	float			fov;

	fov = tan(cam->fov / 2);
	vec.x = (2 * ((x + 0.5) / w) - 1) * w / (float)h * fov;
	vec.y = (1 - 2 * ((y + 0.5) / h)) * fov;
	vec.z = -1;
	rotate_x(&vec, cam->angle.x);
	rotate_y(&vec, cam->angle.y);
	rotate_z(&vec, cam->angle.z);
	return (normalize(vec));
}

/*
 ** raytrace: Handles the ray tracing operation.
 **
 ** -scene: the scene instance.
 ** -o: origin of the ray.
 ** -u: unit vector (direction) of that ray.
 ** -r: where the result will be stored.
 **
 ** returns: 1 if an intersection has been found, 0 otherwise.
 */

static int			raytrace(
		constant t_object *objs,
		size_t objs_num,
		float3 o,
		float3 u,
		t_rt_result *r
		)
{
	size_t			i;
	float			d;
	float			tmp;
	int				face;
	int				face_tmp;
	float2			t_neg;
	size_t			n;

	i = 0;
	d = FLT_MAX;
	while (i < objs_num)
	{
		switch (objs[i].type)
		{
			case OBJ_SPHERE:
				tmp = sphere_intersect(&objs[i], o, u);
				break;
			case OBJ_PLANE:
				tmp = plane_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_CONE:
				tmp = cone_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_CYLINDER:
				tmp = cylinder_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_DISK:
				tmp = disk_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_TRIANGLE:
				tmp = triangle_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_CUBE:
				tmp = cube_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_PYRAMID:
				tmp = pyramid_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_PARABOLOID:
				tmp = paraboloid_intersect(&objs[i], o, u);
				break;
			default:
				tmp = FLT_MAX;
		}
		n = 0;
		while (n < objs_num)
		{
			if (objs[n].negative)
			{
				switch (objs[n].type)
				{
					case OBJ_SPHERE:
						t_neg = negative_sphere_intersect(&objs[n], o, u);
						break;
					case OBJ_CUBE:
						t_neg = negative_cube_intersect(&objs[n], o, u);
						break;
					case OBJ_PYRAMID:
						t_neg = negative_pyramid_intersect(&objs[n], o, u);
						break;
					default:
						t_neg = (float2)(FLT_MAX, FLT_MAX);
				}
				if (tmp < t_neg[1] && tmp > t_neg[0])
					tmp = FLT_MAX;
			}
			n++;
		}
		if (objs[i].negative)
			tmp = FLT_MAX;
		if (tmp > 0 && tmp < d)
		{
			r->obj = objs + i;
			d = tmp;
			face = face_tmp;
		}
		++i;
	}
	if (d == FLT_MAX)
		return (0);
	r->dist = d;
	r->pos = u * d + o;
	switch (r->obj->type)
	{
		case OBJ_SPHERE:
			sphere_normal(r->obj, r);
			break;
		case OBJ_PLANE:
		case OBJ_DISK:
			plane_normal(r->obj, r, face);
			break;
		case OBJ_CONE:
			cone_normal(r->obj, r, face);
			break;
		case OBJ_CYLINDER:
			cylinder_normal(r->obj, r, face);
			break;
		case OBJ_TRIANGLE:
			triangle_normal(r->obj, r, face);
			break;
		case OBJ_CUBE:
			cube_normal(r->obj, r, face);
			break;
		case OBJ_PYRAMID:
			pyramid_normal(r->obj, r, face);
			break;
		case OBJ_PARABOLOID:
			paraboloid_normal(r->obj, r);
			break;
	}
	return (1);
}

/*
 ** shading: Handles the shading using the Phong algorithm.
 **
 ** -scene: the scene instance.
 ** -r: the primary ray's raytrace result.
 ** -c: where the color of the pixel will be stored.
 */

static float3		shading(
		constant t_object *objs, size_t objs_num,
		constant t_light *lights, size_t lights_num,
		t_rt_result *r
		)
{
	size_t			i;
	float3			lvec;
	t_rt_result		sink;
	float3			start;
	float3			result;
	float3			coef;
	float			perlin;

	i = 0;
	perlin = perlin2d(get_global_id(0), get_global_id(1), 0.015, 20);
	coef.r = perlin;
	coef.g = perlin;
	coef.b = perlin;
	result = r->obj->color / 10;
	while (i < lights_num)
	{
		lvec = normalize(lights[i].pos - r->pos);
		start = r->pos + 0.001f * r->normal;
		if (!raytrace(objs, objs_num, start, lvec, &sink)
				|| length(lights[i].pos - r->pos) < sink.dist)
			colorize(&lights[i], lvec, r, &result);
		++i;
	}
	return (result * coef);
}
