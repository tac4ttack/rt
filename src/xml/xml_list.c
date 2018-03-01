/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:46:52 by fmessina          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_node		*xml_list_new(char type)
{
	t_node	*new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	ft_bzero(new, sizeof(t_node));
	new->type = type;
	new->next = NULL;
	return (new);
}

void		xml_list_add_first(t_node **begin, t_node *node)
{
	if (node != NULL)
	{
		node->next = *begin;
		*begin = node;
	}
}

void		xml_list_clean(t_env *e, t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	if (*list)
	{
		while (tmp)
		{
			tmp = (*list)->next;
			free(*list);
			*list = tmp;
		}
	}
	else
		s_error("\x1b[2;31mError while cleaning scene linked list\x1b[0m", e);
}
