#ifndef KERNEL_CYLINDER_HCL
# define KERNEL_CYLINDER_HCL

static float3	get_cylinder_abc(const float radius, const float3 dir, const float3 ray, const float3 origin)
{
	float3		abc;

	// SEMBLE OK
	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

float					inter_cylinder(const __local t_scene *scene, const int id, const float3 ray, const float3 origin)
{
	float3				abc;
	float3				pos;
	float				d;
	float				res1 = 0;
	float				res2 = 0;
	float				m;

	pos = origin - CYLIND[id].pos;
	abc = get_cylinder_abc(CYLIND[id].radius, fast_normalize(CYLIND[id].dir), ray, pos);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		res1 = (-abc[1]) / (2 * abc[0]);
	else
	{
		res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
		res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	}
	if (res1 < 0 && res2 < 0)
		return (0);
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
	{
		if (CYLIND[id].height == 0 || (dot(ray, fast_normalize(CYLIND[id].dir) * res1 +
			dot(origin, fast_normalize(CYLIND[id].dir))) < CYLIND[id].height && dot(ray, fast_normalize(CYLIND[id].dir) * res1 +
			dot(origin, fast_normalize(CYLIND[id].dir))) > 0))
			return (res1);
	}
	if (CYLIND[id].height ==  0 || (dot(ray, fast_normalize(CYLIND[id].dir) * res2 +
			dot(origin, fast_normalize(CYLIND[id].dir))) < CYLIND[id].height && dot(ray, fast_normalize(CYLIND[id].dir) * res2 +
			dot(origin, fast_normalize(CYLIND[id].dir))) > 0))
		return (res2);
	else
		return (0);
}

float3			get_cylinder_normal(const __local t_scene *scene, t_hit hit)
{
	float3 res = 0;
	float3 v = 0;
	float3 project = 0;
	float doty = 0;

	v = hit.pos - CYLIND[hit.id].pos;
	doty = dot(v, fast_normalize(CYLIND[hit.id].dir));

	project = doty * fast_normalize(CYLIND[hit.id].dir);
	res = v - project;
	return (fast_normalize(res));
}

#endif
