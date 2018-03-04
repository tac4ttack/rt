float4	get_sphere_abc(const __local t_sphere *sphere, const float4 ray, const float4 origin)
{
	float4		abc = 0;

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (sphere->radius * sphere->radius);
	return (abc);
}

float			inter_sphere(const __local t_sphere *sphere, const float4 ray, const float4 origin)
{
	float4		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float4		pos = 0;

	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return (res1);
	return (res2);
}

#endif
