/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:09:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/27 15:02:40 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	epic_w(t_game *game)
{
	mlx_texture_t	*tw;
	char			str[50];
	char			*time;

	tw = mlx_load_png("./include/textures/W.png");
	err_check(tw, "w texture error");
	game->w_img = mlx_texture_to_image(game->mlx, tw);
	err_check(game->w_img, "w img error");
	mlx_image_to_window(game->mlx, game->w_img, 0, 0);
	mlx_delete_texture(tw);
	snprintf(str, sizeof(str), "%.*f", 2, mlx_get_time());
	time = ft_strjoin("Time to Complete: ", str);
	game->tmg = mlx_put_string(game->mlx, time, (WIDTH / 2) - 125, (HEIGHT / 2)
			+ 100);
	free(time);
	game->over = 1;
}

void	display_enemycount(t_game *game)
{
	char	*str;
	char	*nstr;
	int		count;
	t_ai	*e;

	e = game->e;
	count = 0;
	while (e)
	{
		if (e->state == ALIVE)
			count++;
		e = e->next;
	}
	if (game->cmg)
		mlx_delete_image(game->mlx, game->cmg);
	if (count == 0 && game->enemy_count != 0)
	{
		epic_w(game);
		return ;
	}
	nstr = ft_itoa(count);
	str = ft_strjoin("Enemy count: ", nstr);
	game->cmg = mlx_put_string(game->mlx, str, 125, 380);
	free(nstr);
	free(str);
}

void	health_bar(t_game *game)
{
	int	hp;
	int	starty;
	int	y;
	int	x;

	hp = (WIDTH / 2 - 250) + game->player.hp * 5;
	starty = HEIGHT - HEIGHT / 15;
	y = starty;
	while (y <= starty + 15)
	{
		x = WIDTH / 2 - 250;
		while (x <= WIDTH / 2 + 250)
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

void	game_over_check(t_game *game)
{
	mlx_texture_t	*end;

	if (game->player.hp > 0)
		return ;
	end = mlx_load_png("./include/textures/GAME_OVER.png");
	err_check(end, "game over texture error");
	game->l_img = mlx_texture_to_image(game->mlx, end);
	err_check(game->l_img, "game over img error");
	mlx_image_to_window(game->mlx, game->l_img, 0, 0);
	mlx_delete_texture(end);
	game->over = 1;
}

void	clear_img(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->emg, x, y, 0);
			y++;
		}
		x++;
	}
}
