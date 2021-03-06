/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:02:54 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/03 20:57:47 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <SDL2/SDL.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "audio.h"
# include "settings.h"
# include "snd.h"

enum				e_game_states
{
	GS_NORMAL,
	GS_DEATH,
	GS_RESTART,
	GS_RESPAWN,
	GS_END,
	GS_HALT
};

enum				e_key_states
{
	KEY_UP,
	KEY_DOWN
};

enum				e_render_modes
{
	LOOP,
	SCREENSHOT
};

enum				e_states
{
	ENABLED,
	DISABLED
};

enum				e_door_states
{
	OPEN,
	CLOSED,
	OPENING,
	CLOSING
};

enum				e_secret_states
{
	INACTIVE,
	ACTIVE
};

enum				e_weapon_types
{
	MELEE,
	HITSCAN
};

enum				e_weapon_firing_modes
{
	SEMI_AUTO,
	FULL_AUTO
};

enum				e_weapon_states
{
	IDLE,
	FIRING,
	EMPTY
};

enum	e_object_states
{
	PLACED,
	TAKEN,
	NOT_A_PICKUP
};

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_fpoint
{
	double			x;
	double			y;
}					t_fpoint;

typedef struct		s_segment
{
	t_fpoint		p0;
	t_fpoint		p1;
}					t_segment;

typedef struct		s_line
{
	double			a;
	double			b;
	double			c;
}					t_line;

typedef struct		s_mlx_image
{
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
	void			*img;
	char			*addr;
}					t_mlx_image;

typedef struct		s_mlx_data
{
	int				width;
	int				height;
	int				frames_per_second;
	double			frame_time;
	void			*mlx;
	void			*win;
	t_mlx_image		frame;
}					t_mlx_data;

typedef struct		s_textures
{
	t_mlx_image		walls[NUM_WALL_TEXTURES];
	t_mlx_image		objects[NUM_OBJECT_TEXTURES];
	t_mlx_image		guard[NUM_GUARD_TEXTURES];
	t_mlx_image		hud[NUM_HUD_TEXTURES];
	t_mlx_image		faces[NUM_FACES_TEXTURES];
	t_mlx_image		menu[NUM_MENU_TEXTURES];
	t_mlx_image		floor;
	t_mlx_image		ceiling;
}					t_textures;

typedef struct		s_block
{
	int				id_tex_n;
	int				id_tex_s;
	int				id_tex_e;
	int				id_tex_w;
}					t_block;

typedef struct		s_map_data
{
	int				width;
	int				height;
	char			**map;
}					t_map_data;

typedef struct		s_door
{
	int				x;
	int				y;
	int				state;
	double			s_timer;
	double			c_timer;
	char			type;
}					t_door;

typedef struct		s_secret
{
	int				x;
	int				y;
	int				state;
	double			s_timer;
	char			type;
}					t_secret;

typedef struct		s_weapon
{
	int				id;
	int				type;
	int				firing_mode;
	int				state;
	int				frame;
	bool			unlocked;
	double			min_frame_time;
	t_mlx_image		frames[NUM_WEAPON_FRAMES];
	t_mlx_image		*hudpic;
}					t_weapon;

typedef struct		s_effects
{
	clock_t			r_bj_evil_grin;
	clock_t			r_item_pickup;
	clock_t			r_player_hit;
	clock_t			r_player_dead;
	clock_t			r_player_respawn;
}					t_effects;

typedef struct		s_player_data
{
	t_weapon		weapons[NUM_WEAPONS];
	t_weapon		*active_weapon;
	t_effects		effects;
	t_door			*door;
	t_secret		*secret;
	t_segment		s1;
	t_segment		s2;
	t_segment		s3;
	t_segment		ray;
	t_line			line1;
	t_line			line2;
	clock_t			r_facetimer;
	unsigned		facecount;
	int				faceframe;
	int				health;
	int				lives;
	int				ammo;
	int				score;
	int				level;
	int				step_x;
	int				step_y;
	int				hit;
	int				door_hit;
	int				secret_hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	int				p;
	double			pos_x;
	double			pos_y;
	double			default_pos_x;
	double			default_pos_y;
	double			pos_z;
	double			map_x;
	double			map_y;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_dir_y;
	double			default_dir_x;
	double			default_dir_y;
	double			plane_x;
	double			plane_y;
	double			default_plane_x;
	double			default_plane_y;
	double			old_plane_x;
	double			old_plane_y;
	double			camera_x;
	double			camera_z;
	double			pitch;
	double			ray_dir_x;
	double			ray_dir_x0;
	double			ray_dir_x1;
	double			ray_dir_y;
	double			ray_dir_y0;
	double			ray_dir_y1;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			move_speed;
	double			rot_speed;
	double			wall_x;
	double			step;
	double			tex_pos;
	double			row_distance;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x;
	double			floor_y;
	double			*zbuffer;
	double			v0;
	bool			is_floor;
}					t_player_data;

typedef struct		s_key_states
{
	int				kvk_ansi_w;
	int				kvk_ansi_a;
	int				kvk_ansi_s;
	int				kvk_ansi_d;
	int				kvk_leftarrow;
	int				kvk_rightarrow;
	int				kvk_uparrow;
	int				kvk_downarrow;
}					t_key_states;

typedef struct		s_button_states
{
	int				mb_left;
	int				mb_right;
	int				mb_middle;
	int				mb_wheel_up;
	int				mb_wheel_down;
}					t_button_states;

typedef struct		s_estate
{
	bool			rotate;
	int				shapenum;
	double			s_max_time;
	void			(*falways)();
	void			(*fonce)();
	int				soundnum;
	struct s_estate	*next;
}					t_estate;

typedef struct		s_enemie_data
{
	t_estate		*state;
	int				health;
	bool			is_alive;
	bool			is_tracking_player;
	double			dir_x;
	double			dir_y;
	clock_t			r_timer;
}					t_enemie_data;

typedef struct		s_sprite
{
	t_mlx_image		*tex;
	t_enemie_data	*e_data;
	int				state;
	double			x;
	double			y;
	double			dist;
	char			type;
	bool			is_visible;
}					t_sprite;

typedef struct		s_sprite_data
{
	int				num_sprites;
	int				v_move_screen;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	int				d;
	int				stripe;
	int				y;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
}					t_sprite_data;

typedef struct		s_scene
{
	int				game_state;
	int				render_started;
	int				mouse_grabbing;
	int				num_doors;
	int				num_secrets;
	t_button_states	button_states;
	t_door			*doors;
	t_secret		*secrets;
	t_key_states	key_states;
	t_map_data		map_data;
	t_mlx_data		mlx_data;
	t_mlx_image		crosshairs[NUM_CROSSHAIRS];
	t_player_data	player_data;
	t_sprite		*sprites;
	t_sprite_data	sprite_data;
	t_textures		textures;
	Audio			*music[NUM_MUSIC_TRACKS];
	Audio			*sounds[NUM_SOUNDS];
}					t_scene;

void				exit_failure(char *format, ...);
void				take_screenshot(t_scene *scene);

extern t_estate		g_grdidle;
extern t_estate		g_grdstand;
extern t_estate		g_grdshoot0;
extern t_estate		g_grdshoot1;
extern t_estate		g_grdshoot2;
extern t_estate		g_grdshoot3;
extern t_estate		g_grdpain;
extern t_estate		g_grddie0;
extern t_estate		g_grddie1;
extern t_estate		g_grddie2;
extern t_estate		g_grddie3;

#endif
