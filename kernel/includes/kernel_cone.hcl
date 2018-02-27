static float3	get_cone_abc(const t_cone cone, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		k = radians(cone.angle);

	k = tan(k);
	k = 1 + k * k;
	abc.x = dot(ray, ray) - (k * (dot(ray, cone.dir) * dot(ray, cone.dir)));
	abc.y = 2 * (dot(ray, origin) - (k * \
			(dot(ray, cone.dir) * dot(origin, cone.dir))));
	abc.z = (dot(origin, origin) - \
			(k * (dot(origin, cone.dir) * dot(origin, cone.dir))));
	return (abc);
}

float			inter_cone(const __local t_scene *scene, const int id, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;

	pos = origin - CONES[id].pos;
	abc = get_cone_abc(CONES[id], ray, pos);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return (-abc[1]) / (2 * abc[0]);
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return (res1);
	return (res2);
}

float3			get_cone_normale(const __local t_scene *scene, const t_hit hit)
{
	float3 res = 0;
	float3 v = 0;
	float3 project = 0;
	float doty = 0;

	v = hit.pos - CONES[hit.id].pos;
	doty = dot(v, CONES[hit.id].dir);
	project = doty * fast_normalize(CONES[hit.id].dir);
	res = v - project;
	return (fast_normalize(res));
}
