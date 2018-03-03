/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:32:13 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/03 21:14:13 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_usage()
{
	ft_putendl("\n\x1b[2;31mScene file is missing!\x1b[0m");
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
		s_error("\x1b[2;31mCan't initialize RT environment\x1b[0m", NULL);
	ft_bzero(e, sizeof(t_env));
//	gtk_init(&ac, &av); // resoudre plus tard probleme arguments gtk
	gtk_init(0, NULL);
	init(e, av[1]);
	gtk_main();
//	set_hooks(e);
	return (0);
}
