/*
** TREE OF RAYS STRUCT /////////////////////////////////////////////////////////
*/
typedef	struct			s_tor
{
	int					activate;
	float3				pos;
	float3				prim;
	float3				normale;
	float				coef_ref;
	float				coef_tra;
	float				opacity;
	unsigned int		color;
	size_t				mem_index;
	int					id;
	int					type;
}						t_tor;
////////////////////////////////////////////////////////////////////////////////

typedef struct			s_hit
{
	float				dist;
	float3				normal;
	float3				pos;
	t_object __local	*obj;
//	void				*dummy_pedro;
	int					mem_index;
	float				opacity;
	float				m;
	int					isin;
	int					mein;
	int					side;
	unsigned int		color;
}						t_hit;

typedef struct			s_tex
{
	unsigned int		pixel_array[12076155];
	int					width;
	int					height;
}						t_tex;

typedef struct			s_scene
{
	t_cam				__local *cameras;
//	void				*dummy_pedro;
	void				__local *mem_lights;
//	void				*dummy_gomez;
	void				__local *mem_obj;
//	void				*dummy_ramon;
	unsigned int		__global *texture_earth;
	unsigned int		__global *texture_moon;
	unsigned int		__global *texture_earth_cloud;
	unsigned int		__global *texture_star;
	unsigned int		n_cams;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	float3				ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
	float				u_time;
	int					flag;
	int					tor_count;
	int					over_sampling;
	int					mem_size_obj;
	int					mem_size_lights;
}						t_scene;
////////////////////////////////////////////////////////////////////////////////






static unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	t_object __local		*obj;
	t_light __local			*light;
	size_t					mem_index_lights;

	unsigned int			res_color;
	float					tmp;
	float3					reflect;
	float3 __private		diffuse;
	float __private			brightness;
	unsigned int __private	hue;
	unsigned int __private 	hue_light;
	unsigned int __private 	col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	t_light_ray				light_ray;
	t_hit					light_hit;
	float __private 		pow_of_spec;
	int __private 			light_color;
	float3 __private 		speculos;
	obj = hit.obj;
	
	hue = hit.color;
	// hue = get_hue(scene, obj, &hit);
	col_r = (hue & 0x00FF0000) >> 16;
	col_g = (hue & 0x0000FF00) >> 8;
	col_b = (hue & 0x000000FF);
	col_r = (0.01 + col_r * scene->ambient.x > 255 ? 255 : 0.01 + col_r * scene->ambient.x);
	col_g = (0.01 + col_g * scene->ambient.y > 255 ? 255 : 0.01 + col_g * scene->ambient.y);
	col_b = (0.01 + col_b * scene->ambient.z > 255 ? 255 : 0.01 + col_b * scene->ambient.z);
	res_color = ((col_r << 16) + (col_g << 8) + col_b);
	//col_r = 0;
	//col_g = 0;
	//col_b = 0;
	// obj_r = 0;
	// obj_g = 0;
	// obj_b = 0;
	// l_r = 0;
	// l_g = 0;
	// l_b = 0;
	// pow_of_spec = 0;
	// light_color = 0;
	// speculos = 0;
	mem_index_lights = 0;
	while (mem_index_lights < scene->mem_size_lights)
	{
		light = scene->mem_lights + mem_index_lights;
		light_ray.dir = light->pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir, light_ray.dist);
		if (!(light_hit.dist < light_ray.dist + 0.01 && light_hit.dist > EPSILON) || light_hit.opacity < 1)
		{
			tmp = (dot(hit.normal, light_ray.dir));
			if (tmp > EPSILON)
			{
				brightness = (float __private)light->brightness;
				diffuse = (float3 __private)obj->diff;
		//		hue = (unsigned int __private)obj->color; inutile
				hue_light = light->color;
				col_r = (res_color & 0xFF0000) >> 16;
				col_g = (res_color & 0x00FF00) >> 8;
				col_b = (res_color & 0x0000FF);
				obj_r = (hue & 0xFF0000) >> 16;
				obj_g = (hue & 0x00FF00) >> 8;
				obj_b = (hue & 0x00000FF);
				l_r = (hue_light & 0xFF0000) >> 16;
				l_g = (hue_light & 0x00FF00) >> 8;
				l_b = (hue_light & 0x0000FF);

				col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				(col_r > 255 ? col_r = 255 : 0);
				// commented lines are failed tonemaping test
			//	col_r = (col_r > 255 ? col_r / (col_r + 1) : col_r);
				(col_g > 255 ? col_g = 255 : 0);
			//	col_g = (col_g > 255 ? col_g / (col_g + 1) : col_g);
				(col_b > 255 ? col_b = 255 : 0);
			//	col_b = (col_b > 255 ? col_b / (col_b + 1) : col_b);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			reflect = fast_normalize(((float)(2.0 * dot(hit.normal, light_ray.dir)) * hit.normal) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > EPSILON)
			{
				speculos = obj->spec;
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = native_powr(tmp, (light->shrink));
				light_color = light->color;
				col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
				col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;
				(col_r > 255 ? col_r = 255 : 0);
			//	col_r = (col_r > 255 ? col_r / (col_r + 1) : col_r);
				(col_g > 255 ? col_g = 255 : 0);
			//	col_g = (col_g > 255 ? col_g / (col_g + 1) : col_g);
				(col_b > 255 ? col_b = 255 : 0);
			//	col_b = (col_b > 255 ? col_b / (col_b + 1) : col_b);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			res_color = blend_factor(res_color, ((light_hit.opacity - 1) * -1));
		}
		mem_index_lights += light->size;
	}
	return (res_color);
}

static unsigned int		bounce(const __local t_scene *scene, const float3 ray, t_hit old_hit, int depth)
{
	unsigned int	color;
	float3			reflex;
	t_hit			new_hit;
	float			reflex_coef;

	reflex = ray;
	new_hit = hit_init();
	color = 0;
	reflex_coef = 0;
	while (depth > 0)
	{
		// PREMIÈRE LOI DE SNELL-DESCARTES /////////////////////////////////////////////////////////
		reflex = fast_normalize(reflex - (2 * (float)dot(old_hit.normal, reflex) * old_hit.normal));
		////////////////////////////////////////////////////////////////////////////////////////////
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(scene, old_hit.pos, reflex, 0);
		reflex_coef = old_hit.obj->reflex;
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * reflex) + old_hit.pos;
			new_hit.normal = get_hit_normal(scene, reflex, new_hit);
			new_hit.pos = new_hit.pos + ((new_hit.dist / 100) * new_hit.normal);
			color = blend_factor(blend_add(color, phong(scene, new_hit, reflex)), reflex_coef);
		}
		if (new_hit.obj->reflex == 0)
			return (color);
		old_hit = new_hit;
		--depth;
	}
	return (color);
}

static unsigned int		refract(const __local t_scene *scene, const float3 ray, t_hit old_hit) // pour le plan, indice de refraction (pour tout objet non plein)
{
	float3			refract = ray;
	t_hit			new_hit;
	float			c1 = 0;
	float			c2 = 0;
	float			eta = 0;
	float			base = 1;
	int				i = 0;

	old_hit.pos = old_hit.pos + ((old_hit.dist / SHADOW_BIAS) * -(old_hit.normal * 2)); //pour refract, inverser le decalage de la position
	while (old_hit.obj->refract != 0 && old_hit.obj->opacity < 1 && ++i < 50)
	{
		c1 = dot(old_hit.normal, refract);
		eta = base / old_hit.obj->refract;
		if (c1 < 0)
			c1 = -c1;
		else
		{
			old_hit.normal = -old_hit.normal;
			eta = old_hit.obj->refract / base;
		}
		c2 = sqrt(1 - ((eta * eta) * (1 - (c1 * c1))));
		// DEUXIEME LOIS DE SNELL-DECARTES ////////////////////////////////////////////
		refract = fast_normalize((eta * refract) + ((eta * c1) - c2) * old_hit.normal);
		///////////////////////////////////////////////////////////////////////////////
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(scene, old_hit.pos, refract, 0);
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * refract) + old_hit.pos;
			new_hit.normal = get_hit_normal(scene, refract, new_hit);
			if (new_hit.mem_index != old_hit.mem_index && new_hit.obj->refract != 0 && new_hit.obj->opacity < 1)
				new_hit.pos = new_hit.pos + ((new_hit.dist / 10000) * -new_hit.normal);//pour refract en chaine, inverser la normale pour le decalage de la position
			else
				new_hit.pos = new_hit.pos + ((new_hit.dist / 10000) * new_hit.normal);
			if (new_hit.obj->refract == 0)
				return (phong(scene, new_hit, refract));
		}
		else
			return (0);
		old_hit = new_hit;
	}
	return (phong(scene, new_hit, refract));
}

static float3		refract_ray(const __local t_scene *scene, const float3 ray, float3 normale, float tra) // pour le plan, indice de refraction (pour tout objet non plein)
{
	float3			refract = 0;
	float			c1 = 0;
	float			c2 = 0;
	float			eta = 0;

	c1 = dot(normale, ray);
	eta = 1 / tra;
	if (c1 < 0)
		c1 = -c1;
	else
	{
		normale = -normale;
		eta = tra;
	}
	c2 = sqrt(1 - ((eta * eta) * (1 - (c1 * c1))));
	// DEUXIEME LOIS DE SNELL-DECARTES /////////////////////////////////////////////
	refract = fast_normalize((eta * ray) + ((eta * c1) - c2) * normale);
	////////////////////////////////////////////////////////////////////////////////
	return (refract);
}

static float3		bounce_ray(const __local t_scene *scene, const float3 ray, t_tor tor)
{
	float3			reflex;
	float			reflex_coef;

	reflex = 0;
	reflex_coef = 0;
	// PREMIÈRE LOI DE SNELL-DESCARTES ////////////////////////////////////////////////////////
	reflex = fast_normalize(ray - (2 * (float)dot(tor.normale, ray) * tor.normale));
	///////////////////////////////////////////////////////////////////////////////////////////
	return (reflex);
}

static float		reflect_ratio(float n1, float n2, float cos1, float sint)
{
	float			fr1 = 0;
	float			fr2 = 0;
	float			cos2 = sqrt(1 - sint * sint);

	if (cos1 >= 0)
	{
		fr1 = n1;
		n1 = n2;
		n2 = fr1;
	}
	else
		cos1 = -cos1;
	if (n1 / n2 * sqrt(1 - cos1 * cos1) > 1)
		return (1);
	fr1 = (n2 * cos1 - n1 * cos2) / (n2 * cos1 + n1 * cos2);
	fr2 = (n1 * cos2 - n2 * cos1) / (n1 * cos2 + n2 * cos1);
	fr1 *= fr1;
	fr2 *= fr2;
	return ((fr1 + fr2) / 2);
}

static t_tor		tor_push(float3 ray, float3 normale, float3 pos, float coef_ref, float coef_tra, float opacity, unsigned int color, size_t mem_index, int id, int type)
{
	t_tor			tor;

	tor.prim = ray;
	tor.pos = pos;
	tor.normale = normale;
	tor.coef_ref = coef_ref;
	tor.coef_tra = coef_tra;
	tor.opacity = opacity;
	tor.color = color;
	tor.mem_index = mem_index;
	tor.activate = 1;
	tor.id = id;
	tor.type = type;
	return (tor);
}

static int			tor_height(int i)
{
	int				h = 0;

	while ((i = (i - 1) / 2) >= 0)
		h++;
	return (h);
}

static unsigned int	tor_final_color(t_tor *tor)
{
	int				i = 63;
	unsigned int	color = 0;

	while (i > 0)
	{
		if (tor[i].activate == 0 && tor[i * 2 + 1].mem_index == tor[i].mem_index)
			;
		else
		{
			color = blend_add(tor[(i + 1) * 2].color, tor[i * 2 + 1].color);
			if (tor[i].coef_tra != 0 && color != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
			else if (tor[i].coef_ref != 0)
				tor[i].color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
			else
			tor[i].color = blend_add(color, tor[i].color);
		}
		i = i - 1;
		while (i > 0 && tor[i].activate == 0)
			i = i - 1;
	}
	color = blend_add(tor[(i + 1) * 2].color, tor[i * 2 + 1].color);
	if (tor[0].coef_tra != 0 && color != 0)
		color = blend_add(blend_factor(tor[i].color, tor[i].opacity), blend_factor(color, 1 - tor[i].opacity));
	else
		color = blend_add(blend_factor(tor[i].color, 1 - tor[i].coef_ref), blend_factor(color, tor[i].coef_ref));
	return (color);
}

static unsigned int	fresnel(const __local t_scene *scene, float3 ray, t_hit old_hit, int depth, unsigned int color)
{
	t_hit			new_hit;
	unsigned int	ncolor = 0;
	float3			refract = 0;
	float3			bounce = 0;
	float			fr = 0;
	float			ft = 0;
	float			eta = 0;
	float			cos1 = 0;
	float			sint = 0;
	t_tor			tor[128];
	int				i = 0;

	depth = (int)pow(2.f, (float)depth) - 1;
	i = 0;
	while (i < 128)
	{
		tor[i].activate = 0;
		tor[i].prim = 0;
		tor[i].normale = 0;
		tor[i].pos = 0;
		tor[i].coef_ref = 0;
		tor[i].coef_tra = 0;
		tor[i].color = 0;
		tor[i].opacity = 0;
		tor[i].mem_index = 0;
		tor[i].id = 0;
		tor[i].type = 0;
		i++;
	}
	i = 0;
	tor[i] = tor_push(ray, old_hit.normal, old_hit.pos, old_hit.obj->reflex, old_hit.obj->refract, old_hit.obj->opacity, color, old_hit.mem_index, old_hit.obj->id, old_hit.obj->type);
	while (i < 63 && i < depth)
	{
		eta = 1 / tor[i].coef_tra;
		cos1 = dot(tor[i].normale, tor[i].prim);
		if (cos1 >= 0)
			eta = tor[i].coef_tra;
		if (cos1 >= 0)
			sint = tor[i].coef_tra * sqrt(1 - cos1 * cos1);
		else
			sint = 1 / tor[i].coef_tra * sqrt(1 - cos1 * cos1);
		if (sint >= 1)
			fr = 1;
		else
			fr = reflect_ratio(1, tor[i].coef_tra, cos1, sint);
		if (fr > 0.9)
			fr = 1;
		if (fr < 0.1)
			fr = 0;
		ft = 1 - fr;
		if (fr < 1)
		{
			if (tor[i].type != OBJ_PLANE)
				refract = refract_ray(scene, tor[i].prim, tor[i].normale, tor[i].coef_tra);
			else
				refract = tor[i].prim;
			if (cos1 < 0)
				new_hit = ray_hit(scene, tor[i].pos + (0.0001f * 2 * -tor[i].normale), refract, 0);
			else
				new_hit = ray_hit(scene, tor[i].pos, refract, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				if (cos1 < 0)
					new_hit.pos = (new_hit.dist * refract) + tor[i].pos + (0.0001f * 2 * -tor[i].normale);
				else
					new_hit.pos = (new_hit.dist * refract) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, refract, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000 * new_hit.normal);
				ncolor = blend_factor(phong(scene, new_hit, refract), ft);
				tor[i * 2 + 1] = tor_push(refract, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, new_hit.obj->id, old_hit.obj->type);
			}

		}
		if ((tor[i].opacity < 1 && tor[i].coef_tra >= 1) || tor[i].coef_ref != 0)
		{
			bounce = bounce_ray(scene, tor[i].prim, tor[i]);
			new_hit = ray_hit(scene, tor[i].pos, bounce, 0);
			if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
			{
				new_hit.pos = (new_hit.dist * bounce) + tor[i].pos;
				new_hit.normal = get_hit_normal(scene, bounce, new_hit);
				new_hit.pos = new_hit.pos + (new_hit.dist / 10000 * new_hit.normal);
				ncolor = blend_factor(phong(scene, new_hit, bounce), fr);
				tor[i * 2 + 2] = tor_push(bounce, new_hit.normal, new_hit.pos, new_hit.obj->reflex, new_hit.obj->refract, new_hit.obj->opacity, ncolor, new_hit.mem_index, new_hit.obj->id, old_hit.obj->type);
			}
		}
		i = i + 1;
		while (i < 63 && tor[i].activate == 0)
			i = i + 1;
	}
	return (tor_final_color(tor));
}


unsigned int		plane_checkerboard(float3 normale, float3 pos)
{
	float3			u_axis;
	float3			v_axis;
	int2			uv;

	u_axis.x = normale.y;
	u_axis.y = normale.z;
	u_axis.z = -normale.x;
	v_axis = cross(u_axis, normale);
	uv.x = (int)floor(dot(pos, u_axis) / 4);
	uv.y = (int)floor(dot(pos, v_axis) / 4);
	if (uv.x % 2 == 0)
	{
		if (uv.y % 2 == 0)
			return (0);
		else
			return (0x00FFFFFF);
	}
	else if (uv.y % 2 == 0)
		return (0x00FFFFFF);
	return (0);
}

unsigned int		plane_texture(float3 normale, float3 pos, float3 u_axis, unsigned int __global *texture, int width, int height)
{
	float3			v_axis;
	int2			uv;

	v_axis = cross(u_axis, normale);
	uv.x = (int)floor(dot(pos, u_axis) * 10 /* + decalage */);// * le ratio
	uv.y = (int)floor(dot(pos, v_axis) * 10 /* + decalage */);// idem
	uv.x %= width;
	uv.y %= height;
	if (uv.x < 0)
		uv.x += width;
	if (uv.y < 0)
		uv.y += height;
	uv.y = (uv.y - 1500) * -1;
	return (texture[uv.y + uv.x * width]);
}

unsigned int		sphere_texture(float3 pos, unsigned int __global *texture, int width, int height, int i, float u_time)
{
	unsigned int	color = 0;
	int2			uv;

	uv.x = (int)floor((0.5 + (atan2(pos.z, pos.x) / (2 * M_PI))) * width);
	uv.y = (int)floor((0.5 - (asin(pos.y) / M_PI)) * height);
	uv.y = (uv.y - height) * -1;
	if (i == 1)					//deplacement gauche / droite
		uv.x += u_time * 100;
	if (i == 2)
		uv.x += u_time * 200;
	if (uv.x > width)
		uv.x -= width;
	// if ((uv.y += decy) > height) deplacement haut / bas
	// 	uv.y -= height;
	color = texture[uv.x + uv.y * width];
	return (color);
}

unsigned int		cylinder_texture(float3 pos, float3 dir, float3 u_axis, float ratio, unsigned int __global *texture, int width, int height, float radius)
{
	unsigned int	color = 0;
	float3			v_axis;
	float			npos;
	float			vpos;
	int2			uv;

	v_axis = cross(u_axis, dir);
	npos = fast_length(dot(pos, dir) * dir);
	while (npos > ratio)
		npos -= ratio;
	if (dot(pos, dir) < 0)
		npos = (npos - ratio) * -1;
	uv.y = (int)floor((npos / ratio) * height);
	npos = dot(pos, u_axis);
	vpos = dot(pos, v_axis);
	uv.x = (int)floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * width);
	// uv.y = (uv.y - height) * -1;
	// if ((uv.x += decx) > width)   Decalage;
	// 	uv.x -= width;
	// if ((uv.y += decy) > height)
	// 	uv.y -= height;
	color = (unsigned int)texture[uv.x + (uv.y * width)];
	return (color);
}

unsigned int		cone_texture(float3 pos, float3 dir, float3 u_axis, float ratio, unsigned int __global *texture, int width, int height)
{
	unsigned int	color = 0;
	float3			v_axis;
	float			npos;
	float			vpos;
	float			radius;
	int2			uv;

	v_axis = cross(u_axis, dir);
	npos = dot(pos, dir);
	radius = fast_length(pos - (npos * dir));
	while (npos > ratio)
		npos -= ratio;
	while (npos < 0)
		npos += ratio;
	uv.y = (int)floor((fast_length(npos * dir) / ratio) * height);
	npos = dot(pos, u_axis);
	vpos = dot(pos, v_axis);
	uv.x = (int)floor((0.5 + (atan2(npos, vpos) / (2 * M_PI))) * width);
	color = (unsigned int)texture[uv.x + (uv.y * width)];
	return (color);
}

unsigned int		sphere_checkerboard(float3 pos, unsigned int color)
{
	int2	uv;

	uv.x = (int)floor((0.5 + (atan2(pos.z, pos.x) / (2 * 3.1415))) * 20);
	uv.y = (int)floor((0.5 - (asin(pos.y) / 3.1415)) * 10);
	if (uv.x % 2 == 0)
	{
		if (uv.y % 2 == 0)
			return (0);
		else
			return (color);
	}
	else if (uv.y % 2 == 0)
			return (color);
	return (0);
}

static unsigned int	get_pixel_color(const __local t_scene *scene, float3 ray, __global int *target, bool isHim)
{
	t_hit			hit;
	unsigned int	color;
	unsigned int	bounce_color;

	hit = hit_init();
	hit.dist = MAX_DIST;
	color = 0;
	bounce_color = 0;
	hit = ray_hit(scene, (ACTIVECAM.pos), ray, 0);
	if (isHim && hit.obj != -1)
		*target = hit.mem_index;
	if (hit.dist > EPSILON && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normal = get_hit_normal(scene, ray, hit);
			hit.pos = hit.pos + (0.001f * hit.normal);
		hit.pos = hit.pos + ((hit.dist / SHADOW_BIAS) * hit.normal);
		if (hit.obj->type == 6)
		{
			if (hit.obj->pos.x == 0)
			{
				hit.color = sphere_texture(fast_normalize(hit.obj->pos - hit.pos), scene->texture_earth, 4915, 2457, 2, scene->u_time);
				color = sphere_texture(fast_normalize(hit.obj->pos - hit.pos), scene->texture_earth_cloud, 8192, 4096, 1, scene->u_time);
				hit.color = blend_add(hit.color, color);
			}
			 if (hit.obj->pos.x != 0)
			 	hit.color = sphere_texture(fast_normalize(hit.obj->pos - hit.pos), scene->texture_moon, 8192, 4096, 0, 0);
				// hit.color = sphere_texture(fast_normalize(hit.obj->pos - hit.pos), scene->texture_earth, 8192, 4096, 0, 0);
		}
		if (hit.obj->type == 5)
			// hit.color = plane_texture(hit.normal, hit.pos, fast_normalize(((__local t_plane *)hit.obj)->u_axis), scene->texture_star, 1500, 1500);
			hit.color = plane_checkerboard(hit.normal, hit.pos);
		if (hit.obj->type == 4)
			hit.color = cylinder_texture(hit.pos - hit.obj->pos, fast_normalize(hit.obj->dir), fast_normalize(((__local t_cylinder *)hit.obj)->u_axis), 10., scene->texture_star, 1500, 1500, ((__local t_cylinder *)hit.obj)->radius);
		if (hit.obj->type == 3)
			hit.color = cone_texture(hit.pos - hit.obj->pos, fast_normalize(hit.obj->dir), fast_normalize(((__local t_cone *)hit.obj)->u_axis), 10., scene->texture_star, 1500, 1500);
		// if (hit.obj->type != 6 && hit.obj->type != 4 && hit.obj->type != 5)
		//  	hit.color = hit.obj->color;
		color = phong(scene, hit, ray);
		if (((hit.obj->refract != 0 && hit.obj->opacity < 1) || hit.obj->reflex > 0) && scene->depth > 0)
			return (fresnel(scene, ray, hit, scene->depth + 1, color));
		/*else if (hit.obj->refract != 0 && hit.obj->opacity < 1)
		{
			bounce_color = refract(scene, ray, hit);
			if (bounce_color == 0)
				return (blend_med(bounce_color, blend_factor(color, ((hit.obj->opacity - 1) * -1))));
			bounce_color = blend_factor(bounce_color, ((hit.obj->opacity - 1) * -1));
		}
		else if (depth > 0 && hit.obj->reflex > 0)
			bounce_color = bounce(scene, ray, hit, depth);*/
		return (blend_add(color, bounce_color));
	}
	return (get_ambient(scene, BACKCOLOR));
}

static float3		get_ray_cam(__local t_scene *scene, const uint2 pix, const uint width, const uint height)
{
	float3			cam_ray = 0;
	float			ratio = ((float)width) / ((float)height);

	cam_ray.x = ((2 * ((pix.x + 0.5) / width)) - 1) * ratio * (tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.y = ((1 - (2 * ((pix.y + 0.5) / height))) * tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.z = 1;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(fast_normalize(cam_ray));
}

__kernel void		ray_trace(	__global	char		*output,

								__global	char		*global_mem_objects,
								__local		char		*mem_objects,
								__private	int		mem_size_objects,

								__private	float		u_time,

								__global	t_scene		*scene_data,
								__global	t_cam		*cameras_data,

								__local		t_scene		*scene,
								__local		t_cam		*cameras,

								__global	char		*global_mem_lights,
								__local		char		*mem_lights,
								__private	int		mem_size_lights,

								__global	int			*target,
								__global	unsigned int *texture_earth,
								__global	unsigned int *texture_moon,
								__global	unsigned int *texture_earth_cloud,
								__global	unsigned int *texture_star)
{

 	event_t			ev;
	int				id;
	uint2			pix;
	float3			prim_ray;
	unsigned int	final_color_o[32];
	unsigned int	final_color;
	uint3			rgb = 0;


	ev = async_work_group_copy((__local char *)mem_objects, (__global char *)global_mem_objects, mem_size_objects, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)mem_lights, (__global char *)global_mem_lights, mem_size_lights, 0);
	wait_group_events(1, &ev);

	int boo = get_global_id(0) + get_global_id(1);

	pix.x = get_global_id(0);// % scene->win_w;
	pix.y = get_global_id(1);// / scene->win_w;


	 // if (!pix.x && !pix.y) printf("%zu\n", sizeof(size_t));

	id = pix.x + (scene->win_w * pix.y);
	scene->cameras = cameras;
	scene->mem_lights = mem_lights;
	scene->u_time = u_time;
	scene->mem_obj = mem_objects;
	scene->mem_size_obj = mem_size_objects;
	scene->mem_size_lights = mem_size_lights;
	scene->texture_earth = texture_earth;
	scene->texture_moon = texture_moon;
	scene->texture_earth_cloud = texture_earth_cloud;
	scene->texture_star = texture_star;
	if (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target = -1;

	final_color = 0;
	if (scene->over_sampling > 1)
	{
		int i = 0;
		pix.x *= scene->over_sampling;
		pix.y *= scene->over_sampling;

		while (i < scene->over_sampling * 2)
		{
			pix.x += (i % 2);
			pix.y += !(i % 2);
			prim_ray = get_ray_cam(scene, pix, scene->win_w * scene->over_sampling, scene->win_h * scene->over_sampling);
			final_color_o[i] = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y));
			rgb.x += (final_color_o[i] & 0x00FF0000);
			rgb.y += (final_color_o[i] & 0x0000FF00);
			rgb.z += (final_color_o[i] & 0x000000FF);
			i++;
		}
		final_color += ((rgb.x / (scene->over_sampling * 2)) & 0x00FF0000);
		final_color += ((rgb.y / (scene->over_sampling * 2)) & 0x0000FF00);
		final_color += ((rgb.z / (scene->over_sampling * 2)) & 0x000000FF);
	}
	else
	{
		prim_ray = get_ray_cam(scene, pix, scene->win_w, scene->win_h);
		final_color = get_pixel_color(scene, prim_ray, target, (scene->flag & OPTION_RUN && pix.x == scene->mou_x && pix.y == scene->mou_y));
	}

	if (scene->flag & OPTION_SEPIA)
		final_color = sepiarize(final_color);
	if (scene->flag & OPTION_BW)
		final_color = desaturate(final_color);
	if (scene->flag & OPTION_INVERT)
		final_color = invert(final_color);

	// ALPHA INSERT and RGB SWAP
	int4 swap;
	swap.w = 255;
	swap.x = (final_color & 0x00FF0000) >> 16;
	swap.y = (final_color & 0x0000FF00) >> 8;
	swap.z = (final_color & 0x000000FF);
	final_color = ((swap.w << 24) + (swap.z << 16) + (swap.y << 8) + swap.x);
	((__global unsigned int *)output)[id] = final_color;
}
