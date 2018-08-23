/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:59:30 by jhache            #+#    #+#             */
/*   Updated: 2018/08/23 04:17:00 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Call me to have a perfect val for a 3D! I'll loop on
** the generation of the noise value to precise the result!
*/
static float		perlin3d(
	t_env_noise *noise,
	float x,
	float y,
	float z,
	float amp
	)
{
	int				i;
	float			res;
	float			freq;
	float			sum_freq;

	res = 0.f;
	freq = 1.f;
	sum_freq = 0.f;
	i = 0;
	while (i < noise->depth)
	{
		res += noise3d(noise, x * amp, y * amp, z * amp) * freq;
		sum_freq += freq;
		freq *= noise->pers;
		amp *= 2.f;
		i++;
	}
	res /= sum_freq;
	res = fabs(res);
	return (res);
}

/*
** Procedural texture function for sinus marble effect.
** c2 is light gray, c1 is white.
*/
static float3		sin_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			res;
	float			val;

	c1 = (float3)(1.0f, 1.0f, 1.0f);
	c2 = (float3)(0.6f, 0.6f, 0.6f);
	if (noise->pers == -1)
		noise->pers = 0.4;
	val = 1.f - sqrt(fabs(native_sin(2.f * M_PI_F *
				perlin3d(noise, x, y, z, (noise->amp == -1 ? 0.3f : noise->amp)))));
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

	line = 20;
	perturb = 0.15f;
	c1 = (float3)(0.2f, 0.2f, 0.2f);
	c2 = (float3)(1.f, 1.f, 1.f);
	if (noise->pers == -1)
		noise->pers = 0.7;
	val = (1 - native_cos(line * 2 * M_PI_F * (x / 256 +
					perturb * perlin3d(noise, x, y, z, (noise->amp == -1 ? 0.2f : noise->amp))))) / 2;
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
	float			threshold;

	threshold = 0.2f;
	c1 = (float3)(0.75f, 0.6f, 0.4f);
	c2 = (float3)(0.4f, 0.20f, 0.16f);
	if (noise->pers == -1)
		noise->pers = 0.4;
	val = fmod(perlin3d(noise, x, y, z,
				(noise->amp == -1 ? 1.f : noise->amp)), threshold);
	if (val > threshold / 2)
		val = threshold - val;
	val = (1 - cos(M_PI_F * val / (threshold / 2))) / 2;
	res.x = c1.x * (1 - val) + c2.x * val;
	res.y = c1.y * (1 - val) + c2.y * val;
	res.z = c1.z * (1 - val) + c2.z * val;
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
	float			pertub;
	int				line;

	line = 5;
	pertub = 0.4f;
	c2 = (float3)(0.8f, 0.8f, 1.0f);
	c1 = (float3)(0.0f, 0.4f, 0.5f);
	val = (1 - native_sin(line * 2 * M_PI_F * (x / 256 +
					pertub * perlin3d(noise, x, y, z,
						(noise->amp == -1 ? 1.f : noise->amp))))) / 2;
	res.x = c1.x * (1 - val) + c2.x * val;
	res.y = c1.y * (1 - val) + c2.y * val;
	res.z = c1.z * (1 - val) + c2.z * val;
	return (res);
}
/*
** Determine what is the perturbation of the color. Just "if" things.
*/
static float3		ft_choose(t_env_noise *e_noise, float x, float y, float z)
{
	float3			res;

	res = (float3)(0.f, 0.f, 0.f);
	if (e_noise->type == WOOD)
		res = wood_noise(e_noise, x, y, z);
	else if (e_noise->type == WATER)
		res = water_noise(e_noise, x, y, z);
	else if (e_noise->type == PERLIN)
	{
		res.x = perlin3d(e_noise, x, y, z, (e_noise->amp == -1.f ? 0.3f : e_noise->amp));
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
		res = (float3)(1.f, 1.f, 1.f);
	return (res);
}

static float3		noise(constant t_cluchar *hash, t_rt_result *r, float3 vec)
{
	float3			res;
	t_env_noise		e_noise;

	res = (float3)(0.f, 0.f, 0.f);
	if (r->obj->mat.has_noise == 0)
		return ((float3)(1.f, 1.f, 1.f));
	e_noise.hash = hash;
	e_noise.type = r->obj->mat.noise.type;
	e_noise.pers = r->obj->mat.noise.pers;
	e_noise.depth = ((r->obj->mat.noise.octave == -1) ? 10 : r->obj->mat.noise.octave);
	e_noise.seed = r->obj->mat.noise.seed;
	e_noise.amp = r->obj->mat.noise.amp;
	res = ft_choose(&e_noise, vec.x, vec.y, vec.z);
	return (res);
}

static float3		bump(constant t_cluchar *hash, t_rt_result *r)
{
	float3			bump;
	float			eps;
	float3			coord;

	eps = 0.03f;
	coord = r->pos - r->obj->pos;
	bump.x = noise(hash, r, (float3)(coord.x - eps, coord.y, coord.z)).x - noise(hash, r, (float3)(coord.x + eps, coord.y, coord.z)).x;
	bump.y = noise(hash, r, (float3)(coord.x, coord.y - eps, coord.z)).x - noise(hash, r, (float3)(coord.x, coord.y + eps, coord.z)).x;
	bump.z = noise(hash, r, (float3)(coord.x, coord.y, coord.z - eps)).x - noise(hash, r, (float3)(coord.x, coord.y, coord.z + eps)).x;
	return (bump);
}
