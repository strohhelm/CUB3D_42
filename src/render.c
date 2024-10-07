/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/07 10:05:36 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	blank(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (y <= HEIGHT / 2 && y >= 0)
				mlx_put_pixel(game->img, x, y, game->map.ceiling);
			else
				mlx_put_pixel(game->img, x, y, game->map.floor);
		}
	}
}

void	screen_init(t_player *player)
{
	t_point	dir;
	t_point	scr;

	dir = player->dir;
	player->dir.x /= 10;
	player->dir.y /= 10;
	scr.x = 0;
	scr.y = 0;
	if (dir.y > 0)
		scr.x = (-player->pov) / 10;
	else if (dir.y < 0)
		scr.x = player->pov / 10;
	else if (dir.x > 0)
		scr.y = player->pov / 10;
	else if (dir.x < 0)
		scr.y = -player->pov / 10;
	player->scr = scr;
}

void	render(void *param)
{
	t_game		*game;
	double		t;
	double		ft;
	double		time;
	static int	i;

	time = 1.0 / 30;
	game = (t_game *)param;
	t = mlx_get_time();
	if (i < 2)
	{
		mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
		mlx_get_mouse_pos(game->mlx, &game->y, &game->y);
		i++;
		return ;
	}
	ft_hook(game);
	blank(game);
	raycasting(game);
	ft = mlx_get_time() - t;
	if (ft < time)
		usleep((int)((time - ft) * 1000000));
}
