/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 02:03:25 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/03 06:17:44 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "mlx.h"

static void		calc_block(t_player_data *pd, t_mlx_image *frame)
{
	pd->ray_dir_x0 = pd->dir_x - pd->plane_x;
	pd->ray_dir_y0 = pd->dir_y - pd->plane_y;
	pd->ray_dir_x1 = pd->dir_x + pd->plane_x;
	pd->ray_dir_y1 = pd->dir_y + pd->plane_y;
	pd->row_distance = pd->pos_z / pd->p;
	pd->floor_step_x = pd->row_distance * (pd->ray_dir_x1 - pd->ray_dir_x0) \
		/ frame->width;
	pd->floor_step_y = pd->row_distance * (pd->ray_dir_y1 - pd->ray_dir_y0) \
		/ frame->width;
	pd->floor_x = pd->pos_x + pd->row_distance * pd->ray_dir_x0;
	pd->floor_y = pd->pos_y + pd->row_distance * pd->ray_dir_y0;
}

static void		calc_texture_xy(t_player_data *pd, t_mlx_image *tex)
{
	pd->tex_x = (int)(tex->width * \
		(pd->floor_x - pd->map_x)) & (tex->width - 1);
	pd->tex_y = (int)(tex->height * \
		(pd->floor_y - pd->map_y)) & (tex->height - 1);
}

static void		fill_line(t_player_data *pd, t_mlx_image *frame, \
					t_textures *textures, int y)
{
	int		x;
	int		tex_size_differs;

	if ((*textures).floor.width != (*textures).ceiling.width || \
		(*textures).floor.height != (*textures).ceiling.height)
		tex_size_differs = 1;
	else
		tex_size_differs = 0;
	x = 0;
	while (x < frame->width)
	{
		pd->map_x = (int)pd->floor_x;
		pd->map_y = (int)pd->floor_y;
		calc_texture_xy(pd, &textures->floor);
		mlx_pixel_set(frame, x, y, mlx_pixel_get(&textures->floor, \
			pd->tex_x, pd->tex_y));
		if (tex_size_differs)
			calc_texture_xy(pd, &textures->ceiling);
		mlx_pixel_set(frame, x, frame->height - y - 1, \
			mlx_pixel_get(&textures->ceiling, pd->tex_x, pd->tex_y));
		pd->floor_x += pd->floor_step_x;
		pd->floor_y += pd->floor_step_y;
		++x;
	}
}

void			render_floor_and_ceiling(t_scene *scene)
{
	t_mlx_image		*frame;
	t_player_data	*pd;
	t_textures		*textures;
	int				y;

	frame = &(*scene).mlx_data.frame;
	pd = &scene->player_data;
	textures = &scene->textures;
	y = 0;
	while (y < frame->height)
	{
		pd->p = y - frame->height / 2;
		calc_block(pd, frame);
		fill_line(pd, frame, textures, y);
		++y;
	}
}