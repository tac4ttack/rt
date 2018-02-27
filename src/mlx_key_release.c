/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_release.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:50:30 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	mlx_key_release_1(int key, t_env *e)
{
	(key == K_ESC ? e->keys.k_esc = 0 : 0);
	(key == K_LA ? e->keys.k_la = 0 : 0);
	(key == K_RA ? e->keys.k_ra = 0 : 0);
	(key == K_UA ? e->keys.k_ua = 0 : 0);
	(key == K_DA ? e->keys.k_da = 0 : 0);
	(key == K_A ? e->keys.k_a = 0 : 0);
	(key == K_B ? e->keys.k_b = 0 : 0);
	(key == K_C ? e->keys.k_c = 0 : 0);
	(key == K_D ? e->keys.k_d = 0 : 0);
	(key == K_E ? e->keys.k_e = 0 : 0);
	(key == K_F ? e->keys.k_f = 0 : 0);
	(key == K_G ? e->keys.k_g = 0 : 0);
	(key == K_H ? e->keys.k_h = 0 : 0);
	(key == K_I ? e->keys.k_i = 0 : 0);
	(key == K_J ? e->keys.k_j = 0 : 0);
	(key == K_K ? e->keys.k_k = 0 : 0);
	(key == K_L ? e->keys.k_l = 0 : 0);
	(key == K_M ? e->keys.k_m = 0 : 0);
	(key == K_N ? e->keys.k_n = 0 : 0);
	(key == K_O ? e->keys.k_o = 0 : 0);
	(key == K_P ? e->keys.k_p = 0 : 0);
	(key == K_Q ? e->keys.k_q = 0 : 0);
	(key == K_R ? e->keys.k_r = 0 : 0);
	(key == K_S ? e->keys.k_s = 0 : 0);
	(key == K_T ? e->keys.k_t = 0 : 0);
}

static	void	mlx_key_release_2(int key, t_env *e)
{
	(key == K_U ? e->keys.k_u = 0 : 0);
	(key == K_V ? e->keys.k_v = 0 : 0);
	(key == K_W ? e->keys.k_w = 0 : 0);
	(key == K_X ? e->keys.k_x = 0 : 0);
	(key == K_Y ? e->keys.k_y = 0 : 0);
	(key == K_Z ? e->keys.k_z = 0 : 0);
	(key == K_0 ? e->keys.k_0 = 0 : 0);
	(key == K_1 ? e->keys.k_1 = 0 : 0);
	(key == K_2 ? e->keys.k_2 = 0 : 0);
	(key == K_3 ? e->keys.k_3 = 0 : 0);
	(key == K_4 ? e->keys.k_4 = 0 : 0);
	(key == K_5 ? e->keys.k_5 = 0 : 0);
	(key == K_6 ? e->keys.k_6 = 0 : 0);
	(key == K_7 ? e->keys.k_7 = 0 : 0);
	(key == K_8 ? e->keys.k_8 = 0 : 0);
	(key == K_9 ? e->keys.k_9 = 0 : 0);
	(key == K_N0 ? e->keys.k_n0 = 0 : 0);
	(key == K_N1 ? e->keys.k_n1 = 0 : 0);
	(key == K_N2 ? e->keys.k_n2 = 0 : 0);
	(key == K_N3 ? e->keys.k_n3 = 0 : 0);
	(key == K_N4 ? e->keys.k_n4 = 0 : 0);
	(key == K_N5 ? e->keys.k_n5 = 0 : 0);
	(key == K_N6 ? e->keys.k_n6 = 0 : 0);
	(key == K_N7 ? e->keys.k_n7 = 0 : 0);
	(key == K_N8 ? e->keys.k_n8 = 0 : 0);
}

static	void	mlx_key_release_3(int key, t_env *e)
{
	(key == K_N9 ? e->keys.k_n9 = 0 : 0);
	(key == K_NSLA ? e->keys.k_nsla = 0 : 0);
	(key == K_NSTR ? e->keys.k_nstr = 0 : 0);
	(key == K_NMIN ? e->keys.k_nmin = 0 : 0);
	(key == K_NPLU ? e->keys.k_nplu = 0 : 0);
	(key == K_NENT ? e->keys.k_nent = 0 : 0);
	(key == K_NDOT ? e->keys.k_ndot = 0 : 0);
	(key == K_NEQU ? e->keys.k_nequ = 0 : 0);
	(key == K_NDEL ? e->keys.k_ndel = 0 : 0);
	(key == K_HOME ? e->keys.k_home = 0 : 0);
	(key == K_END ? e->keys.k_end = 0 : 0);
	(key == K_PGU ? e->keys.k_pgu = 0 : 0);
	(key == K_PGD ? e->keys.k_pgd = 0 : 0);
	(key == K_DEL ? e->keys.k_del = 0 : 0);
	(key == K_BSP ? e->keys.k_bsp = 0 : 0);
	(key == K_SPC ? e->keys.k_spc = 0 : 0);
	(key == K_LSHI ? e->keys.k_lshi = 0 : 0);
	(key == K_RSHI ? e->keys.k_rshi = 0 : 0);
	(key == K_LCTRL ? e->keys.k_lctrl = 0 : 0);
	(key == K_RCTRL ? e->keys.k_rctrl = 0 : 0);
	(key == K_LOPT ? e->keys.k_lopt = 0 : 0);
	(key == K_ROPT ? e->keys.k_ropt = 0 : 0);
	(key == K_LCMD ? e->keys.k_lcmd = 0 : 0);
	(key == K_RCMD ? e->keys.k_rcmd = 0 : 0);
	(key == K_COM ? e->keys.k_com = 0 : 0);
}

static	void	mlx_key_release_4(int key, t_env *e)
{
	(key == K_DOT ? e->keys.k_dot = 0 : 0);
	(key == K_SLA ? e->keys.k_sla = 0 : 0);
	(key == K_SCOL ? e->keys.k_scol = 0 : 0);
	(key == K_QUO ? e->keys.k_quo = 0 : 0);
	(key == K_LBRA ? e->keys.k_lbra = 0 : 0);
	(key == K_RBRA ? e->keys.k_rbra = 0 : 0);
	(key == K_BSLA ? e->keys.k_bsla = 0 : 0);
	(key == K_DASH ? e->keys.k_dash = 0 : 0);
	(key == K_EQU ? e->keys.k_equ = 0 : 0);
	(key == K_APO ? e->keys.k_apo = 0 : 0);
	(key == K_TAB ? e->keys.k_tab = 0 : 0);
	(key == K_CAPS ? e->keys.k_caps = 0 : 0);
	(key == K_RET ? e->keys.k_ret = 0 : 0);
	(key == K_FN ? e->keys.k_fn = 0 : 0);
	(key == K_F1 ? e->keys.k_f1 = 0 : 0);
	(key == K_F2 ? e->keys.k_f2 = 0 : 0);
	(key == K_F3 ? e->keys.k_f3 = 0 : 0);
	(key == K_F4 ? e->keys.k_f4 = 0 : 0);
	(key == K_F5 ? e->keys.k_f5 = 0 : 0);
	(key == K_F6 ? e->keys.k_f6 = 0 : 0);
	(key == K_F7 ? e->keys.k_f7 = 0 : 0);
	(key == K_F8 ? e->keys.k_f8 = 0 : 0);
	(key == K_F9 ? e->keys.k_f9 = 0 : 0);
	(key == K_F10 ? e->keys.k_f10 = 0 : 0);
	(key == K_F11 ? e->keys.k_f11 = 0 : 0);
}

int				mlx_key_release(int key, t_env *e)
{
	if (e->debug == 1)
	{
		ft_putstr("Released key is ");
		ft_putnbr(key);
		ft_putchar('\n');
	}
	(key == K_F12 ? e->keys.k_f12 = 0 : 0);
	(key == K_F13 ? e->keys.k_f13 = 0 : 0);
	(key == K_F14 ? e->keys.k_f14 = 0 : 0);
	(key == K_F15 ? e->keys.k_f15 = 0 : 0);
	(key == K_F16 ? e->keys.k_f16 = 0 : 0);
	(key == K_F17 ? e->keys.k_f17 = 0 : 0);
	(key == K_F18 ? e->keys.k_f18 = 0 : 0);
	(key == K_F19 ? e->keys.k_f19 = 0 : 0);
	mlx_key_release_1(key, e);
	mlx_key_release_2(key, e);
	mlx_key_release_3(key, e);
	mlx_key_release_4(key, e);
	return (0);
}
