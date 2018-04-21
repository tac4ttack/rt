/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_print_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 20:33:52 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/21 20:33:53 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void						cuda_print_mem(void)
{
	int						device_id;
	size_t 					mem_free;
	size_t 					mem_total;
	struct cudaDeviceProp	device_prop;
	char					*str;

	device_id = 0;
	cudaSetDevice(device_id);
	cudaGetDeviceProperties(&device_prop, device_id);
	cudaMemGetInfo(&mem_free, &mem_total);
	ft_putstr("\nDevice ");
	ft_putnbr(device_id);
	ft_putstr(" ");
	ft_putstr(device_prop.name);
	ft_putstr(" ");
	str = ft_ftoa((float)mem_free / (1024 * 1024));
	ft_putstr(str);
	free(str);
	ft_putstr(" MB Free of ");
	str = ft_ftoa((float)mem_total / (1024 * 1024));
	ft_putstr(str);
	free(str);
	ft_putstr(" MB Total\n");
}
