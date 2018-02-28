unsigned int	sepiarize(const unsigned int color)
{
	uint3	base, cooking_pot = 0;
	base.x = (color & 0x00FF0000) >> 16;
	base.y = (color & 0x0000FF00) >> 8;
	base.z = (color & 0x000000FF);
	cooking_pot.x = (base.x * 0.393) + (base.y * 0.769) + (base.z * 0.189);
	cooking_pot.y = (base.x * 0.349) + (base.y * 0.686) + (base.z * 0.168);
	cooking_pot.z = (base.x * 0.272) + (base.y * 0.534) + (base.z * 0.131);
	if (cooking_pot.x > 255)
		cooking_pot.x = 255;
	if (cooking_pot.y > 255)
		cooking_pot.y = 255;
	if (cooking_pot.z > 255)
		cooking_pot.z = 255;
	return (((uint)cooking_pot.x << 16) + ((uint)cooking_pot.y << 8) + (uint)cooking_pot.z);
}

unsigned int	desaturate(const unsigned int color)
{
	uint3	rgb = 0;
	rgb.x = (color & 0x00FF0000) >> 16;
	rgb.y = (color & 0x0000FF00) >> 8;
	rgb.z = (color & 0x000000FF);
	float 	average = (rgb.x + rgb.y + rgb.z) / 3;
	return (((unsigned int)average << 16) \
			+ ((unsigned int)average << 8) \
			+ (unsigned int)average);
}

unsigned int	blend_multiply(const unsigned int c1, const unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	if ((r = r1 * r2) > 255)
		r = 255;
	if ((g = g1 * g2) > 255)
		g = 255;
	if ((b = b1 * b2) > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	blend_add(const unsigned int c1, const unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	if ((r = r1 + r2) > 255)
		r = 255;
	if ((g = g1 + g2) > 255)
		g = 255;
	if ((b = b1 + b2) > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	blend_factor(const unsigned int c1, const float factor)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);

	r = r1 * factor;
	g = g1 * factor;
	b = b1 * factor;
	return ((r << 16) + (g << 8) + b);
}

unsigned int			get_obj_reflex(const __local t_scene *scene, const t_hit hit)
{
	unsigned int		color = 0;

	if (hit.type == 1)
		color = CONES[hit.id].reflex;
	if (hit.type == 2)
		color = CYLIND[hit.id].reflex;
//	if (hit.type == 3)
//		color = LIGHT[hit.id].reflex;
	if (hit.type == 4)
		color = PLANE[hit.id].reflex;
	if (hit.type == 5)
		color = SPHERE[hit.id].reflex;
	return (color);
}

unsigned int			get_obj_hue(const __local t_scene *scene, const t_hit hit)
{
	unsigned int		color = 0;

	if (hit.type == 1)
		color = CONES[hit.id].color;
	if (hit.type == 2)
		color = CYLIND[hit.id].color;
	if (hit.type == 3)
		color = LIGHT[hit.id].color;
	if (hit.type == 4)
		color = PLANE[hit.id].color;
	if (hit.type == 5)
		color = SPHERE[hit.id].color;
	return (color);
}

unsigned int	get_ambient(const __local t_scene *scene, const unsigned int obj_color)
{
	unsigned int r, g, b;

	r = (obj_color & 0x00FF0000) >> 16;
	g = (obj_color & 0x0000FF00) >> 8;
	b = (obj_color & 0x000000FF);
	r = (0.01 + r * scene->ambient.x > 255 ? 255 : 0.01 + r * scene->ambient.x);
	g = (0.01 + g * scene->ambient.y > 255 ? 255 : 0.01 + g * scene->ambient.y);
	b = (0.01 + b * scene->ambient.z > 255 ? 255 : 0.01 + b * scene->ambient.z);
	return ((r << 16) + (g << 8) + b);
}

float3			get_obj_speculos(const __local t_scene *scene, const t_hit hit)
{
	float3	speculos = 0;

	if (hit.type == 1)
		speculos = CONES[hit.id].spec;
	if (hit.type == 2)
		speculos = CYLIND[hit.id].spec;
	if (hit.type == 4)
		speculos = PLANE[hit.id].spec;
	if (hit.type == 5)
		speculos = SPHERE[hit.id].spec;
	return (speculos);
}

float3			get_obj_diffuse(const __local t_scene *scene, const t_hit hit)
{
	float3	diffuse = 0;

	if (hit.type == 1)
		diffuse = CONES[hit.id].diff;
	if (hit.type == 2)
		diffuse = CYLIND[hit.id].diff;
	if (hit.type == 4)
		diffuse = PLANE[hit.id].diff;
	if (hit.type == 5)
		diffuse = SPHERE[hit.id].diff;
	return (diffuse);
}

unsigned int			color_diffuse(const __local t_scene *scene, const t_hit hit, \
										const t_hit light_hit, const unsigned int color, const float coef)
{
	float3			diffuse = get_obj_diffuse(scene, hit);
	float			brightness = LIGHT[light_hit.id].brightness;


	unsigned int	col_r = (color & 0x00FF0000) >> 16;
	unsigned int	col_g = (color & 0x0000FF00) >> 8;
	unsigned int	col_b = (color & 0x000000FF);
	unsigned int	obj_r = (get_obj_hue(scene, hit) & 0xFF0000) >> 16;
	unsigned int	obj_g = (get_obj_hue(scene, hit) & 0x00FF00) >> 8;
	unsigned int	obj_b = (get_obj_hue(scene, hit) & 0x0000FF);
	unsigned int	l_r = (get_obj_hue(scene, light_hit) & 0xFF0000) >> 16;
	unsigned int	l_g = (get_obj_hue(scene, light_hit) & 0x00FF00) >> 8;
	unsigned int	l_b = (get_obj_hue(scene, light_hit) & 0x0000FF);

	col_r += ((l_r * brightness) + obj_r) * coef * diffuse.x;
	col_g += ((l_g * brightness) + obj_g) * coef * diffuse.y;
	col_b += ((l_b * brightness) + obj_b) * coef * diffuse.z;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}

unsigned int			color_specular(const __local t_scene *scene, const t_hit hit, \
										const t_hit light_hit, const unsigned int color, const float coef)
{
	float3			speculos = get_obj_speculos(scene, hit);
	float			old_coef = coef;
	unsigned int	col_r = (color & 0x00FF0000) >> 16;
	unsigned int	col_g = (color & 0x0000FF00) >> 8;
	unsigned int	col_b = (color & 0x000000FF);

	col_r += ((LIGHT[light_hit.id].color & 0x00FF0000) >> 16) * pow(old_coef, LIGHT[light_hit.id].shrink) * speculos.x;
	col_g += ((LIGHT[light_hit.id].color & 0x0000FF00) >> 8) * pow(old_coef, LIGHT[light_hit.id].shrink) * speculos.y;
	col_b += (LIGHT[light_hit.id].color & 0x000000FF) * pow(old_coef, LIGHT[light_hit.id].shrink) * speculos.z;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}
