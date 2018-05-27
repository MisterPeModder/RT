__kernel void is_prime(
		 __global int* input,
		 __global int* output,
		 const unsigned int count)
{
	private unsigned int i = get_global_id(0);
	private int j = 2;
	if (i < count)
	{
		while (j * j <= input[i])
		{
			if (input[i] % j == 0)
			{
				output[i] = 0;
				break ;
			}
		++j;
		}
		if (!(j * j <= input[i]))
			output[i] = input[i];
	}
}