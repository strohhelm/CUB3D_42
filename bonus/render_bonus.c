/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/11 21:43:50 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// draws the background colours, depending on mouse vertical input.
void	blank(t_game *game)
{
	int	x;
	int	y;
	uint	col;
	
	uint	flo;

	x = -1;
	col = game->map.ceiling;
	flo = game->map.floor;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < HEIGHT / 2 - game->y)
				mlx_put_pixel(game->img, x, y, col);
			else
				mlx_put_pixel(game->img, x, y, flo);
		}
	}
}

// initializes the crosshai img that will be rendered on top of the main img
void	put_crosshair(t_game *game)
{
	game->cross = mlx_new_image(game->mlx, CROSSHAIR, CROSSHAIR);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 6);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 5);
	draw_circle(game->cross, 0xFFFF00FF, CROSSHAIR / 2 - 4);
	draw_circle(game->cross, 0xFFFF00FF, CROSSHAIR / 2 - 3);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 2);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 1);
	mlx_image_to_window(game->mlx, game->cross, WIDTH / 2
		- game->cross->width/2, HEIGHT/2
		- game->cross->height / 2);
}

// wierd initializing fuction. to keep mlx from returning wrong values
// for mouse input the first two frames.
// idk why that happens but works like that :P.
int	mousecounter(t_game *game)
{
	static int	i = 0;
	
	if (i++ < 2)
	{
		mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
		mlx_get_mouse_pos(game->mlx, &game->x, &game->x);
		game->x = 0;
		return (0);
	}
	return (1);
}

//main render loop
void render(void *param)
{
	t_game		*game;
	double		t;
	double		ft;
	double		time;
	static int	frame = 1;
	static t_ai *e = NULL;
	static int	i = 0;

	game = (t_game *)param;
	if (!mousecounter(game))
		return ;
	t = mlx_get_time();
	if (frame == 30)
		frame = 1;
	time = 1.0 / FPS;
	if (i++ == 0)
	{
		e = load_alien(game);
		game->hp = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->hp, 0, 0);
		health_bar(game);
	}
	ft_hook(game);
	if (!game->over)
	{
		blank(game);
		minimap(game);
		raycasting(game);
		update_enemy_pos(&e, game);
		enemy_dist(game, &e, frame);
		gun_anim(game, frame);
		draw_doors(game);
		doors(game);
		ft = mlx_get_time() - t;
		if (ft < time)
			usleep((int)((time - ft) * 1000000));
		frame++;
	}
}
