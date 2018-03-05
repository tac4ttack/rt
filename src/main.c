/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:32:13 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 18:55:39 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_usage()
{
	ft_putendl("\n\x1b[1;31mScene file is missing!\x1b[0m");
	ft_putendl("usage: rt <scene> [options]\n\n\t--display\n\t--debug-level\n\
	--no-xshm\n\t--sync\n\t--show-events\n\t--no-show-events\n");
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (ac < 2 || ac > 8)
		print_usage();
	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[1;31mCan't initialize RT\x1b[0m", NULL);
	ft_bzero(e, sizeof(t_env));
	init(e, av[1]);
		
	gtk_main();
//	set_hooks(e);
	return (0);
}
