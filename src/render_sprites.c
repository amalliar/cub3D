/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 13:04:05 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/27 11:38:16 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "ft_stdlib.h"
#include "item_pickup.h"
#include "render_scene.h"

static void		calculate_sprite_distances(t_scene *scene, t_sprite *sprites)
{
	t_player_data	*pd;
	int				i;

	pd = &scene->player_data;
	i = 0;
	while (i < (scene->sprite_data).num_sprites)
	{
		sprites[i].dist = sqrt(pow(pd->pos_x - sprites[i].x, 2) + \
			pow(pd->pos_y - sprites[i].y, 2));
		++i;
	}
}

static int		compar(const void *p1, const void *p2)
{
	double		delta;

	delta = ((t_sprite *)p2)->dist - ((t_sprite *)p1)->dist;
	if (delta < 0)
		return (-1);
	if (delta > 0)
		return (1);
	return (0);
}

static void		init_sprite_data(t_mlx_image *frame, t_player_data *pd, \
					t_sprite_data *sd)
{
	sd->inv_det = 1.0 / (pd->plane_x * pd->dir_y - pd->dir_x * pd->plane_y);
	sd->transform_x = sd->inv_det * (pd->dir_y * sd->sprite_x - \
		pd->dir_x * sd->sprite_y);
	sd->transform_y = sd->inv_det * (-pd->plane_y * sd->sprite_x + \
		pd->plane_x * sd->sprite_y);
	sd->sprite_screen_x = (int)(frame->width / 2 * (1 + sd->transform_x / \
		sd->transform_y));
	sd->v_move_screen = pd->pitch + pd->pos_z / sd->transform_y;
	sd->sprite_height = ft_abs(frame->height / sd->transform_y);
	sd->draw_start_y = -sd->sprite_height / 2 + frame->height / 2 + \
		sd->v_move_screen;
	if (sd->draw_start_y < 0)
		sd->draw_start_y = 0;
	sd->draw_end_y = sd->sprite_height / 2 + frame->height / 2 + \
		sd->v_move_screen;
	if (sd->draw_end_y >= frame->height)
		sd->draw_end_y = frame->height - 1;
	sd->sprite_width = ft_abs(frame->height / sd->transform_y);
	sd->draw_start_x = -sd->sprite_width / 2 + sd->sprite_screen_x;
	if (sd->draw_start_x < 0)
		sd->draw_start_x = 0;
	sd->draw_end_x = sd->sprite_width / 2 + sd->sprite_screen_x;
	if (sd->draw_end_x >= frame->width)
		sd->draw_end_x = frame->width - 1;
	sd->stripe = sd->draw_start_x;
}

static void		draw_sprite(t_sprite *sp, t_mlx_image *frame, \
					t_player_data *pd, t_sprite_data *sd)
{
	int		color;

	while (sd->stripe < sd->draw_end_x)
	{
		sd->tex_x = (int)(256 * (sd->stripe - (-sd->sprite_width / 2 + \
		sd->sprite_screen_x)) * sp->tex->width / sd->sprite_width) / 256;
		sd->y = sd->draw_start_y;
		if (sd->transform_y > 0 && sd->stripe > 0 && sd->stripe < \
			frame->width && sd->transform_y < (pd->zbuffer)[sd->stripe])
			while (sd->y < sd->draw_end_y)
			{
				sd->d = (sd->y - sd->v_move_screen) * 256 - frame->height * \
					128 + sd->sprite_height * 128;
				sd->tex_y = ((sd->d * sp->tex->height) \
					/ sd->sprite_height) / 256;
				color = mlx_pixel_get(sp->tex, sd->tex_x, sd->tex_y);
				if (color != CLR_NAN)
				{
					mlx_pixel_set(frame, sd->stripe, sd->y, color);
					sp->is_visible = true;
				}
				++sd->y;
			}
		++sd->stripe;
	}
}

void			render_sprites(t_scene *scene)
{
	t_sprite		*sprites;
	t_sprite_data	*sd;
	t_player_data	*pd;
	int				i;

	sprites = scene->sprites;
	sd = &scene->sprite_data;
	pd = &scene->player_data;
	calculate_sprite_distances(scene, sprites);
	ft_qsort(sprites, sd->num_sprites, sizeof(t_sprite), compar);
	i = 0;
	while (i < sd->num_sprites)
	{
		if (sprites[i].state != TAKEN)
		{
			sd->sprite_x = sprites[i].x - pd->pos_x;
			sd->sprite_y = sprites[i].y - pd->pos_y;
			sprites[i].is_visible = false;
			init_sprite_data(&(scene->mlx_data).frame, pd, sd);
			draw_sprite(sprites + i, &(scene->mlx_data).frame, pd, sd);
		}
		++i;
	}
}
