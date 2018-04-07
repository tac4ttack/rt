static float	ft_ret(float *tab)
{
	float		ret;
	int			i;
	ret = -1.0;
	i = 0;
	while(i < 4)
	{
		if(tab[i] > 0.0001 && ret == -1)
			ret = tab[i];
			if (tab[i] < ret && tab[i] > 0.0001 )
			ret = tab[i];
		i++;
	}
	if (ret == -1.0)
		ret = 0.0;
	return (ret);
}

static float3	ft_solve_3(float a, float b, float c, float d)
{
	float 	a1;
	a1 = c / d;
	float a2;
	a2 = b / d;
	float a3;
	a3 = a / d;
	float3 Result;
	float theta;
	float sqrtQ;
	float e;
	float Q = (a1 * a1 - 3.0f * a2) / 9.0f;
	float R = (2.0f * a1 * a1 * a1 - 9.0f * a1 * a2 + 27.0f * a3) / 54.0f;
	float Qcubed = Q * Q * Q;
	d = Qcubed - R * R;
	if ( d >= 0.0001f )
	{	
		if ( Q < 0.0f )
		{
			Result.x = 0.0f;
			Result.y = 0.0f;
			Result.z = 0.0f;
				return (Result);
		}
		theta = acos(R / sqrt(Qcubed));
		sqrtQ = sqrt(Q);
		Result.x = -2.0f * sqrtQ * cos(theta / 3.0f) - a1 / 3.0f;
		Result.y = -2.0f * sqrtQ * cos((theta + 2.0f * M_PI) / 3.0f ) - a1 / 3.0f;
		Result.z = -2.0f * sqrtQ * cos((theta + 4.0f * M_PI) / 3.0f ) - a1 / 3.0f;
	}
	else
	{	
		e = pow(sqrt(-d) + fabs(R), 1.0f/ 3.0f);	
		if ( R > 0.0001f )
			e = -e;
		Result.x = Result.y = Result.z = (e + Q / e) - a1 / 3.0f;
	}
	return (Result);
}
static float	ft_solve_4(float t[5])
{
	float Result[4];
	float3 Roots;
	float Rsquare;
	float Rrec;
	float a0= t[0] / t[4];
	float a1 = t[1] / t[4];
	float a2 = t[2] / t[4];
	float  a3 = t[3] / t[4];
	float D;
	float E;
	float3 b;
	b.x = 4.0f * a2 * a0 - a1 * a1 - a3 * a3 * a0;
	b.y = a1 * a3 - 4.0f * a0;
	b.z = -a2;
	Roots = ft_solve_3(b.x, b.y, b.z, 1.0f);
	float	y = fmax(Roots.x, fmax(Roots.y, Roots.z));
	float R = 0.25f * a3 * a3 - a2 + y;
	if ( R < 0.0001f)
		return (0.0f);
	R = sqrt(R);
	if ( R == 0.0001f )
	{
		D = sqrt( 0.75f * a3 * a3 - 2.0f * a2 + 2.0f * sqrt( y * y - 4.0f * a0 ) );
		E = sqrt( 0.75f * a3 * a3 - 2.0f * a2 - 2.0f * sqrt( y * y - 4.0f * a0 ) );
	}
	else
	{
		Rsquare = R * R;
		Rrec = 1.0f / R;
		D = sqrt( 0.75f * a3 * a3 - Rsquare - 2.0f * a2 + 0.25f * Rrec * (4.0f * a3 * a2 - 8.0f * a1 - a3 * a3 * a3) );
		E = sqrt( 0.75f * a3 * a3 - Rsquare - 2.0f * a2 - 0.25f * Rrec * (4.0f * a3 * a2 - 8.0f * a1 - a3 * a3 * a3) );
	}
	Result[0] = -0.25f * a3 + 0.5f * R + 0.5f * D;
	Result[1] = -0.25f * a3 + 0.5f * R - 0.5f * D;
	Result[2] =  -0.25f * a3 - 0.5f * R + 0.5f * E;
	Result[3] = -0.25f * a3 - 0.5f * R - 0.5f * E;
	return(ft_ret(Result));
return (0.0f);
}

static t_ret		inter_thor(const __local t_thor *thor, const float3 ray, const float3 origin)
{
	t_ret		ret;
	ret.dist = 0;
	ret.normal = 0;
	ret.wall = 0;

	float		c[5];
	float3		k;
	float		e;
	float 		r = thor->big_radius;
	
	k.x = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	e = (origin.x - thor->pos.x) * (origin.x - thor->pos.x) + (origin.y - thor->pos.y) *
	(origin.y - thor->pos.y) + (origin.z - thor->pos.z) * (origin.z - thor->pos.z) -
	r * r - thor->lil_radius * thor->lil_radius;
	k.z = (origin.x - thor->pos.x) * ray.x + (origin.y - thor->pos.y) * ray.y +
	(origin.z - thor->pos.z) * ray.z;
	k.y = 4.0f * r * r;
	c[0] = e * e - k.y * (thor->lil_radius * thor->lil_radius - (origin.y - thor->pos.y) *
	(origin.y - thor->pos.y));
	c[1] = 4.0f * k.z * e + 2.0f * k.y * (origin.y - thor->pos.y) * ray.y;
	c[2] = 2.0f * k.x * e + 4.0f * k.z * k.z + k.y * ray.y * ray.y;
	c[3] = 4.0f * k.x * k.z;
	c[4] = k.x * k.x;
	ret.dist = ft_solve_4(c);
	return (ret);
}

static float3 get_thor_normal(const __local t_thor *thor, const t_hit hit)
{
	__private float3	res = 0;
	float	c = 0;

	float	R = (float)(thor->lil_radius * thor->lil_radius);
	float	r = (float)(thor->big_radius * thor->big_radius);

	float	px = hit.pos.x - thor->pos.x;
	float	py = hit.pos.y - thor->pos.y;
	float	pz = hit.pos.z - thor->pos.z;

	c = ((px * px) + (py * py) + (pz * pz) - r - R);
	
	res.x = 4.0f * c * px;
	res.y = 4.0f * py * (c + 2 * r);
	res.z = 4.0f * c * pz;

	return (res);
}
