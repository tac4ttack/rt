/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:51:49 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/20 16:31:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

FT_FLOAT3			normalize_vect(FT_FLOAT3 v)
{
	FT_FLOAT3		res;
	float			id;

	id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

FT_FLOAT3			add_cl_float(FT_FLOAT3 v1, FT_FLOAT3 v2)
{
	FT_FLOAT3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

FT_FLOAT3			sub_cl_float(FT_FLOAT3 v1, FT_FLOAT3 v2)
{
	FT_FLOAT3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

FT_FLOAT3			cross_vect(FT_FLOAT3 v1)
{
	FT_FLOAT3		res;
	FT_FLOAT3		v2;

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
