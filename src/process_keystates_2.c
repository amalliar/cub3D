/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keystates_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:38:17 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/04 07:45:39 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_keystates.h"

/*
** Player moves independent of current frame rate.
*/

void		set_player_speed(t_player_data *pd, t_keystates *ks, \
				double frame_time)
{
	double		speed_mod;

	if ((ks->kvk_ansi_w == KEY_DOWN || ks->kvk_ansi_s == KEY_DOWN) && \
		(ks->kvk_ansi_a == KEY_DOWN || ks->kvk_ansi_d == KEY_DOWN))
		speed_mod = 0.50;
	else
		speed_mod = 1.0;
	pd->move_speed = frame_time * PLAYER_MOVE_SPEED * speed_mod;
	pd->rot_speed = frame_time * PLAYER_ROT_SPEED;
}

void		rotate_left(t_player_data *pd, double rot_speed)
{
	pd->old_dir_x = pd->dir_x;
	pd->dir_x = pd->dir_x * cos(-rot_speed) - pd->dir_y * \
		sin(-rot_speed);
	pd->dir_y = pd->old_dir_x * sin(-rot_speed) + pd->dir_y * \
		cos(-rot_speed);
	pd->old_plane_x = pd->plane_x;
	pd->plane_x = pd->plane_x * cos(-rot_speed) - pd->plane_y * \
		sin(-rot_speed);
	pd->plane_y = pd->old_plane_x * sin(-rot_speed) + pd->plane_y * \
		cos(-rot_speed);
}

void		rotate_right(t_player_data *pd, double rot_speed)
{
	pd->old_dir_x = pd->dir_x;
	pd->dir_x = pd->dir_x * cos(rot_speed) - pd->dir_y * \
		sin(rot_speed);
	pd->dir_y = pd->old_dir_x * sin(rot_speed) + pd->dir_y * \
		cos(rot_speed);
	pd->old_plane_x = pd->plane_x;
	pd->plane_x = pd->plane_x * cos(rot_speed) - pd->plane_y * \
		sin(rot_speed);
	pd->plane_y = pd->old_plane_x * sin(rot_speed) + pd->plane_y * \
		cos(rot_speed);
}

void		rotate_up(t_player_data *pd, double rot_speed)
{
	pd->pitch += 400 * rot_speed;
	if (pd->pitch > 600)
		pd->pitch = 600;
}

void		rotate_down(t_player_data *pd, double rot_speed)
{
	pd->pitch -= 400 * rot_speed;
	if (pd->pitch < -600)
		pd->pitch = -600;
}
