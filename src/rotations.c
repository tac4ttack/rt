/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:24:52 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/22 18:48:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

FT_FLOAT3			rotx(FT_FLOAT3 dir, const float pitch)
{
	FT_FLOAT3		newdir;

	if (dir.x == 0 && dir.y == 0 && dir.z == 0)
	{
		dir.x = 0.000001;
		dir.y = 0.000001;
		dir.z = 0.000001;
	}
	dir = normalize_vect(dir);
	newdir.x = dir.x;
	newdir.y = dir.y * cos(pitch) + dir.z * -sin(pitch);
	newdir.z = dir.y * sin(pitch) + dir.z * cos(pitch);
	return (normalize_vect(newdir));
}

FT_FLOAT3			roty(FT_FLOAT3 dir, const float yaw)
{
	FT_FLOAT3		newdir;

	if (dir.x == 0 && dir.y == 0 && dir.z == 0)
	{
		dir.x = 0.000001;
		dir.y = 0.000001;
		dir.z = 0.000001;
	}
	dir = normalize_vect(dir);
	newdir.x = dir.x * cos(yaw) + dir.z * sin(yaw);
	newdir.y = dir.y;
	newdir.z = dir.x * -sin(yaw) + dir.z * cos(yaw);
	return (normalize_vect(newdir));
}

FT_FLOAT3			rotz(FT_FLOAT3 dir, const float roll)
{
	FT_FLOAT3		newdir;

	if (dir.x == 0 && dir.y == 0 && dir.z == 0)
	{
		dir.x = 0.000001;
		dir.y = 0.000001;
		dir.z = 0.000001;
	}
	dir = normalize_vect(dir);
	newdir.x = dir.x * cos(roll) + dir.y * -sin(roll);
	newdir.y = dir.x * sin(roll) + dir.y * cos(roll);
	newdir.z = dir.z;
	return (normalize_vect(newdir));
}

FT_FLOAT3			rotcam(FT_FLOAT3 vect, float rad_pitch, float rad_yaw)
{
	FT_FLOAT3		res;
	float			rad_roll;

	rad_roll = 0;
	vect = normalize_vect(vect);
	res.x = vect.x * cos(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_pitch) \
			* -sin(rad_roll) + cos(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) \
			+ vect.z * (-sin(rad_roll) * -sin(rad_pitch) + cos(rad_roll) \
			* sin(rad_yaw) * cos(rad_pitch));
	res.y = vect.x * sin(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_roll) \
			* cos(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) \
			+ vect.z * (cos(rad_roll) * -sin(rad_pitch) + sin(rad_roll) \
			* sin(rad_yaw) * cos(rad_pitch));
	res.z = vect.x * -sin(rad_yaw) + vect.y * cos(rad_yaw) * sin(rad_pitch) \
			+ vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (normalize_vect(res));
}

void				calculate_cos_sin_obj(t_object *obj)
{
	obj->cos.x = cosf(obj->dir.x);
	obj->cos.y = cosf(obj->dir.y);
	obj->cos.z = cosf(obj->dir.z);
	obj->sin.x = sinf(obj->dir.x);
	obj->sin.y = sinf(obj->dir.y);
	obj->sin.z = sinf(obj->dir.z);
}
