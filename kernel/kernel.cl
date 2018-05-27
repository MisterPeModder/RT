__kernel void a_frame(
		private unsigned int x_size,
		private unsigned int y_size,
		write_only image2d_t output)
{
	private int2 coord;

	coord.x = get_global_id(0);
	coord.y = get_global_id(1);
	write_imageui(output, coord, (uint4)(255 * (coord.x / (float)x_size), 0,
										 255 * (coord.y / (float)y_size), 0));
}
