/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:07 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/27 15:05:45 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	load_gun(t_game *game)
{
	mlx_texture_t	**gun;
	mlx_image_t		*gun_img;
	int				i;

	i = 0;
	gun = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	gun[0] = mlx_load_png("include/textures/gunsprites/1.png");
	gun[1] = mlx_load_png("include/textures/gunsprites/2.png");
	gun[2] = mlx_load_png("include/textures/gunsprites/3.png");
	gun[3] = mlx_load_png("include/textures/gunsprites/4.png");
	while (i < 4)
	{
		err_check(gun[i], "gun texture error\n");
		i++;
	}
	gun_img = mlx_texture_to_image(game->mlx, gun[0]);
	err_check(gun_img, "fucking malloc");
	game->player.gun = gun;
	game->player.gun_img = gun_img;
	mlx_image_to_window(game->mlx, gun_img, WIDTH - 600, HEIGHT - 500);
}

void	gun_anim(t_game *game, int frame)
{
	static int	i = 0;

	if (game->over || !game->player.attack)
		return ;
	game->player.attack = 2;
	if (frame % 2 == 0 && i < 4)
		i++;
	if (i <= 3)
	{
		mlx_delete_image(game->mlx, game->player.gun_img);
		game->player.gun_img = mlx_texture_to_image(game->mlx,
				game->player.gun[i]);
		err_check(game->player.gun[i], " fucking malloc");
		mlx_image_to_window(game->mlx, game->player.gun_img, WIDTH - 600, HEIGHT
			- 500);
		return ;
	}
	mlx_delete_image(game->mlx, game->player.gun_img);
	game->player.gun_img = mlx_texture_to_image(game->mlx, game->player.gun[0]);
	err_check(game->player.gun_img, " fucking malloc");
	mlx_image_to_window(game->mlx, game->player.gun_img, WIDTH - 600, HEIGHT
		- 500);
	i = 0;
	game->player.attack = 0;
}
