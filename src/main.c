/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:32:13 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 22:35:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_argument_error(char *arg, int type)
{
	if (type == 0)
	{
		ft_putstr("\n\x1b[1;31mERROR!\nInvalid scene file -> \x1b[0m");
		ft_putstr(arg);
	}
	if (type == 1)
	{
		ft_putstr("\n\x1b[1;31mERROR!\nInvalid argument -> \x1b[0m");
		ft_putstr(arg);
	}
	exit(EXIT_FAILURE);
}

void		check_arguments(int ac, char **av)
{
	int i;

	i = ft_strlen(av[1]) - 4;
	if (ft_strcmp(av[1] + i, ".xml") != 0)
		print_argument_error(av[1], 0);
	i = 2;
	if (ac > 2)
		while (i < ac)
		{
			if (ft_strncmp(av[i], "--display", 9) != 0 &&
			ft_strncmp(av[i], "--debug_level", 13) != 0 &&
			ft_strncmp(av[i], "--no-xshm", 9) != 0 &&
			ft_strncmp(av[i], "--sync", 6) != 0 &&
			ft_strncmp(av[i], "--show-events", 13) != 0 &&
			ft_strncmp(av[i], "--no-show-events", 16) != 0)
				print_argument_error(av[i], 1);
			else
				i++;
		}
}

void		print_usage()
{
	ft_putendl("\n\x1b[1;31mScene file is missing!\x1b[0m");
	ft_putendl("usage: rt <scene.xml> [options]\n\n\t--display\n\
				--debug-level\n\t--no-xshm\n\t--sync\n\t--show-events\n\
				--no-show-events\n");
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (ac < 2 || ac > 8)
		print_usage();
	else
		check_arguments(ac, av);
	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[1;31mCan't initialize RT\x1b[0m", NULL);
	ft_bzero(e, sizeof(t_env));
	e->scene_file = ft_strdup(av[1]);
	
	init(e);
		
//	set_hooks(e);
	return (0);
}
