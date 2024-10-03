/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:30:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/03 19:55:09 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	player_dir_line(t_game *game)
{
	t_point	player;
	t_point	dir;
	t_point	scr_start;
	t_point	scr_end;

	player.x = game->player.pos.x * game->map.scale;
	player.y = game->player.pos.y * game->map.scale;
	mlx_put_pixel(game->img, player.x, player.y, 0x0F00FFF);
	dir.x = (game->player.pos.x + game->player.dir.x) * game->map.scale;
	dir.y = (game->player.pos.y + game->player.dir.y) * game->map.scale;
	draw_line(&player, &dir, game, 0xFF00FFF);
	scr_start.x = (game->player.pos.x + game->player.dir.x - game->player.scr.x)
		* game->map.scale;
	scr_start.y = (game->player.pos.y + game->player.dir.y - game->player.scr.y)
		* game->map.scale;
	mlx_put_pixel(game->img, scr_start.x, scr_start.y, 0xFFFF00F);
	scr_end.x = (game->player.pos.x + game->player.dir.x + game->player.scr.x)
		* game->map.scale;
	scr_end.y = (game->player.pos.y + game->player.dir.y + game->player.scr.y)
		* game->map.scale;
	draw_line(&scr_start, &scr_end, game, 0x00FF00FF);
}

void	draw_player(t_game *game)
{
	int	scale;
	int	posx;
	int	posy;
	int	x;
	int	y;

	scale = game->map.scale;
	posx = game->player.pos.x * scale - 5;
	posy = game->player.pos.y * scale - 5;
	x = 0;
	y = 0;
	while (y < 10)
	{
		x = 0;
		posx = game->player.pos.x * scale - 5;
		while (x < 10)
		{
			mlx_put_pixel(game->img, posx, posy, 0xFFFF00FF);
			x++;
			posx++;
		}
		y++;
		posy++;
	}
}
