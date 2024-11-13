/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:00:58 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/13 14:19:28 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// frees enemy struct list
void	free_e_list(t_game *game)
{
	t_ai *e = game->e;

	while(game->e)
	{
		e = game->e->next;
		free(game->e);
		game->e = e;
	}
}

// frees all the sprite textures
void	free_sprites(t_game *game)
{
	int i;

	i = -1;
	mlx_delete_image(game->mlx, game->emg);
	mlx_delete_image(game->mlx, game->cmg);
	mlx_delete_image(game->mlx, game->player.gun_img);
	mlx_delete_image(game->mlx, game->hp);
	if(game->w_img)
	{
		mlx_delete_image(game->mlx, game->w_img);
		mlx_delete_image(game->mlx, game->tmg);
	}
	if (game->l_img)
		mlx_delete_image(game->mlx, game->l_img);
	while(++i < 6)
		mlx_delete_texture(game->e->tex[ALIVE][i]);
	i = -1;
	while (++i < 8)
		mlx_delete_texture(game->e->tex[DYING][i]);
	i = -1;
	while (++i < 4)
		mlx_delete_texture(game->player.gun[i]);
	free_e_list(game);
}

// frees all textures for Walls and Bullethole also the indiv textures
void	free_textures(t_game *game)
{
	long	i;
	long	j;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->map.textures[i])
			mlx_delete_texture(game->map.textures[i]);
		game->map.textures[i] = NULL;
		i++;
	}
	j = game->map.map_h * game->map.map_w;
	i = -1;
	while (++i < j)
	{
		if (game->map.indiv[i])
			free_indiv(game->map.indiv[i]);
	}
}

// main frees the game and everything connected to it
void	free_game_end(t_game *game)
{
	free_int_array(game->map.map, game->map.map_h);
	free_string_array(game->map.str_map);
	free_sprites(game);
	free_textures(game);
	ft_lstclear(&game->map.dstuff.doors, &free_door);
	mlx_delete_image(game->mlx, game->img);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	mlx_terminate(game->mlx);
}