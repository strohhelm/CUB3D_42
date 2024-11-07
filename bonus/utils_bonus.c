/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:30:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/07 23:02:02 by pstrohal         ###   ########.fr       */
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

void	free_game_end(t_game *game)
{
	int	i;

	free_int_array(game->map.map, game->map.map_h);
	free_string_array(game->map.str_map);
	mlx_delete_image(game->mlx, game->img);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	mlx_terminate(game->mlx);
	i = 0;
	while (i < 6)
	{
		mlx_delete_texture(game->map.textures[i]);
		i++;
	}
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
int	left_or_right(t_point a, t_point b, t_point p)
{
	double	cross_product;
	t_point	b_vector;
	t_point	p_vector;

	b_vector = vector(a, b);
	p_vector = vector(a, p);
	cross_product = b_vector.x * p_vector.y - b_vector.y * p_vector.x;
	if (cross_product < 0 )
		return (LEFT);
	else
		return (RIGHT);
}
