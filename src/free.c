/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:05:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/13 16:58:42 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_game_end(t_game *game)
{
	int	i;

	free_int_array(game->map.map, game->map.map_h);
	free_string_array(game->map.str_map);
	mlx_delete_image(game->mlx, game->img);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(game->map.textures[i]);
		i++;
	}
	mlx_terminate(game->mlx);
	exit(0);
}

void	free_int_array(int **arr, int h)
{
	if (arr)
	{
		while (--h >= 0)
		{
			free(arr[h]);
		}
		free(arr);
	}
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}
