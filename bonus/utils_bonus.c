/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:30:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/03 19:55:39 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int	mv_arr(char **src, char **dest)
{
	int	i;

	i = 0;
	if (src && dest)
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = NULL;
	}
	return (i);
}

t_game	*game_pointer(int i, void *game)
{
	static t_game	*def_not_global;

	if (i == 1 && game)
	{
		def_not_global = (t_game *)game;
		return (NULL);
	}
	else
		return (def_not_global);
}

void	free_game(t_game *game, int j)
{
	int	i;

	free(game->map.map);
	free(game->map.str_map);
	if (j)
	{
		i = 0;
		while (i < 6)
		{
			mlx_delete_texture(game->map.textures[i]);
			i++;
		}
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
