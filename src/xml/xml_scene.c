/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:11:29 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 15:09:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_scene_res(t_env *e, char **att, int *i)
{
	int		w;
	int		h;

	if (e && att && i)
	{
		w = ft_atoi(att[(*i)++] + 5);
		h = ft_atoi(att[(*i)++]);
		if (w == 0 || h == 0)
			s_error("\x1b[1;31mError scene Width/Height must be > 0\x1b[0m", e);
		else
		{
			e->scene->win_w = (w < 0 ? -w : w);
			e->scene->win_h = (h < 0 ? -h : h);
		}
	}
	else
		s_error("\x1b[1;31mError reading RESOLUTION from scene node\x1b[0m", e);
}

static void	xml_scene_ambient(t_env *e, char **att, int *i)
{
	if (e && att && i)
	{
		if (att[(*i)] == NULL)
			s_error("\x1b[1;31mError reading AMBIENT scene node\x1b[0m", e);
		e->scene->ambient.x = ft_atof(att[(*i)++] + 9);
		e->scene->ambient.y = ft_atof(att[(*i)++]);
		e->scene->ambient.z = ft_atof(att[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading AMBIENT from scene node\x1b[0m", e);
}

/*
** RAJOUTER CONTROLE DE L'AMBIANTE QUAND ON SAURA QUELLE VALEUR CA DOIT AVOIR
*/

static void	xml_scene_parse(t_env *e, char *node)
{
	int		i;
	char	**tmp;

	i = 1;
	tmp = ft_strsplit(node, ' ');
	if (xml_check_node_format(tmp, 0) != 0)
		s_error("\x1b[1;31mError CAM format\x1b[0m", e);
	if (ft_strncmp(tmp[i], "res=\"", 5) != 0 || tmp[i] == NULL)
		s_error("\x1b[1;31mError in scene RESOLUTION expected in #0\x1b[0m", e);
	else
		xml_scene_res(e, tmp, &i);
	if (ft_strncmp(tmp[i], "ambient=\"", 9) != 0 || tmp[(i)] == NULL)
		s_error("\x1b[1;31mError in scene, AMBIENT expected in #1\x1b[0m", e);
	else
		xml_scene_ambient(e, tmp, &i);
	if (tmp[i] == NULL)
	{
		if (tmp[i - 1][ft_strlen(tmp[i - 1]) - 1] != '>')
			s_error("\x1b[1;31mError SCENE node isn't closed\x1b[0m", e);
	}
	else if (tmp[i][ft_strlen(tmp[i]) - 1] != '>')
		s_error("\x1b[1;31mError CAMERA node isn't closed\x1b[0m", e);
	xml_node_clean(tmp);
}

void		xml_node_scene(t_env *e, char *node, char mod)
{
	if (mod == 0)
	{
		if (ft_strncmp(node, "scene ", 6) != 0)
			s_error("\x1b[1;31mError in XML syntax\x1b[0m", e);
		XML->in_scene = 1;
		xml_scene_parse(e, node);
	}
	else if (mod == 1)
	{
		if (ft_strlen(node) != 8)
			s_error("\x1b[1;31mError in XML syntax\x1b[0m", e);
		XML->in_scene = 0;
	}
}
