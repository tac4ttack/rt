/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:19:10 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 11:19:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_H
# define GEN_H

# include "libft.h"
# include <stdbool.h>

typedef struct			s_gen
{
	size_t				mem_size;
	size_t				length;
	void				*mem;
	bool				(*add)(struct s_gen *, void *);
	bool				(*remove_mem_index)(struct s_gen *, size_t);
	bool				(*remove_index)(struct s_gen *, size_t);
	void				(*print)(struct s_gen *, \
								void (*)(struct s_gen *, void *));
}						t_gen;

void					*gen_construct();
bool					gen_add(t_gen *gen, void *elem);
void					*gen_destruct(t_gen **gen);
void					*gen_get_index_ptr(t_gen *gen, int index);
int						gen_get_ptr_index(t_gen *gen, void *obj);
bool					gen_remove_mem_index(t_gen *gen, \
											size_t mem_remove_index);
bool					gen_remove_index(t_gen *gen, size_t remove_index);
void					gen_print(t_gen *gen, void (*print)(t_gen *, void *));
#endif
