/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyrelease_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:25:47 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/07 17:54:25 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycodes.h"

int		keyrelease_handler(int keycode, t_scene *scene)
{
	t_keystates		*ks;

	ks = &scene->keystates;
	if (keycode == KVK_ANSI_W)
		ks->kvk_ansi_w = KEY_UP;
	else if (keycode == KVK_ANSI_A)
		ks->kvk_ansi_a = KEY_UP;
	else if (keycode == KVK_ANSI_S)
		ks->kvk_ansi_s = KEY_UP;
	else if (keycode == KVK_ANSI_D)
		ks->kvk_ansi_d = KEY_UP;
	else if (keycode == KVK_LEFTARROW)
		ks->kvk_leftarrow = KEY_UP;
	else if (keycode == KVK_RIGHTARROW)
		ks->kvk_rightarrow = KEY_UP;
	return (0);
}
