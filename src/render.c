/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/25 13:41:01 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void blank(t_game *game)
{
	int x = WIDTH/2;
	int y = 0;

	while (x < WIDTH)
	{
		y = 0;
		while (y <= (HEIGHT / 2))
			mlx_put_pixel(game->img, x, y++, game->map.ceiling);
		while (y < (HEIGHT))
			mlx_put_pixel(game->img, x, y++, game->map.floor);
		x++;
	}
}

void	screen_init(t_player *player)
{
	t_point dir;
	t_point scr;

	dir = player->dir;
	player->dir.x/= 10;
	player->dir.y /=10;
	scr.x = 0;
	scr.y = 0;
	if (dir.y > 0)
		scr.x = (-player->pov)/10;
	else if (dir.y < 0)
		scr.x = player->pov / 10;
	else if (dir.x > 0)
		scr.y = player->pov / 10;
	else if (dir.x < 0)
		scr.y = -player->pov / 10;
	player->scr = scr;
}

void render(void *param)
{
	t_game *game;

	game = (t_game*)param;
	grid(game);
	blank(game);
	ft_hook(game);
	raycasting(game);
	draw_player(game);
	player_dir_line(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	usleep(10000);
}
