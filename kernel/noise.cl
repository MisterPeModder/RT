/*
** Noise struct.
** -c1, c2 and c3 are colors for material perturbation.
** -amp is amplitude used by noise function.
** -fin is incremented in noise function by the noise value.
** -div divide fin at the end of all noise depth.
** -freq is the frequence used by the noise function.
** -depth of the noise.
** -lines of marble perturbation method.
** -value and value1 for intermediate sin/cos and material perturbations.
** -result to store material perturbations.
** -threshold for wood material method.
** -perturbation for marble perturbation method.
** -a to d for lerp the noise.
** -i to increment the depth of the noise.
** -s to z for noise transformation of x, y and z.
** -xa, ya, za, x_int, y_int, z_int, x_frac, y_frac and z_frac diverse
** var to manipulate x, y and z through different types, etc..
** -low and high to smooth the shape of the function by his mix and max values.
*/
typedef struct	s_env_noise
{
	t_clint		has_noise;
	t_clfloat	freq;
	t_clint		depth;
	t_clint		seed;
	t_type_mat	type;
	t_clint		hash[256];
	t_clfloat3	c1;
	t_clfloat3	c2;
	t_clfloat3	c3;
	t_clfloat	amp;
	t_clfloat	fin;
	t_clfloat	div;
	t_clint		lines;
	t_clfloat	value;
	t_clfloat	value1;
	t_clfloat3	result;
	t_clfloat	threshold;
	t_clfloat	perturbation;
	t_clint		a;
	t_clint		b;
	t_clint		c;
	t_clint		d;
	t_clint		i;
	t_clint		s;
	t_clint		t;
	t_clint		u;
	t_clint		v;
	t_clint		w;
	t_clint		x;
	t_clint		y;
	t_clint		z;
	t_clfloat	xa;
	t_clfloat	ya;
	t_clfloat	za;
	t_clfloat	low;
	t_clfloat	high;
	t_clint		x_int;
	t_clint		y_int;
	t_clint		z_int;
	t_clfloat	x_frac;
	t_clfloat	y_frac;
	t_clfloat	z_frac;
}				t_env_noise;

/*
** LERP for Linear Interpolation, it helps to interpolate differente noise->values.
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
** Run through the hash table of our fake random noise->values with x, y and z.
*/
static float		noise3(t_env_noise *noise, int x, int y, int z)
{
	int 	tmp;

	tmp = noise->hash[((y + noise->seed) * z) % 256];
	return (noise->hash[((tmp + x) * z) % 256]);
}

/*
** Return a single noise->value of a noise in 3D.
*/
static float		noise3d(t_env_noise *noise, float x, float y, float z)
{
	noise->x_int = x;
	noise->y_int = y;
	noise->z_int = z;
	noise->x_frac = x - noise->x_int;
	noise->y_frac = y - noise->y_int;
	noise->z_frac = z - noise->z_int;
	noise->s = noise3(noise, noise->x_int, noise->y_int, noise->z_int);
	noise->t = noise3(noise, noise->x_int + 1, noise->y_int, noise->z_int);
	noise->u = noise3(noise, noise->x_int, noise->y_int + 1, noise->z_int);
	noise->v = noise3(noise, noise->x_int + 1, noise->y_int + 1, noise->z_int);
	noise->w = noise3(noise, noise->x_int, noise->y_int, noise->z_int + 1);
	noise->x = noise3(noise, noise->x_int + 1, noise->y_int, noise->z_int + 1);
	noise->y = noise3(noise, noise->x_int, noise->y_int + 1, noise->z_int + 1);
	noise->z = noise3(noise, noise->x_int + 1, noise->y_int + 1, noise->z_int + 1);
	noise->a = lerp(noise->s, noise->t, noise->x_frac);
	noise->b = lerp(noise->u, noise->v, noise->x_frac);
	noise->c = lerp(noise->w, noise->x, noise->x_frac);
	noise->d = lerp(noise->y, noise->z, noise->x_frac);
	noise->low = smooth(noise->a, noise->b, noise->y_frac);
	noise->high = smooth(noise->c, noise->d, noise->y_frac);
	return (lerp(noise->low, noise->high, noise->z_frac));
}

/*
** Call me to have a perfect noise->value for a 3D
*/
static float		perlin3d(t_env_noise *noise, float x, float y, float z)
{
	noise->i = 0;
	noise->fin = 0;
	noise->amp = 1.0;
	noise->xa = x * noise->freq;
	noise->ya = y * noise->freq;
	noise->za = z * noise->freq;
	while (noise->i < noise->depth)
	{
		noise->div += 256 * noise->amp;
		noise->fin += noise3d(noise, noise->xa, noise->ya, noise->za) * noise->amp;
		noise->amp /= 2;
		noise->xa *= 2;
		noise->ya *= 2;
		noise->za *= 2;
		noise->i++;
	}
	return (noise->fin / noise->div);
}

/*
** Procedural texture function for sinus marble effect.
** noise->c1 is light gray, noise->c2 is white.
*/
static float3		sin_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	noise->c1.x = 0.7;
	noise->c1.y = 0.7;
	noise->c1.z = 0.7;
	noise->c2.x = 1.0;
	noise->c2.y = 1.0;
	noise->c2.z = 1.0;
	noise->value = 1 - sqrt(fabs(sin(2 * M_PI_F *
		perlin3d(noise, x, y, z))));
	noise->result.x = noise->c1.x * (1 - noise->value) + noise->c2.x * noise->value;
	noise->result.y = noise->c1.y * (1 - noise->value) + noise->c2.y * noise->value;
	noise->result.z = noise->c1.z * (1 - noise->value) + noise->c2.z * noise->value;
	return (noise->result);
}

/*
** Procedural texture function for line marble effect.
** noise->c1 is light gray, noise->c2 is white.
*/
static float3		line_marble_noise(t_env_noise *noise, float x, float y, float z)
{
	noise->c1.x = 0.7;
	noise->c1.y = 0.7;
	noise->c1.z = 0.7;
	noise->c2.x = 1.0;
	noise->c2.y = 1.0;
	noise->c2.z = 1.0;
	noise->lines = 30;
	noise->perturbation = 0.25;
	noise->value = (1 - cos(noise->lines * 2 * M_PI_F * (x / 512 +
		noise->perturbation * perlin3d(noise, x, y, z)))) / 2;
	noise->result.x = noise->c1.x * (1 - noise->value) + noise->c2.x * noise->value;
	noise->result.y = noise->c1.y * (1 - noise->value) + noise->c2.y * noise->value;
	noise->result.z = noise->c1.z * (1 - noise->value) + noise->c2.z * noise->value;
	return (noise->result);
}

/*
** Procedural texture function for wood effect.
** noise->c1 is light brown, noise->c2 is dark brown.
*/
static float3		wood_noise(t_env_noise *noise, float x, float y, float z)
{
	noise->c1.x = 0.6;
	noise->c1.y = 0.6;
	noise->c1.z = 0.0;
	noise->c2.x = 0.2;
	noise->c2.y = 0.2;
	noise->c2.z = 0.0;
	noise->threshold = 0.2;
	noise->value1 = (1 - cos(M_PI_F * noise->value / (noise->threshold / 2))) / 2;
	noise->value = fmod(perlin3d(noise, x, y, z), noise->threshold);
	if (noise->value > noise->threshold / 2)
		noise->value = noise->threshold - noise->value;
	noise->result.x = noise->c1.x * (1 - noise->value1) + noise->c2.x * noise->value1;
	noise->result.y = noise->c1.y * (1 - noise->value1) + noise->c2.y * noise->value1;
	noise->result.z = noise->c1.z * (1 - noise->value1) + noise->c2.z * noise->value1;
	return (noise->result);
}


/*
** Determine what is the perturbation of the color. Just "if" things.
*/
static float3		ft_choose(t_env_noise *e_noise, t_noise *noise, float x, float y, float z)
{
	e_noise->has_noise = noise->has_noise;
	e_noise->freq = noise->freq;
	e_noise->depth = noise->depth;
	e_noise->seed = noise->seed;
	e_noise->type = noise->type;
	if (e_noise->type == WOOD)
		return(wood_noise(e_noise, x, y, z));
	else if (e_noise->type == WATER)
		return(wood_noise(e_noise, x, y, z));
	else if (e_noise->type == PERLIN)
		return(perlin3d(e_noise, x, y, z));
	else if (e_noise->type == SIN_MARBLE)
		return(sin_marble_noise(e_noise, x, y, z));
	else if (e_noise->type == LINE_MARBLE)
		return(line_marble_noise(e_noise, x, y, z));
	else
		return(0);
}
