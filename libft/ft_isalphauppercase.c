/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphauppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:31:51 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/11 17:32:39 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalphauppercase(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}
