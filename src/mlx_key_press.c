/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_press.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:37:50 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/26 19:37:51 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	mlx_key_press_1(int key, t_env *e)
{
	(key == K_ESC ? e->keys.k_esc = 1 : 0);
	(key == K_LA ? e->keys.k_la = 1 : 0);
	(key == K_RA ? e->keys.k_ra = 1 : 0);
	(key == K_UA ? e->keys.k_ua = 1 : 0);
	(key == K_DA ? e->keys.k_da = 1 : 0);
	(key == K_A ? e->keys.k_a = 1 : 0);
	(key == K_B ? e->keys.k_b = 1 : 0);
	(key == K_C ? e->keys.k_c = 1 : 0);
	(key == K_D ? e->keys.k_d = 1 : 0);
	(key == K_E ? e->keys.k_e = 1 : 0);
	(key == K_F ? e->keys.k_f = 1 : 0);
	(key == K_G ? e->keys.k_g = 1 : 0);
	(key == K_H ? e->keys.k_h = 1 : 0);
	(key == K_I ? e->keys.k_i = 1 : 0);
	(key == K_J ? e->keys.k_j = 1 : 0);
	(key == K_K ? e->keys.k_k = 1 : 0);
	(key == K_L ? e->keys.k_l = 1 : 0);
	(key == K_M ? e->keys.k_m = 1 : 0);
	(key == K_N ? e->keys.k_n = 1 : 0);
	(key == K_O ? e->keys.k_o = 1 : 0);
	(key == K_P ? e->keys.k_p = 1 : 0);
	(key == K_Q ? e->keys.k_q = 1 : 0);
	(key == K_R ? e->keys.k_r = 1 : 0);
	(key == K_S ? e->keys.k_s = 1 : 0);
	(key == K_T ? e->keys.k_t = 1 : 0);
}

static	void	mlx_key_press_2(int key, t_env *e)
{
	(key == K_U ? e->keys.k_u = 1 : 0);
	(key == K_V ? e->keys.k_v = 1 : 0);
	(key == K_W ? e->keys.k_w = 1 : 0);
	(key == K_X ? e->keys.k_x = 1 : 0);
	(key == K_Y ? e->keys.k_y = 1 : 0);
	(key == K_Z ? e->keys.k_z = 1 : 0);
	(key == K_0 ? e->keys.k_0 = 1 : 0);
	(key == K_1 ? e->keys.k_1 = 1 : 0);
	(key == K_2 ? e->keys.k_2 = 1 : 0);
	(key == K_3 ? e->keys.k_3 = 1 : 0);
	(key == K_4 ? e->keys.k_4 = 1 : 0);
	(key == K_5 ? e->keys.k_5 = 1 : 0);
	(key == K_6 ? e->keys.k_6 = 1 : 0);
	(key == K_7 ? e->keys.k_7 = 1 : 0);
	(key == K_8 ? e->keys.k_8 = 1 : 0);
	(key == K_9 ? e->keys.k_9 = 1 : 0);
	(key == K_N0 ? e->keys.k_n0 = 1 : 0);
	(key == K_N1 ? e->keys.k_n1 = 1 : 0);
	(key == K_N2 ? e->keys.k_n2 = 1 : 0);
	(key == K_N3 ? e->keys.k_n3 = 1 : 0);
	(key == K_N4 ? e->keys.k_n4 = 1 : 0);
	(key == K_N5 ? e->keys.k_n5 = 1 : 0);
	(key == K_N6 ? e->keys.k_n6 = 1 : 0);
	(key == K_N7 ? e->keys.k_n7 = 1 : 0);
	(key == K_N8 ? e->keys.k_n8 = 1 : 0);
}

static	void	mlx_key_press_3(int key, t_env *e)
{
	(key == K_N9 ? e->keys.k_n9 = 1 : 0);
	(key == K_NSLA ? e->keys.k_nsla = 1 : 0);
	(key == K_NSTR ? e->keys.k_nstr = 1 : 0);
	(key == K_NMIN ? e->keys.k_nmin = 1 : 0);
	(key == K_NPLU ? e->keys.k_nplu = 1 : 0);
	(key == K_NENT ? e->keys.k_nent = 1 : 0);
	(key == K_NDOT ? e->keys.k_ndot = 1 : 0);
	(key == K_NEQU ? e->keys.k_nequ = 1 : 0);
	(key == K_NDEL ? e->keys.k_ndel = 1 : 0);
	(key == K_HOME ? e->keys.k_home = 1 : 0);
	(key == K_END ? e->keys.k_end = 1 : 0);
	(key == K_PGU ? e->keys.k_pgu = 1 : 0);
	(key == K_PGD ? e->keys.k_pgd = 1 : 0);
	(key == K_DEL ? e->keys.k_del = 1 : 0);
	(key == K_BSP ? e->keys.k_bsp = 1 : 0);
	(key == K_SPC ? e->keys.k_spc = 1 : 0);
	(key == K_LSHI ? e->keys.k_lshi = 1 : 0);
	(key == K_RSHI ? e->keys.k_rshi = 1 : 0);
	(key == K_LCTRL ? e->keys.k_lctrl = 1 : 0);
	(key == K_RCTRL ? e->keys.k_rctrl = 1 : 0);
	(key == K_LOPT ? e->keys.k_lopt = 1 : 0);
	(key == K_ROPT ? e->keys.k_ropt = 1 : 0);
	(key == K_LCMD ? e->keys.k_lcmd = 1 : 0);
	(key == K_RCMD ? e->keys.k_rcmd = 1 : 0);
	(key == K_COM ? e->keys.k_com = 1 : 0);
}

static	void	mlx_key_press_4(int key, t_env *e)
{
	(key == K_DOT ? e->keys.k_dot = 1 : 0);
	(key == K_SLA ? e->keys.k_sla = 1 : 0);
	(key == K_SCOL ? e->keys.k_scol = 1 : 0);
	(key == K_QUO ? e->keys.k_quo = 1 : 0);
	(key == K_LBRA ? e->keys.k_lbra = 1 : 0);
	(key == K_RBRA ? e->keys.k_rbra = 1 : 0);
	(key == K_BSLA ? e->keys.k_bsla = 1 : 0);
	(key == K_DASH ? e->keys.k_dash = 1 : 0);
	(key == K_EQU ? e->keys.k_equ = 1 : 0);
	(key == K_APO ? e->keys.k_apo = 1 : 0);
	(key == K_TAB ? e->keys.k_tab = 1 : 0);
	(key == K_CAPS ? e->keys.k_caps = 1 : 0);
	(key == K_RET ? e->keys.k_ret = 1 : 0);
	(key == K_FN ? e->keys.k_fn = 1 : 0);
	(key == K_F1 ? e->keys.k_f1 = 1 : 0);
	(key == K_F2 ? e->keys.k_f2 = 1 : 0);
	(key == K_F3 ? e->keys.k_f3 = 1 : 0);
	(key == K_F4 ? e->keys.k_f4 = 1 : 0);
	(key == K_F5 ? e->keys.k_f5 = 1 : 0);
	(key == K_F6 ? e->keys.k_f6 = 1 : 0);
	(key == K_F7 ? e->keys.k_f7 = 1 : 0);
	(key == K_F8 ? e->keys.k_f8 = 1 : 0);
	(key == K_F9 ? e->keys.k_f9 = 1 : 0);
	(key == K_F10 ? e->keys.k_f10 = 1 : 0);
	(key == K_F11 ? e->keys.k_f11 = 1 : 0);
}

/*
**gerer le key repeat
*/

int				mlx_key_press(int key, t_env *e)
{
	if (e->debug == 1)
	{
		ft_putstr("Pressed key is ");
		ft_putnbr(key);
		ft_putchar('\n');
	}
	(key == K_F12 ? e->keys.k_f12 = 1 : 0);
	(key == K_F13 ? e->keys.k_f13 = 1 : 0);
	(key == K_F14 ? e->keys.k_f14 = 1 : 0);
	(key == K_F15 ? e->keys.k_f15 = 1 : 0);
	(key == K_F16 ? e->keys.k_f16 = 1 : 0);
	(key == K_F17 ? e->keys.k_f17 = 1 : 0);
	(key == K_F18 ? e->keys.k_f18 = 1 : 0);
	(key == K_F19 ? e->keys.k_f19 = 1 : 0);
	mlx_key_press_1(key, e);
	mlx_key_press_2(key, e);
	mlx_key_press_3(key, e);
	mlx_key_press_4(key, e);
	return (0);
}
