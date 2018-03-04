/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_check_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 03:02:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/02 23:28:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cl_check_err(cl_int err, const char *name)
{
	if (err != CL_SUCCESS)
	{
		dprintf(2, "Error : %s (%i)\n", name, err);
		exit(EXIT_FAILURE);
	}
}
