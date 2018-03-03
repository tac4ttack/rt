/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:24:52 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/02 22:02:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float4			rotx(cl_float4 dir, const float pitch)
{
	cl_float4		newdir;

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

cl_float4			roty(cl_float4 dir, const float yaw)
{
	cl_float4		newdir;

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

cl_float4			rotz(cl_float4 dir, const float roll)
{
	cl_float4		newdir;

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

cl_float4			rotcam(cl_float4 vect, float rad_pitch, float rad_yaw)
{
	cl_float4		res;
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
