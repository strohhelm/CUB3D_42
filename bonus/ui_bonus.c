/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:09:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/11 15:29:26 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void epic_w(t_game *game)
{
	mlx_texture_t *tw;
	mlx_image_t *w;

	tw = mlx_load_png("./include/textures/w.png");
	w = mlx_texture_to_image(game->mlx, tw);
	mlx_image_to_window(game->mlx, w, 0, 0);
	game->over = 1;
}

void display_enemycount(t_game *game)
{
	char *str;
	char *nstr;
	int count;
	t_ai *e;

	e = game->e;
	count = 0;
	while (e)
	{
		if (e->state == ALIVE)
			count ++;
		e = e->next;
	}
	if(game->cmg)
		mlx_delete_image(game->mlx, game->cmg);
	if (count == 0)
	{
		epic_w(game);
		return;
	}
	nstr = ft_itoa(count);
	str = ft_strjoin("Enemy count: ", nstr);	
	game->cmg = mlx_put_string(game->mlx, str, 125, 380);
	free(nstr);
	free(str);
}

void	health_bar(t_game *game)
{
	int	start;
	int	end;
	int	hp;
	int	starty;
	int	y;
	int	x;

	start = WIDTH / 2 - 250;
	end = WIDTH / 2 + 250;
	hp = start + game->player.hp * 5;
	starty = HEIGHT - HEIGHT / 15;
	y = starty;
	while (y <= starty + 15)
	{
		x = start;
		while (x <= end)
		{
			if (x < hp)
				mlx_put_pixel(game->hp, x, y, 0xFF0000FF);
			else
				mlx_put_pixel(game->hp, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void game_over_check(t_game *game)
{
	int x; 
	int y;
	mlx_texture_t *end;
	mlx_image_t *go;

	x = 0;
	end = mlx_load_png("./include/textures/GAME_OVER.png");
	go = mlx_texture_to_image(game->mlx, end);
	if (game->player.hp > 0)
		return;
	mlx_image_to_window(game->mlx, go, 0, 0);
	game->over = 1;
}
