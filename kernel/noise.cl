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
	t_clint		seed;
	t_clint		depth;
	t_clint		hash[256];
}				t_env_noise;

/*
** LERP for Linear Interpolation, it helps to interpolate different vals.
*/
static float 		lerp(float a, float b, float s)
{
    /*double f = (1 - cos(s * 3.141593)) * 0.5;

	return a * (1 - f) + b * f;
	*/return (a + s * (b - a));
}

/*
** It "smooth" the shape of a function, it form is: 6t^5 - 15t^4 + 10t^3.
*/
static float 		smooth(float s)
{
	return (s * s * s * (s * (s * 6 - 15) + 10));
	//return (s * s * (3.f - 2.f * s));
}

/*
** Run through the hash table of our fake random vals with x, y and z.
*/
static int		noise3(t_env_noise *noise, int x, int y, int z)
{
	int 			tmp;

	tmp = 0;
	tmp = noise->hash[abs(((y + noise->seed) * z) % 256)];
	return (noise->hash[abs(((tmp + x) * z) % 256)]);
}

static float quinticDeriv(const float t)
{
	return 30 * t * t * (t * (t - 2) + 1);
}

/*static float		float perm, float x, float y, float z)
{
	switch ((int)perm & 15)
	{
		case 0: return x + y; // (1,1,0)
		case 1: return -x + y; // (-1,1,0)
		case 2: return x - y; // (1,-1,0)
		case 3: return -x - y; // (-1,-1,0)
		case 4: return x + z; // (1,0,1)
		case 5: return -x + z; // (-1,0,1)
		case 6: return x - z; // (1,0,-1)
		case 7: return -x - z; // (-1,0,-1)
		case 8: return y + z; // (0,1,1),
		case 9: return -y + z; // (0,-1,1),
		case 10: return y - z; // (0,1,-1),
		case 11: return -y - z; // (0,-1,-1)
		case 12: return y + x; // (1,1,0)
		case 13: return -x + y; // (-1,1,0)
		case 14: return -y + z; // (0,-1,1)
		case 15: return -y - z; // (0,-1,-1) 
	}
}*/

/*
** Return a single val of a noise in 3D.
*/
static float		noise3d(
	t_env_noise *noise,
	float x_f,
	float y_f,
	float z_f)
{
	float				a;
	float				b;
	float				c;
	float				d;
	int				s;
	int				t;
	int				u;
	int				v;
	int				w;
	int				x;
	int				y;
	int				z;
	int				x_i;
	int				y_i;
	int				z_i;
	float			low;
	float			high;

	x_i = x_f;
	y_i = y_f;
	z_i = z_f;
	x_f -= x_i;
	y_f -= y_i;
	z_f -= z_i;
	x_f = smooth(x_f);
	y_f = smooth(y_f);
	y_f = smooth(z_f);
	s = noise3(noise, x_i, y_i, z_i);
	t = noise3(noise, x_i + 1, y_i, z_i);
	u = noise3(noise, x_i, y_i + 1, z_i);
	v = noise3(noise, x_i + 1, y_i + 1, z_i);
	w = noise3(noise, x_i, y_i, z_i + 1);
	x = noise3(noise, x_i + 1, y_i, z_i + 1);
	y = noise3(noise, x_i, y_i + 1, z_i + 1);
	z = noise3(noise, x_i + 1, y_i + 1, z_i + 1);
	a = lerp(s, t, x_f);
	b = lerp(u, v, x_f);
	c = lerp(w, x, x_f);
	d = lerp(y, z, x_f);
	low = lerp(a, b, y_f);
	high = lerp(c, d, y_f);
	//printf("%f ", smooth(a, b, y_f));
	return (lerp(low, high, z_f) * 0.001);
}

/*
** Call me to have a perfect val for a 3D
*/
static float		perlin3d(t_env_noise *noise, float x, float y, float z)
{
	int				i;
	float			div;
	float			res;
	float			amp;
	float			freq;

	i = 0;
	div = 0.0f;
	res = 0.0f;
	freq = 1.0f;
	amp = 1.0f;
	while (i < noise->depth)
	{
		res += noise3d(noise, x, y, z) * amp;
		freq /= 2.f;
		amp *= noise->freq;
		x *= 2.f;
		y *= 2.f;
		z *= 2.f;
		i++;
	}
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
	
	val = 0.0f;
	c1 = (float3)(1.0f, 1.0f, 1.0f);
	c2 = (float3)(0.7f, 0.7f, 0.7f);
	res = (float3)(0.0f, 0.0f, 0.0f);
	val = 1.f - sqrt(fabs(sin(2 * M_PI_F *
		noise3d(noise, x, y, z))));
	res.x = c1.x * (1.f - val) + c2.x * val;
	res.y = c1.y * (1.f - val) + c2.y * val;
	res.z = c1.z * (1.f - val) + c2.z * val;
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
	val = 0.0f;
	perturb = 0.9f;
	c1 = (float3)(0.7f, 0.7f, 0.7f);
	c2 = (float3)(1.0f, 1.0f, 1.0f);
	res = (float3)(0.0f, 0.0f, 0.0f);
	val = (1 - cos(line * 2 * M_PI_F * (x / 512 +
		perturb * noise3d(noise, x, y, z)))) / 2;
	res.x = c1.x * (1 - val) + c2.x * val;
	res.y = c1.y * (1 - val) + c2.y * val;
	res.z = c1.z * (1 - val) + c2.z * val;
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

	val = 0.0f;
	val1 = 0.0f;
	threshold = 0.2f;
	c1 = (float3)(0.6f, 0.6f, 0.0f);
	c2 = (float3)(0.2f, 0.2f, 0.0f);
	res = (float3)(0.0f, 0.0f, 0.0f);
	val = fmod(noise3d(noise, x, y, z), threshold);
	if (val > threshold / 2)
		val = threshold - val;
	val1 = (1 - cos(M_PI_F * val / (threshold / 2))) / 2;
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
		res = wood_noise(e_noise, x, y, z);
	else if (e_noise->type == PERLIN)
		res = perlin3d(e_noise, x, y, z);
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

static float3		noise(global t_clint *hash, t_rt_result *r)
{
	int				i;
	float3			res;
	t_env_noise		e_noise;

	i = 0;
	res = (float3)(0.0f, 0.0f, 0.0f);
	if (r->obj->mat.noise.has_noise == 0)
		return ((float3)(1.0f, 1.0f, 1.0f));
	while (i < 256)
	{
		e_noise.hash[i] = hash[i];
		i++;
	}
	e_noise.freq = r->obj->mat.noise.freq;
	e_noise.seed = r->obj->mat.noise.seed;
	e_noise.type = r->obj->mat.noise.type;
	e_noise.depth = r->obj->mat.noise.depth;
	res = ft_choose(&e_noise, (r->pos.x - r->obj->pos.x), (r->pos.y - r->obj->pos.y), (r->pos.z - r->obj->pos.z));
	//printf(" %3f ", res);
	return (res);
}
