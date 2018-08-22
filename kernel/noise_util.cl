/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_util.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:59:30 by jhache            #+#    #+#             */
/*   Updated: 2018/08/22 06:08:17 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static float 	lerp(float a, float b, float s)
{
	float		f;

	f = (1 - native_cos(s * M_PI_F)) * 0.5f;
	return (a + f * (b - a));
}

/*
** It "smooth" the shape of a function, it form is: 6t^5 - 15t^4 + 10t^3.
*/
static float 	smooth(float s)
{
	return (s * s * s * (s * (s * 6.f - 15.f) + 10.f));
}

/*
** Run through the hash table of our fake random vals with x, y and z.
*/
static int		noise3(t_env_noise *noise, int x, int y, int z)
{
	return (noise->hash[(z + noise->hash[(y + noise->hash[(x + noise->seed) & 255]) & 255]) & 255]);
}

/*
** Used to pick the correct gradient.
*/
static float	gradient(float perm, float x, float y, float z)
{
	switch ((int)perm & 15)
	{
		case 0: return x + y;
		case 1: return -x + y;
		case 2: return x - y;
		case 3: return -x - y;
		case 4: return x + z;
		case 5: return -x + z;
		case 6: return x - z;
		case 7: return -x - z;
		case 8: return y + z;
		case 9: return -y + z;
		case 10: return y - z;
		case 11: return -y - z;
		case 12: return y + x;
		case 13: return -x + y;
		case 14: return -y + z;
		case 15: return -y - z;
	}
}

/*
** Return a single val of a noise in 3D.
*/
static float		noise3d(
	t_env_noise *noise,
	float x_f,
	float y_f,
	float z_f)
{
	int				x_i;
	int				y_i;
	int				z_i;
	float			low;
	float			high;

	x_i = (int)floor(x_f);
	y_i = (int)floor(y_f);
	z_i = (int)floor(z_f);
	x_f -= x_i;
	y_f -= y_i;
	z_f -= z_i;
	float a = gradient(noise3(noise, x_i, y_i, z_i), x_f, y_f, z_f);
	float b = gradient(noise3(noise, x_i + 1, y_i, z_i), x_f - 1, y_f, z_f);
	float c = gradient(noise3(noise, x_i, y_i + 1, z_i), x_f, y_f - 1, z_f);
	float d = gradient(noise3(noise, x_i + 1, y_i + 1, z_i), x_f - 1, y_f - 1, z_f);
	float e = gradient(noise3(noise, x_i, y_i, z_i + 1), x_f, y_f, z_f - 1);
	float f = gradient(noise3(noise, x_i + 1, y_i, z_i + 1), x_f - 1, y_f, z_f - 1);
	float g = gradient(noise3(noise, x_i, y_i + 1, z_i + 1), x_f, y_f - 1, z_f - 1);
	float h = gradient(noise3(noise, x_i + 1, y_i + 1, z_i + 1), x_f - 1, y_f - 1, z_f - 1);
	x_f = smooth(x_f);
	y_f = smooth(y_f);
	z_f = smooth(z_f);
	float w = lerp(a, b, x_f);
	float x = lerp(c, d, x_f);
	float y = lerp(e, f, x_f);
	float z = lerp(g, h, x_f);
	low = lerp(w, x, y_f);
	high = lerp(y, z, y_f);
	return (lerp(low, high, z_f));
}
