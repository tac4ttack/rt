/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:51:49 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/08 05:46:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_float3			normalize_vect(t_float3 v)
{
	t_float3		res;
	cl_float		id;

	id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

t_float3			add_cl_float(t_float3 v1, t_float3 v2)
{
	t_float3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_float3			sub_cl_float(t_float3 v1, t_float3 v2)
{
	t_float3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}
