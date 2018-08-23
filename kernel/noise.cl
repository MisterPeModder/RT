/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:59:30 by jhache            #+#    #+#             */
/*   Updated: 2018/08/22 06:08:17 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Call me to have a perfect val for a 3D
*/

static float		perlin3d(t_env_noise *noise, float x, float y, float z)
{
	int				i;
	float			res;
	float			amp;
	float			freq;
	float			max_amp;

	res = 0.f;
	amp = 1.f;
	freq = 1.f;
	max_amp = 0;
	i = 0;
	while (i < noise->depth)
	{
		res += noise3d(noise, x * freq, y * freq, z * freq) * amp;
		if (max_amp < amp)
			max_amp = amp;
		amp *= noise->pers;
		freq *= 2.f;
		i++;
	}
	res /= max_amp;
	res = fabs(res);
	return (res);
}

/*
** Procedural texture function for sinus marble effect.
** c1 is light gray, c2 is white.
*/
static float3		sin_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			res;
	float			val;

	c1 = (float3)(1.0f, 1.0f, 1.0f);
	c2 = (float3)(0.7f, 0.7f, 0.7f);
	val = 1.f - sqrt(fabs(native_sin(2.f * M_PI_F *
		perlin3d(noise, x, y, z))));
	res = c1 * (1.f - val) + c2 * val;
	return (res);
}

/*
** Procedural texture function for line marble effect.
** c1 is light gray, c2 is white.
*/
static float3		line_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			res;
	float			val;
	int 			line;
	float			perturb;

	line = 30;
	perturb = 0.25f;
	c1 = (float3)(0.7f, 0.7f, 0.7f);
	c2 = (float3)(1.0f, 1.0f, 1.0f);
	val = (1 - native_cos(line * 2 * M_PI_F * (x / 256 +
		perturb * perlin3d(noise, x, y, z)))) / 2;
	res = c1 * (1 - val) + c2 * val;
	return (res);
}

/*
** Procedural texture function for wood effect.
** c1 is light brown, c2 is dark brown.
*/
static float3		wood_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			res;
	float			val;
	float			val1;
	float			threshold;

	threshold = 0.3f;
	c1 = (float3)(0.87f, 0.72f, 0.53f);
	c2 = (float3)(0.52f, 0.26f, 0.11f);
	res = (float3)(0.0f, 0.0f, 0.0f);
	val = fmod(perlin3d(noise, x, y, z), threshold);
	if (val > threshold / 2)
		val = threshold - val;
	val1 = (1 - cos(M_PI_F * val / (threshold / 2))) / 2;
	res.x = c1.x * (1 - val1) + c2.x * val1;
	res.y = c1.y * (1 - val1) + c2.y * val1;
	res.z = c1.z * (1 - val1) + c2.z * val1;
	return (res);
}

/*
** Procedural texture function for water effect.
** c1 is light brown, c2 is dark brown.
*/
static float3		water_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			res;
	float			val;
	float			val1;
	float			pertub;
	int				line;

	line = 5;
	pertub = 0.4f;
	c2 = (float3)(0.8f, 0.8f, 1.0f);
	c1 = (float3)(0.0f, 0.4f, 0.5f);
//	val1 = perlin3d(noise, x, y, z, pertub, 5);
	val1 = (1 - native_sin(line * 2 * M_PI_F * (x / 256 +
		pertub * perlin3d(noise, x, y, z)))) / 2;
	res.x = c1.x * (1 - val1) + c2.x * val1;
	res.y = c1.y * (1 - val1) + c2.y * val1;
	res.z = c1.z * (1 - val1) + c2.z * val1;
	return (res);
}
/*
** Determine what is the perturbation of the color. Just "if" things.
*/
static float3		ft_choose(t_env_noise *e_noise, float x, float y, float z)
{
	float3			res;

	res = (float3)(0.0f, 0.0f, 0.0f);
	if (e_noise->type == WOOD)
		res = wood_noise(e_noise, x, y, z);
	else if (e_noise->type == WATER)
		res = water_noise(e_noise, x, y, z);
	else if (e_noise->type == PERLIN)
	{
		res.x = perlin3d(e_noise, x, y, z);
		res.y = res.x;
		res.z = res.x;
	}
	else if (e_noise->type == SIN_MARBLE)
		res = sin_marble_noise(e_noise, x, y, z);
	else if (e_noise->type == LINE_MARBLE)
		res = line_marble_noise(e_noise, x, y, z);
	else
		return ((float3)(1.0f, 1.0f, 1.0f));
	if (res.x < 0 || res.y < 0 || res.z < 0)
		res = (float3)(1.0f, 1.0f, 1.0f);
	return (res);
}

static float3		noise(global t_clint *hash, t_rt_result *r, float3 vec)
{
	int				i;
	float3			res;
	t_env_noise		e_noise;

	i = 0;
	res = (float3)(0.0f, 0.0f, 0.0f);
	if (r->obj->mat.has_noise == 0)
		return ((float3)(1.0f, 1.0f, 1.0f));
	while (i < 256)
	{
		e_noise.hash[i] = hash[i];
		i++;
	}
	e_noise.pers = r->obj->mat.noise.pers;
	e_noise.seed = r->obj->mat.noise.seed;
	e_noise.type = r->obj->mat.noise.type;
	e_noise.depth = r->obj->mat.noise.octave;
	e_noise.amp = r->obj->mat.noise.amp;
	res = ft_choose(&e_noise, vec.x, vec.y, vec.z);
	return (res);
}
