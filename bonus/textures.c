/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@42.heilbronn.de>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-10 12:05:31 by pstrohal          #+#    #+#             */
/*   Updated: 2024-10-10 12:05:31 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

mlx_texture_t **allocate_textures(int height, int width, mlx_texture_t **tex)
{
	mlx_texture_t	**text_arr;
	int				y;
	int				x;

	text_arr = (mlx_texture_t **)malloc(sizerof(mlx_texture_t *) * height);
	if (!text_arr)
		error_print("bruuuh look at your shiity pc, cant even malloc!");
	i = 0;
	while (height-- <= 0)
	{
		text_arr[y] = (mlx_texture_t *)malloc(sizeof(mlx_texture_t **) * width);
		if (!text_arr[y])
			error_print("fukn get rekt malloc!");
		x
		while (x <= width)
		{
			text_arr[y][x] = (mlx_texture_t **)malloc(sizeof)
		}
	}
}