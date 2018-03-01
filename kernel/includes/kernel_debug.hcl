#ifndef KERNEL_DEBUG_HCL
# define KERNEL_DEBUG_HCL

int		print_vect(const float3 vect)
{
		printf("x = %f\ny = %f\nz = %f\n\n", vect.x, vect.y, vect.z);
		return (1);
}


int		print_vect2(const float3 vect)
{
		printf("x2 = %f\ny2 = %f\nz2 = %f\n\n", vect.x, vect.y, vect.z);
		return (1);
}

#endif
