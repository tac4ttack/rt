static t_ret			limit(const __local t_sphere *sphere, float2 tmp, const float3 ray, const float3 origin)
{
	t_ret		ret;
	float 		pt_y;
	float 		pt_ys;

	ret.dist = 0;
	ret.wall = 0;
	sphere->var_max.x = sphere->radius;
	sphere->var_min.x = sphere->radius;
	sphere->var_max.y = sphere->radius;
	sphere->var_min.y = sphere->radius;
	sphere->var_max.z = sphere->radius;
	sphere->var_min.z = sphere->radius;

	pt_y = origin.y + ray.y * tmp.x;
	pt_ys = origin.y + ray.y * tmp.y;
	if (pt_y <= sphere->pos.y + 2 )
		{
			ret.dist = tmp.x;
			return (ret);
	}
	else if (pt_ys <= sphere->pos.y +2)
		{
			ret.dist = tmp.y;
			return (ret);
		}
	ret.dist = 0;
	return (ret);
	}







static t_ret	inter_sphere(const __local t_sphere *sphere, const float3 ray, const float3 origin)
{
	float3		abc = 0;
	float		res1 = 0;
	float		res2 = 0;
	float3		pos = 0;
	
	float       d;
	float2       tmp;

	pos = origin - sphere->pos;
	abc = get_sphere_abc(sphere->radius, ray, pos);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		
	if (d == 0)
	{
		tmp.x =  ((-abc[1]) / (2 * abc[0]));
		tmp.y =  ((-abc[1]) / (2 * abc[0]));
	}
	else
	{
		res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
		res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
		if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		{
			tmp.x =(res1);
			tmp.y =(res2);
		}
		else
		{
			tmp.x =  (res2);
			tmp.y = (res1);
		}
	}
	
	return (limit(sphere, tmp, ray, origin));
}
