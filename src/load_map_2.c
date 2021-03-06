/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 21:44:31 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/03 21:47:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "load_map.h"

static void		init_wpn_knife(t_weapon *wpn, t_mlx_image *hud)
{
	wpn->id = 0;
	wpn->type = MELEE;
	wpn->firing_mode = SEMI_AUTO;
	wpn->state = IDLE;
	wpn->frame = 0;
	wpn->min_frame_time = 0.025;
	wpn->hudpic = hud + 11;
	wpn->unlocked = true;
}

static void		init_wpn_pistol(t_weapon *wpn, t_mlx_image *hud)
{
	wpn->id = 1;
	wpn->type = HITSCAN;
	wpn->firing_mode = SEMI_AUTO;
	wpn->state = IDLE;
	wpn->frame = 0;
	wpn->min_frame_time = 0.025;
	wpn->hudpic = hud + 12;
	wpn->unlocked = true;
}

static void		init_wpn_machinegun(t_weapon *wpn, t_mlx_image *hud)
{
	wpn->id = 2;
	wpn->type = HITSCAN;
	wpn->firing_mode = FULL_AUTO;
	wpn->state = IDLE;
	wpn->frame = 0;
	wpn->min_frame_time = 0.05;
	wpn->hudpic = hud + 13;
	wpn->unlocked = false;
}

static void		init_wpn_chaingun(t_weapon *wpn, t_mlx_image *hud)
{
	wpn->id = 3;
	wpn->type = HITSCAN;
	wpn->firing_mode = FULL_AUTO;
	wpn->state = IDLE;
	wpn->frame = 0;
	wpn->min_frame_time = 0.05;
	wpn->hudpic = hud + 14;
	wpn->unlocked = false;
}

void			init_player_weapons(t_player_data *pd, t_mlx_image *hud)
{
	init_wpn_knife(pd->weapons + 0, hud);
	init_wpn_pistol(pd->weapons + 1, hud);
	init_wpn_machinegun(pd->weapons + 2, hud);
	init_wpn_chaingun(pd->weapons + 3, hud);
	pd->active_weapon = pd->weapons + 1;
}
