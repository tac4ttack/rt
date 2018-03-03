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

cl_float4			normalize_vect(cl_float4 v)
{
	cl_float4		res;
	cl_float		id;

	id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

cl_float4			add_cl_float(cl_float4 v1, cl_float4 v2)
{
	cl_float4		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

cl_float4			sub_cl_float(cl_float4 v1, cl_float4 v2)
{
	cl_float4		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}
