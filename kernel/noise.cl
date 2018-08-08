/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:59:30 by jhache            #+#    #+#             */
/*   Updated: 2018/08/08 02:07:53 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO: reduire le nombre de variable en reutilisant celle deja creer
//		au sein de chaque fonction

/*
** Noise struct.
** -type describe what kind of perturbation we will apply to the pixel.
** -freq is the frequence used by the noise function.
** -depth of the noise.
** -seed and hash is used for the generation of the perturbation.
*/
typedef struct	s_env_noise
{
	t_type_mat	type;
	t_clfloat	freq;
	t_clint		depth;
	t_clint		seed;
	t_clint		hash[256];
}				t_env_noise;

/*
** LERP for Linear Interpolation, it helps to interpolate different values.
*/
static float 		lerp(float a, float b, float s)
{
	return (a + s * (b - a));
}

/*
** It "smooth" the shape of a function, it form is: 6t^5 - 15t^4 + 10t^3.
*/
static float 		smooth(float x, float y, float s)
{
	return (x * y * s * (s * (s * 6 - 15) + 10));
}

/*
** Run through the hash table of our fake random values with x, y and z.
*/
static float		noise3(t_env_noise *noise, int x, int y, int z)
{
	int 	tmp;

	tmp = noise->hash[abs(((y + noise->seed) * z) % 256)];
	return (noise->hash[abs(((tmp + x) * z) % 256)]);
}

/*
** Return a single value of a noise in 3D.
*/
static float		noise3d(
	t_env_noise *noise,
	float x_f,
	float y_f,
	float z_f)
{
	int				x_int;
	int				y_int;
	int				z_int;
	int				a;
	int				b;
	int				c;
	int				d;
	int				s;
	int				t;
	int				u;
	int				v;
	int				w;
	int				x;
	int				y;
	int				z;
	float			low;
	float			high;

	x_int = x_f;
	y_int = y_f;
	z_int = z_f;
	x_f -= x_int;
	y_f -= y_int;
	z_f -= z_int;
	s = noise3(noise, x_int, y_int, z_int);
	t = noise3(noise, x_int + 1, y_int, z_int);
	u = noise3(noise, x_int, y_int + 1, z_int);
	v = noise3(noise, x_int + 1, y_int + 1, z_int);
	w = noise3(noise, x_int, y_int, z_int + 1);
	x = noise3(noise, x_int + 1, y_int, z_int + 1);
	y = noise3(noise, x_int, y_int + 1, z_int + 1);
	z = noise3(noise, x_int + 1, y_int + 1, z_int + 1);
	a = lerp(s, t, x_f);
	b = lerp(u, v, x_f);
	c = lerp(w, x, x_f);
	d = lerp(y, z, x_f);
	low = smooth(a, b, y_f);
	high = smooth(c, d, y_f);
	return (lerp(low, high, z_f));
}

/*
** Call me to have a perfect value for a 3D
*/
static float		perlin3d(t_env_noise *noise, float x, float y, float z)
{
	float			xa;
	float			ya;
	float			za;
	int				i;
	float			amp;
	float			fin;
	float			div;

	i = 0;
	fin = 0.f;
	div = 0.f;//cette variable etait non-initialiser, j'ai choisi 0.f arbitrairement
	amp = 1.f;
	xa = x * noise->freq;
	ya = y * noise->freq;
	za = z * noise->freq;
	while (i < noise->depth)
	{
		div += 256 * amp;
		fin += noise3d(noise, (int)xa, (int)ya, (int)za) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
		za *= 2;
		i++;
	}
	return (fin / div);
}

/*
** Procedural texture function for sinus marble effect.
** c1 is light gray, c2 is white.
*/
static float3		sin_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			result;
	float			value;

	c1.x = 0.7f;
	c1.y = 0.7f;
	c1.z = 0.7f;
	c2.x = 1.f;
	c2.y = 1.f;
	c2.z = 1.f;
	value = 1 - sqrt(fabs(sin(2 * M_PI_F *
		perlin3d(noise, x, y, z))));
	result.x = c1.x * (1 - value) + c2.x * value;
	result.y = c1.y * (1 - value) + c2.y * value;
	result.z = c1.z * (1 - value) + c2.z * value;
	return (result);
}

/*
** Procedural texture function for line marble effect.
** c1 is light gray, c2 is white.
*/
static float3		line_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			result;
	float			value;

	c1.x = 0.7f;
	c1.y = 0.7f;
	c1.z = 0.7f;
	c2.x = 1.f;
	c2.y = 1.f;
	c2.z = 1.f;
	value = (1 - cos(30 * 2 * M_PI_F * (x / 512 +
		0.25f * perlin3d(noise, x, y, z)))) / 2;
	result.x = c1.x * (1 - value) + c2.x * value;
	result.y = c1.y * (1 - value) + c2.y * value;
	result.z = c1.z * (1 - value) + c2.z * value;
	return (result);
}

/*
** Procedural texture function for wood effect.
** c1 is light brown, c2 is dark brown.
*/
static float3		wood_noise(t_env_noise *noise, float x, float y, float z)
{
	float3			c1;
	float3			c2;
	float3			result;
	float			value;
	float			value1;
	float			threshold;

	c1.x = 0.6f;
	c1.y = 0.6f;
	c1.z = 0.f;
	c2.x = 0.2f;
	c2.y = 0.2f;
	c2.z = 0.f;
	threshold = 0.2f;
	value = fmod(perlin3d(noise, x, y, z), threshold);
	if (value > threshold / 2)
		value = threshold - value;
	value1 = (1 - cos(M_PI_F * value / (threshold / 2))) / 2;
	result.x = c1.x * (1 - value1) + c2.x * value1;
	result.y = c1.y * (1 - value1) + c2.y * value1;
	result.z = c1.z * (1 - value1) + c2.z * value1;
	return (result);
}

/*
** Determine what is the perturbation of the color. Just "if" things.
*/
static float3		ft_choose(t_env_noise *e_noise, float x, float y, float z)
{
	float3			result;

	if (e_noise->type == WOOD)
		result = wood_noise(e_noise, x, y, z);
	else if (e_noise->type == WATER)
		result = wood_noise(e_noise, x, y, z);
	else if (e_noise->type == PERLIN)
		result = perlin3d(e_noise, x, y, z);
	else if (e_noise->type == SIN_MARBLE)
		result = sin_marble_noise(e_noise, x, y, z);
	else if (e_noise->type == LINE_MARBLE)
		result = line_marble_noise(e_noise, x, y, z);
	else
		return ((float3)(1.f, 1.f, 1.f));
	if (result.x < 0 || result.y < 0 || result.z < 0)
		result = (float3)(1.f, 1.f, 1.f);
	return (result);
}

static float3		noise(global t_clint *hash, t_rt_result *r)
{
	int				i;
	float3			result;
	t_env_noise		e_noise;

	if (r->obj->mat.noise.has_noise == 0)
		return ((float3)(1.f, 1.f, 1.f));
	i = 0;
	while (i < 256)
	{
		e_noise.hash[i] = hash[i];
		i++;
	}
	e_noise.freq = r->obj->mat.noise.freq;
	e_noise.depth = r->obj->mat.noise.depth;
	e_noise.seed = r->obj->mat.noise.seed;
	e_noise.type = r->obj->mat.noise.type;
	result = ft_choose(&e_noise, r->pos.x, r->pos.y, r->pos.z);
	return (result);
}
