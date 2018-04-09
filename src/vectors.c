/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:51:49 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/02 22:01:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3			normalize_vect(cl_float3 v)
{
	cl_float3		res;
	cl_float		id;

	id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

cl_float3			add_cl_float(cl_float3 v1, cl_float3 v2)
{
	cl_float3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

cl_float3			sub_cl_float(cl_float3 v1, cl_float3 v2)
{
	cl_float3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

cl_float3			cross_vect(cl_float3 v1)
{
	cl_float3		res;
	cl_float3		v2;

	if (v1.x == 1 || v1.x == -1)
	{
		v2.x = 0;
		v2.y = 1;
		v2.z = 0;
	}
	else
	{
		v2.x = 1;
		v2.y = 0;
		v2.z = 0;
	}
	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (normalize_vect(res));
}
